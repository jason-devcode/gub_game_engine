# GUB Game Engine

![z_buffer](./screenshots/image_z_buffer.png)

GUB Game Engine is a powerful and versatile engine designed for the development of game and graphic applications across multiple platforms, including Android, Linux, and Windows. Whether you're building a 2D or 3D game, GUB provides the tools and flexibility you need to bring your projects to life.

## Features

- **Cross-Platform Support**: Develop once, deploy on Android, Linux, and Windows.
- **Customizable Components**: Design custom UI components, inspired by React, for dynamic and interactive game interfaces.
- **Software Rendering**: Pure software rendering engine, with no hardware acceleration required, suitable for projects where control over every pixel is essential.
- **Z-Buffer Implementation**: Efficient depth management for 3D rendering.
- **Event Handling System**: 
  - Utilizes a pattern involving hash tables of lists of nodes.
  - Each node contains a listener that handles events, with functionalities for adding listeners similar to how JavaScript manages events.
  - Includes support for keyboard, mouse, and joystick event handling, providing comprehensive input management for diverse gaming experiences.
- **Extensible Architecture with Facade Pattern**: The engine can be easily extended with other graphic libraries via the facade pattern. This is how it supports both SDL 1 and SDL 2, providing flexibility in choosing or integrating other libraries.

## Getting Started

### Requirements

#### Windows

- **MinGW-w64**: A 64-bit version of the MinGW compiler.
- **SDL 2 Development Libraries** (recommended): Download and install the SDL 2 development dependencies. Place these in the compiler's directory.
  - SDL 2 is recommended as it's easier to download and set up on Windows.

#### Linux

**Debian/Ubuntu**:
- GCC or Clang compiler
- SDL 2 Development Libraries:
  ```bash
  sudo apt-get install libsdl2-dev
  ```

**Arch Linux**:
- GCC or Clang compiler
- SDL 2 Development Libraries:
  ```bash
  sudo pacman -S sdl2
  ```

### Compilation Instructions

#### Windows

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/jason-devcode/gub-game-engine.git
   cd gub-game-engine
   ```

2. **Edit `build.bat`**:
   - Open the `build.bat` file in a text editor.
   - Uncomment the section corresponding to the sample you wish to build.

3. **Run the Build Script**:
   - Double-click on `build.bat` to start the build process.
   - The compiled binaries will be placed in the `build` directory.

4. **SDL Version**:
   - By default, the engine is configured to use SDL 2. If you wish to use SDL 1, you can adjust the build script accordingly, but SDL 2 is recommended for ease of use.

#### Linux

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/jason-devcode/gub-game-engine.git
   cd gub-game-engine
   ```

2. **Build the Engine**:
   - Run the build script:
   ```bash
   ./build.sh
   ```

3. **Run the Engine**:
   ```bash
   ./build/gub_engine
   ```

   - The engine will automatically detect the platform and use the appropriate SDL version. Ensure you have SDL 2 installed as per the requirements.

### Extending the Engine

GUB Game Engine's architecture allows for easy extension with other graphic libraries using the facade pattern. This design pattern abstracts the underlying graphic library, enabling seamless support for SDL 1, SDL 2, and potential future libraries. To integrate a new library, implement the necessary facade interfaces in the engine and adjust the build scripts to include the new library.

### Sample Projects

The engine comes with several sample projects that demonstrate various features:

- **Basic 3D Rendering**: A simple 3D scene with z-buffering.
- **Custom UI Components**: Demonstrates how to create and manage custom UI elements.
- **Event Handling**: Showcases the engine's event management system, utilizing hash tables of lists of nodes with listener functionalities similar to JavaScript, including joystick event handling.

To build a sample, follow the instructions in the `Compilation Instructions` section.

## Documentation

**Documentation of use is coming soon!** Stay tuned for comprehensive guides, tutorials, and API references that will help you make the most of the GUB Game Engine.

## Contributing

We welcome contributions to the GUB Game Engine! If you find a bug or have a feature request, please open an issue. Contributions can be made via pull requests. Please ensure that your code follows the project's coding standards and includes appropriate documentation.

## License

This project is licensed under the MIT License - see the [LICENSE](./LICENSE) file for details.