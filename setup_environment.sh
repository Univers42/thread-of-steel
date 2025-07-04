#!/bin/bash

# Enhanced Build Tool - Powerful project management script
# Features: Error handling, logging, parallel builds, config management, cleanup, and more

set -euo pipefail  # Exit on error, undefined vars, pipe failures

# Configuration
readonly SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
readonly LOG_FILE="${SCRIPT_DIR}/build.log"
readonly CONFIG_FILE="${SCRIPT_DIR}/build.config"
readonly LOCK_FILE="${SCRIPT_DIR}/.build.lock"

# Colors for output
readonly RED='\033[0;31m'
readonly GREEN='\033[0;32m'
readonly YELLOW='\033[1;33m'
readonly BLUE='\033[0;34m'
readonly NC='\033[0m' # No Color

# Default configuration
declare -A CONFIG=(
    ["PARALLEL_JOBS"]="$(nproc)"
    ["TIMEOUT"]="300"
    ["VERBOSE"]="false"
    ["DRY_RUN"]="false"
    ["FORCE"]="false"
    ["BACKUP_COUNT"]="5"
)

# Arrays for project structure
filters=(
    "node_modules"
    "dist"
    "build"
    ".env"
    ".DS_Store"
    "*.log"
    "*.tmp"
    ".cache"
    "coverage"
    ".nyc_output"
    "*.swp"
    "*.swo"
    "*~"
)

setter_dirs=(
    "srcs"
    "srcs/rendu"
    "srcs/parser"
    "srcs/core"
    "srcs/"
    "inc"
    "libs"
    "tests"
    "docs"
    "examples"
)

builder_dirs=(
    "lib/libft"
    "lib/minilibx"
)

modules=(
    "libft"
    "minilibx"
)

environments=(
    "git"
    "backup"
    "codebase"
    "tests"
)

# Logging functions
log() {
    local level="$1"
    shift
    local message="$*"
    local timestamp=$(date '+%Y-%m-%d %H:%M:%S')
    
    case "$level" in
        "ERROR")   echo -e "${RED}[ERROR]${NC} $message" >&2 ;;
        "WARN")    echo -e "${YELLOW}[WARN]${NC} $message" ;;
        "INFO")    echo -e "${GREEN}[INFO]${NC} $message" ;;
        "DEBUG")   [[ "${CONFIG[VERBOSE]}" == "true" ]] && echo -e "${BLUE}[DEBUG]${NC} $message" ;;
    esac
    
    echo "[$timestamp] [$level] $message" >> "$LOG_FILE"
}

# Error handling
error_exit() {
    log "ERROR" "$1"
    cleanup
    exit 1
}

# Signal handling
trap 'error_exit "Script interrupted"' INT TERM

# Lock management
acquire_lock() {
    if [[ -f "$LOCK_FILE" ]]; then
        local lock_pid=$(cat "$LOCK_FILE")
        if kill -0 "$lock_pid" 2>/dev/null; then
            error_exit "Another instance is running (PID: $lock_pid)"
        else
            log "WARN" "Removing stale lock file"
            rm -f "$LOCK_FILE"
        fi
    fi
    echo $$ > "$LOCK_FILE"
}

release_lock() {
    [[ -f "$LOCK_FILE" ]] && rm -f "$LOCK_FILE"
}

# Cleanup function
cleanup() {
    log "INFO" "Cleaning up..."
    release_lock
}

