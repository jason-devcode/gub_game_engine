#!/bin/bash

if [ ! -d "build" ]; then
    echo "Creating build directory..."
    mkdir build
fi

# gcc src/sample_fast_triangle.c -o build/sample -lm -lSDL -O3
# gcc src/sample_triangle.c -o build/sample -lm -lSDL -O3
gcc src/sample_render_mesh.c -o build/sample -lm -lSDL -O3

echo "Compilation completed."
