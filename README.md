# nnsim

A C++ project using raylib for rendering.

## Prerequisites

- CMake 3.20 or higher
- C++17 compatible compiler
- raylib library

## Building the Project

### macOS

```bash
# Install dependencies (if using Homebrew)
brew install cmake raylib

# Create build directory
mkdir build
cd build

# Configure and build
cmake ..
cmake --build .

# Run the executable
./neurodrive
```

### Windows

```bash
# Install dependencies
# Option 1: Using vcpkg (recommended)
vcpkg install raylib

# Option 2: Download raylib from https://www.raylib.com/

# Create build directory
mkdir build
cd build

# Configure and build (using Visual Studio)
cmake ..
cmake --build . --config Release

# Run the executable
.\Release\neurodrive.exe
```

### Linux

```bash
# Install dependencies (Ubuntu/Debian)
sudo apt-get install cmake libraylib-dev

# Create build directory
mkdir build
cd build

# Configure and build
cmake ..
cmake --build .

# Run the executable
./neurodrive
```

## Project Structure

- `main.cpp` - Main application entry point
- `CMakeLists.txt` - CMake build configuration
- `.gitignore` - Git ignore rules for build artifacts and IDE files

## Contributing

When collaborating on this project:
- Never commit build artifacts (executables, object files, etc.)
- Keep the build directory out of version control
- Test builds on your platform before pushing changes