# Load configuration
load_config() {
    if [[ -f "$CONFIG_FILE" ]]; then
        log "INFO" "Loading configuration from $CONFIG_FILE"
        while IFS='=' read -r key value; do
            [[ $key =~ ^[[:space:]]*# ]] && continue
            [[ -z "$key" ]] && continue
            CONFIG["$key"]="$value"
        done < "$CONFIG_FILE"
    fi
}

# Save configuration
save_config() {
    log "INFO" "Saving configuration to $CONFIG_FILE"
    for key in "${!CONFIG[@]}"; do
        echo "$key=${CONFIG[$key]}"
    done > "$CONFIG_FILE"
}

# Validate dependencies
check_dependencies() {
    local deps=("git" "tar" "curl" "make")
    local missing=()
    
    for dep in "${deps[@]}"; do
        if ! command -v "$dep" &> /dev/null; then
            missing+=("$dep")
        fi
    done
    
    if [[ ${#missing[@]} -gt 0 ]]; then
        error_exit "Missing dependencies: ${missing[*]}"
    fi
}

# Enhanced git environment setup
git_env() {
    log "INFO" "Setting up git environment"
    
    if [[ "${CONFIG[DRY_RUN]}" == "true" ]]; then
        log "INFO" "DRY RUN: Would create .gitignore"
        return
    fi
    
    # Initialize git if not already done
    if [[ ! -d ".git" ]]; then
        git init
        log "INFO" "Initialized git repository"
    fi
    
    # Create comprehensive .gitignore
    {
        echo "# Build Tool Generated .gitignore"
        echo "# Generated on $(date)"
        echo ""
        
        for filter in "${filters[@]}"; do
            echo "$filter"
        done
        
        echo ""
        echo "# OS generated files"
        echo ".DS_Store"
        echo ".DS_Store?"
        echo "._*"
        echo ".Spotlight-V100"
        echo ".Trashes"
        echo "ehthumbs.db"
        echo "Thumbs.db"
        
    } > .gitignore
    
    log "INFO" "Created .gitignore with ${#filters[@]} filters"
}

# Enhanced module building with parallel support
build_modules() {
    log "INFO" "Building modules with ${CONFIG[PARALLEL_JOBS]} parallel jobs"
    
    local pids=()
    local failed_modules=()
    
    for module in "${modules[@]}"; do
        if [[ ${#pids[@]} -ge ${CONFIG[PARALLEL_JOBS]} ]]; then
            # Wait for any job to complete
            wait -n
        fi
        
        build_single_module "$module" &
        pids+=($!)
    done
    
    # Wait for all remaining jobs
    for pid in "${pids[@]}"; do
        if ! wait "$pid"; then
            failed_modules+=("$module")
        fi
    done
    
    if [[ ${#failed_modules[@]} -gt 0 ]]; then
        error_exit "Failed to build modules: ${failed_modules[*]}"
    fi
}

# Build single module
build_single_module() {
    local module="$1"
    local link="git@github.com:Univers42/${module}.git"
    local target_dir="inc/${module}"
    
    log "INFO" "Processing module: $module"
    
    if [[ "${CONFIG[DRY_RUN]}" == "true" ]]; then
        log "INFO" "DRY RUN: Would build module $module"
        return
    fi
    
    if [[ -d "$target_dir" ]]; then
        if [[ "${CONFIG[FORCE]}" == "true" ]]; then
            log "WARN" "Force mode: removing existing module $module"
            rm -rf "$target_dir"
        else
            log "INFO" "Module $module already exists, skipping"
            return
        fi
    fi
    
    # Add submodule with timeout
    if timeout "${CONFIG[TIMEOUT]}" git submodule add "$link" "$target_dir"; then
        log "INFO" "Successfully added module: $module"
        
        # Build the module if Makefile exists
        if [[ -f "$target_dir/Makefile" ]]; then
            log "INFO" "Building module: $module"
            (cd "$target_dir" && make -j"${CONFIG[PARALLEL_JOBS]}")
        fi
    else
        log "ERROR" "Failed to add module: $module"
        return 1
    fi
}

# Enhanced backup with rotation
backup_environment() {
    log "INFO" "Creating backup with rotation"
    
    local backup_dir="backup"
    local timestamp=$(date '+%Y%m%d_%H%M%S')
    local current_backup="${backup_dir}/backup_${timestamp}"
    
    if [[ "${CONFIG[DRY_RUN]}" == "true" ]]; then
        log "INFO" "DRY RUN: Would create backup at $current_backup"
        return
    fi
    
    mkdir -p "$backup_dir"
    
    # Create current backup
    if cp -r . "$current_backup" 2>/dev/null; then
        log "INFO" "Backup created: $current_backup"
    else
        log "ERROR" "Failed to create backup"
        return 1
    fi
    
    # Rotate old backups
    local backups=($(ls -1t "$backup_dir"/backup_* 2>/dev/null || true))
    if [[ ${#backups[@]} -gt ${CONFIG[BACKUP_COUNT]} ]]; then
        local to_remove=("${backups[@]:${CONFIG[BACKUP_COUNT]}}")
        log "INFO" "Removing old backups: ${to_remove[*]}"
        for old_backup in "${to_remove[@]}"; do
            rm -rf "$backup_dir/$old_backup"
        done
    fi
}

# Enhanced codebase setup
setup_codebase() {
    log "INFO" "Setting up project structure"
    
    for dir in "${setter_dirs[@]}"; do
        if [[ -n "$dir" ]]; then
            if [[ "${CONFIG[DRY_RUN]}" == "true" ]]; then
                log "INFO" "DRY RUN: Would create directory $dir"
            else
                mkdir -p "$dir"
                log "INFO" "Created directory: $dir"
            fi
        fi
    done
    
    # Create basic project files
    local project_files=(
        "README.md"
        "Makefile"
        "srcs/main.c"
        "tests/test_main.c"
    )
    
    for file in "${project_files[@]}"; do
        if [[ ! -f "$file" && "${CONFIG[DRY_RUN]}" != "true" ]]; then
            mkdir -p "$(dirname "$file")"
            touch "$file"
            log "INFO" "Created file: $file"
        fi
    done
}

# Enhanced removal with safety checks
remove_environment() {
    log "WARN" "Removing environment components"
    
    if [[ "${CONFIG[FORCE]}" != "true" ]]; then
        read -p "Are you sure you want to remove the environment? (y/N): " -n 1 -r
        echo
        if [[ ! $REPLY =~ ^[Yy]$ ]]; then
            log "INFO" "Operation cancelled"
            return
        fi
    fi
    
    local items_to_remove=(".git" "backup" ".gitignore" ".gitmodules")
    
    for item in "${items_to_remove[@]}"; do
        if [[ -e "$item" ]]; then
            if [[ "${CONFIG[DRY_RUN]}" == "true" ]]; then
                log "INFO" "DRY RUN: Would remove $item"
            else
                rm -rf "$item"
                log "INFO" "Removed: $item"
            fi
        fi
    done
}

# Test environment
test_environment() {
    log "INFO" "Running environment tests"
    
    local tests_passed=0
    local tests_total=0
    
    # Test git setup
    ((tests_total++))
    if [[ -d ".git" ]]; then
        log "INFO" "✓ Git repository exists"
        ((tests_passed++))
    else
        log "WARN" "✗ Git repository missing"
    fi
    
    # Test directory structure
    for dir in "${setter_dirs[@]}"; do
        if [[ -n "$dir" ]]; then
            ((tests_total++))
            if [[ -d "$dir" ]]; then
                log "INFO" "✓ Directory exists: $dir"
                ((tests_passed++))
            else
                log "WARN" "✗ Directory missing: $dir"
            fi
        fi
    done
    
    log "INFO" "Tests passed: $tests_passed/$tests_total"
    
    if [[ $tests_passed -eq $tests_total ]]; then
        log "INFO" "All tests passed!"
        return 0
    else
        log "WARN" "Some tests failed"
        return 1
    fi
}

# Main execution functions
create_environment() {
    log "INFO" "Creating complete environment"
    git_env
    setup_codebase
    build_modules
    backup_environment
}

# Enhanced minilibx extraction
extract_minilibx() {
    local archive="$1"
    local target_dir="inc/minilibx"
    
    log "INFO" "Extracting minilibx from $archive"
    
    if [[ ! -f "$archive" ]]; then
        error_exit "Archive not found: $archive"
    fi
    
    if [[ "${CONFIG[DRY_RUN]}" == "true" ]]; then
        log "INFO" "DRY RUN: Would extract $archive to $target_dir"
        return
    fi
    
    mkdir -p "$target_dir"
    
    case "$archive" in
        *.tar.gz|*.tgz)
            tar -xzf "$archive" -C "$target_dir" --strip-components=1
            ;;
        *.tar.bz2)
            tar -xjf "$archive" -C "$target_dir" --strip-components=1
            ;;
        *.zip)
            unzip -q "$archive" -d "$target_dir"
            ;;
        *)
            error_exit "Unsupported archive format: $archive"
            ;;
    esac
    
    log "INFO" "Successfully extracted minilibx"
}

# Status reporting
show_status() {
    echo -e "${BLUE}=== Build Tool Status ===${NC}"
    echo "Project Directory: $(pwd)"
    echo "Log File: $LOG_FILE"
    echo "Configuration: $CONFIG_FILE"
    echo ""
    
    echo -e "${GREEN}Configuration:${NC}"
    for key in "${!CONFIG[@]}"; do
        echo "  $key: ${CONFIG[$key]}"
    done
    echo ""
    
    echo -e "${GREEN}Directory Structure:${NC}"
    for dir in "${setter_dirs[@]}"; do
        if [[ -n "$dir" ]]; then
            if [[ -d "$dir" ]]; then
                echo "  ✓ $dir"
            else
                echo "  ✗ $dir"
            fi
        fi
    done
    echo ""
    
    echo -e "${GREEN}Modules:${NC}"
    for module in "${modules[@]}"; do
        local target_dir="inc/$module"
        if [[ -d "$target_dir" ]]; then
            echo "  ✓ $module"
        else
            echo "  ✗ $module"
        fi
    done
}

# Help function
show_help() {
    cat << EOF
Enhanced Build Tool - Powerful project management script

Usage: $0 [OPTIONS] [COMMAND]

Commands:
    create          Create complete environment (default)
    build           Build modules only
    backup          Create backup only
    remove          Remove environment
    test            Test environment
    status          Show status
    extract FILE    Extract minilibx from archive
    config          Edit configuration
    help            Show this help

Options:
    -v, --verbose       Enable verbose output
    -d, --dry-run       Show what would be done
    -f, --force         Force operations
    -j, --jobs N        Number of parallel jobs (default: $(nproc))
    -t, --timeout N     Timeout in seconds (default: 300)
    -h, --help          Show this help

Examples:
    $0                          # Create environment
    $0 -v build                 # Build modules with verbose output
    $0 -d remove                # Dry run removal
    $0 -f -j 4 create          # Force create with 4 parallel jobs
    $0 extract minilibx.tgz     # Extract minilibx archive
    $0 status                   # Show current status

EOF
}

# Parse command line arguments
parse_args() {
    while [[ $# -gt 0 ]]; do
        case $1 in
            -v|--verbose)
                CONFIG["VERBOSE"]="true"
                shift
                ;;
            -d|--dry-run)
                CONFIG["DRY_RUN"]="true"
                shift
                ;;
            -f|--force)
                CONFIG["FORCE"]="true"
                shift
                ;;
            -j|--jobs)
                CONFIG["PARALLEL_JOBS"]="$2"
                shift 2
                ;;
            -t|--timeout)
                CONFIG["TIMEOUT"]="$2"
                shift 2
                ;;
            -h|--help)
                show_help
                exit 0
                ;;
            create|build|backup|remove|test|status|config|help)
                COMMAND="$1"
                shift
                ;;
            extract)
                COMMAND="extract"
                EXTRACT_FILE="$2"
                shift 2
                ;;
            *)
                error_exit "Unknown option: $1"
                ;;
        esac
    done
}

# Main execution
main() {
    local COMMAND="create"
    local EXTRACT_FILE=""
    touch "$LOG_FILE"
    log "INFO" "Starting Enhanced Build Tool"
    parse_args "$@"
    load_config
    check_dependencies
    acquire_lock
    case "$COMMAND" in
        create)
            create_environment
            ;;
        build)
            build_modules
            ;;
        backup)
            backup_environment
            ;;
        remove)
            remove_environment
            ;;
        test)
            test_environment
            ;;
        status)
            show_status
            ;;
        extract)
            [[ -n "$EXTRACT_FILE" ]] || error_exit "No file specified for extraction"
            extract_minilibx "$EXTRACT_FILE"
            ;;
        config)
            save_config
            log "INFO" "Configuration saved to $CONFIG_FILE"
            ;;
        help)
            show_help
            ;;
        *)
            error_exit "Unknown command: $COMMAND"
            ;;
    esac
    
    log "INFO" "Build tool completed successfully"
    cleanup
}

main "$@"