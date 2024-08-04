#!/bin/bash

if [ ! -d "build" ]; then
    echo "Creating build directory..."
    mkdir build
fi

gcc src/sample_parallelogram.c -o build/sample -lm -lSDL -O3

echo "Compilation completed."
