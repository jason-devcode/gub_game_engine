#!/bin/bash

if [ ! -d "build" ]; then
    echo "Creating build directory..."
    mkdir build
fi

SDL_VERSION_1="-lSDL -DUSE_SDL_1"
SDL_VERSION_2="-lSDL2 -DUSE_SDL_2"

API_GRAPHIC_LIBRARIES=${SDL_VERSION_2}

# gcc src/sample_fast_triangle.c -o build/sample -lm -lSDL -O3 --pedantic -Wfatal-errors
# gcc src/sample_triangle.c -o build/sample -lm -lSDL -O3 --pedantic -Wfatal-errors
# gcc src/sample_render_mesh.c -o build/sample -lm -lSDL -O3 --pedantic -Wfatal-errors
# gcc src/sample_plane_generator.c -o build/sample -lm -lSDL -O3 --pedantic -Wfatal-errors
# gcc src/sample_bezier.c -o build/sample -lm -lSDL -O3 --pedantic -Wfatal-errors
# gcc src/sample_joystick.c -o build/sample -lm ${API_GRAPHIC_LIBRARIES} -O3 --pedantic -Wfatal-errors

# gcc src/sample_game_engine_api.c -o build/sample -lm ${API_GRAPHIC_LIBRARIES} -O3 --pedantic -Wfatal-errors
# gcc src/sample_keyboard_events.c -o build/sample -lm ${API_GRAPHIC_LIBRARIES} -O3 --pedantic -Wfatal-errors
gcc src/sample_mouse_events.c -o build/sample -lm ${API_GRAPHIC_LIBRARIES} -O3 --pedantic -Wfatal-errors

echo "Compilation completed."
