@echo off

if not exist "build" (
    mkdir "build"
)

@REM gcc src/sample_game_engine_api.c -o build/sample.exe -D USE_SDL_2 -D SDL_MAIN_HANDLED -lSDL2 -O3 --pedantic -Wfatal-errors
@REM gcc src/sample_keyboard_events.c -o build/sample.exe -D USE_SDL_2 -D SDL_MAIN_HANDLED -lSDL2 -O3 --pedantic -Wfatal-errors
gcc src/sample_mouse_events.c -o build/sample.exe -D USE_SDL_2 -D SDL_MAIN_HANDLED -lSDL2 -O3 --pedantic -Wfatal-errors
pause