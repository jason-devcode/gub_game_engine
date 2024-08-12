#!/bin/bash

if [ ! -d "build" ]; then
    echo "Creating build directory..."
    mkdir build
fi

# gcc src/sample_fast_triangle.c -o build/sample -lm -lSDL -O3 --pedantic -Wfatal-errors
# gcc src/sample_triangle.c -o build/sample -lm -lSDL -O3 --pedantic -Wfatal-errors
# gcc src/sample_render_mesh.c -o build/sample -lm -lSDL -O3 --pedantic -Wfatal-errors
# gcc src/sample_plane_generator.c -o build/sample -lm -lSDL -O3 --pedantic -Wfatal-errors
# gcc src/sample_bezier.c -o build/sample -lm -lSDL -O3 --pedantic -Wfatal-errors
gcc src/sample_joystick.c -o build/sample -lm -lSDL -O3 --pedantic -Wfatal-errors

echo "Compilation completed."
