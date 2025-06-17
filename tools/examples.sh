#!/bin/bash

# Map Editor Examples Script

echo "=== FDF Map Editor Examples ==="
echo

# Build the tool
make

if [ ! -f "map_editor" ]; then
    echo "Failed to build map_editor"
    exit 1
fi

# Create test maps directory
mkdir -p test_maps

echo "1. Creating test map with gradient..."
./map_editor gradient ../test_maps/elem-col.fdf test_maps/gradient.fdf 0 20 1

echo "2. Adding noise to gradient..."
./map_editor noise test_maps/gradient.fdf test_maps/noisy.fdf 3

echo "3. Smoothing noisy map..."
./map_editor smooth test_maps/noisy.fdf test_maps/smooth.fdf 2

echo "4. Replacing all 0 values with 5..."
./map_editor replace ../test_maps/elem-col.fdf test_maps/replaced.fdf 0 5

echo "5. Flood fill from center..."
./map_editor info ../test_maps/elem-col.fdf
./map_editor flood ../test_maps/elem-col.fdf test_maps/flood.fdf 5 5 25

echo "6. Creating radial mountain..."
./map_editor gradient test_maps/mountain.fdf test_maps/mountain.fdf 0 30 3

echo
echo "Generated test maps:"
ls -la test_maps/

echo
echo "You can now test these maps with FDF:"
echo "  ./fdf test_maps/gradient.fdf"
echo "  ./fdf test_maps/mountain.fdf"
echo "  ./fdf test_maps/flood.fdf"
