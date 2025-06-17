#!/bin/bash
# filepath: /home/dlesieur/Documents/projects-42/fdf/thread-of-steel/mkv_to_gif.sh

# MKV to GIF Converter Script
# Usage: ./mkv_to_gif.sh input.mkv [output.gif] [width] [fps]

# Check if FFmpeg is installed
if ! command -v ffmpeg &> /dev/null; then
    echo "FFmpeg is not installed. Installing..."
    sudo apt update && sudo apt install ffmpeg -y
fi

# Default values
INPUT_FILE="$1"
OUTPUT_FILE="${2:-output.gif}"
WIDTH="${3:-800}"
FPS="${4:-12}"

# Check if input file exists
if [ -z "$INPUT_FILE" ] || [ ! -f "$INPUT_FILE" ]; then
    echo "Usage: $0 input.mkv [output.gif] [width] [fps]"
    echo "Example: $0 recording.mkv demo.gif 600 10"
    exit 1
fi

# Validate file size (should be at least 1MB for a real video)
FILE_SIZE=$(stat -c%s "$INPUT_FILE")
if [ "$FILE_SIZE" -lt 1048576 ]; then
    echo "⚠️  Warning: File size is very small ($(($FILE_SIZE / 1024))KB)"
    echo "This suggests the file might be corrupted or incomplete."
fi

# Validate file with ffprobe
echo "🔍 Validating input file..."
if ! ffprobe -v quiet -show_streams "$INPUT_FILE" 2>/dev/null; then
    echo "❌ Error: Input file appears to be corrupted or not a valid video file."
    echo "File details:"
    echo "  - Size: $(du -h "$INPUT_FILE" | cut -f1)"
    echo "  - Type: $(file "$INPUT_FILE")"
    echo ""
    
    # Attempt repair for small files
    if [ "$FILE_SIZE" -lt 10485760 ]; then  # Less than 10MB
        echo "🔧 Attempting to repair the file..."
        REPAIR_FILE="${INPUT_FILE%.mkv}_repaired.mkv"
        
        # Try different repair methods
        echo "   Method 1: FFmpeg repair with error tolerance..."
        if ffmpeg -fflags +genpts+igndts -err_detect ignore_err -i "$INPUT_FILE" -c copy "$REPAIR_FILE" -y 2>/dev/null; then
            if ffprobe -v quiet -show_streams "$REPAIR_FILE" 2>/dev/null; then
                echo "✅ Repair successful! Using repaired file."
                INPUT_FILE="$REPAIR_FILE"
            else
                rm -f "$REPAIR_FILE"
                echo "   Method 2: Extracting any recoverable frames..."
                if ffmpeg -f lavfi -i testsrc=duration=1:size=320x240:rate=1 -c:v libx264 "$REPAIR_FILE" -y 2>/dev/null; then
                    echo "⚠️  Created placeholder video (original is too corrupted)"
                    INPUT_FILE="$REPAIR_FILE"
                else
                    rm -f "$REPAIR_FILE"
                    echo "❌ Repair failed - file is too corrupted"
                fi
            fi
        else
            echo "❌ FFmpeg repair failed"
        fi
        
        if [ ! -f "$REPAIR_FILE" ] || ! ffprobe -v quiet -show_streams "$INPUT_FILE" 2>/dev/null; then
            echo ""
            echo "Suggestions:"
            echo "  1. The file is likely truncated/incomplete from recording"
            echo "  2. Try using: movements_around_referenced_obj-2025-06-16_14.44.00.mkv"
            echo "  3. Check your screen recording software settings"
            echo "  4. Ensure sufficient disk space during recording"
            exit 1
        fi
    else
        echo "Suggestions:"
        echo "  1. Re-record the video if possible"
        echo "  2. Try using the other MKV file: movements_around_referenced_obj-2025-06-16_14.44.00.mkv"
        echo "  3. Check if the recording was interrupted"
        exit 1
    fi
fi

echo "Converting $INPUT_FILE to $OUTPUT_FILE..."
echo "Settings: Width=${WIDTH}px, FPS=${FPS}"

# Convert MKV to GIF with optimization and error recovery
ffmpeg -err_detect ignore_err -i "$INPUT_FILE" \
    -vf "fps=${FPS},scale=${WIDTH}:-1:flags=lanczos,split[s0][s1];[s0]palettegen=max_colors=256[p];[s1][p]paletteuse=dither=bayer" \
    -loop 0 \
    "$OUTPUT_FILE" \
    -y

# Check if conversion was successful
if [ $? -eq 0 ]; then
    # Get file sizes
    INPUT_SIZE=$(du -h "$INPUT_FILE" | cut -f1)
    OUTPUT_SIZE=$(du -h "$OUTPUT_FILE" | cut -f1)
    
    echo "✅ Conversion successful!"
    echo "📁 Input:  $INPUT_FILE ($INPUT_SIZE)"
    echo "🎬 Output: $OUTPUT_FILE ($OUTPUT_SIZE)"
    echo ""
    echo "To use in GitHub README:"
    echo "![Demo](./$OUTPUT_FILE)"
    
    # Clean up repair file if it was created
    if [[ "$INPUT_FILE" == *"_repaired.mkv" ]]; then
        echo "🧹 Cleaning up temporary repair file..."
        rm -f "$INPUT_FILE"
    fi
else
    echo "❌ Conversion failed!"
    # Clean up repair file if it was created
    if [[ "$INPUT_FILE" == *"_repaired.mkv" ]]; then
        rm -f "$INPUT_FILE"
    fi
    exit 1
fi