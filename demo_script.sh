#!/bin/bash

# FDF Demo Script - Thread of Steel Edition
# Showcases various features and maps

echo "🚀 FDF - Thread of Steel Edition Demo"
echo "====================================="

# Check if binary exists
if [ ! -f "./fdf" ]; then
    echo "❌ FDF binary not found. Please run 'make' first."
    exit 1
fi

# Function to run demo with instructions
run_demo() {
    local map_file=$1
    local description=$2
    
    echo ""
    echo "🎯 Demo: $description"
    echo "📁 Map: $map_file"
    echo ""
    echo "Try these controls:"
    echo "  • Drag mouse for trackball rotation"
    echo "  • Press 1-9 for color themes"
    echo "  • Press Alt+1-9 for shape transformations"
    echo "  • Use WASD for movement"
    echo "  • Mouse wheel to zoom"
    echo "  • Press ESC to exit"
    echo ""
    echo "Press Enter to start demo..."
    read
    
    ./fdf "$map_file"
}

# Demo sequence
echo "This demo will showcase different maps and features."
echo "Each demo runs independently - exit with ESC to continue."

# Demo 1: Classic 42 map
if [ -f "test_maps/42.fdf" ]; then
    run_demo "test_maps/42.fdf" "Classic 42 Logo - Try sphere transformation (Alt+1)"
fi

# Demo 2: Julia fractal
if [ -f "test_maps/julia.fdf" ]; then
    run_demo "test_maps/julia.fdf" "Julia Set Fractal - Try rainbow theme (4) and wave shape (Alt+4)"
fi

# Demo 3: Mars terrain
if [ -f "test_maps/mars.fdf" ]; then
    run_demo "test_maps/mars.fdf" "Mars Surface - Try desert theme (9) and ripple effect (Alt+8)"
fi

# Demo 4: Pyramid
if [ -f "test_maps/pyramide.fdf" ]; then
    run_demo "test_maps/pyramide.fdf" "Pyramid Structure - Try earth theme (1) and cone shape (Alt+3)"
fi

# Demo 5: Large ocean data (if available)
if [ -f "test_maps/MGDS_MID_OCEAN_RIDGES_EPR_8_11_N_OCEAN1_L.fdf" ]; then
    run_demo "test_maps/MGDS_MID_OCEAN_RIDGES_EPR_8_11_N_OCEAN1_L.fdf" "Ocean Ridge Data - Try ocean theme (3) and cylinder shape (Alt+2)"
fi

echo ""
echo "🎉 Demo complete! Key features demonstrated:"
echo "  ✅ Smooth trackball rotation"
echo "  ✅ Multiple color themes" 
echo "  ✅ Shape transformations"
echo "  ✅ Performance optimization"
echo "  ✅ Real-time interaction"
echo ""
echo "For more information, see README.md"
