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

echo "Converting $INPUT_FILE to $OUTPUT_FILE..."
echo "Settings: Width=${WIDTH}px, FPS=${FPS}"

# Convert MKV to GIF with optimization
ffmpeg -i "$INPUT_FILE" \
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
else
    echo "❌ Conversion failed!"
    exit 1
fi