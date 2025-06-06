CMakeList scripts based on https://github.com/sun1211/cmake_with_add_subdirectory and https://github.com/NagyD/SDLPoP

# Prerequisites
---
`cmake`,`SDL3`, `SDL3_image`, `SDL3_ttf`

## Windows
Make sure to install the MinGW Development Libraries of SDL3 at: (The `*-mingw.tar.gz` files)
- https://github.com/libsdl-org/SDL/releases/latest
- https://github.com/libsdl-org/SDL_image/releases/latest
- https://github.com/libsdl-org/SDL_ttf/releases/latest

Follow the instructions from INSTALL.md in the files downloaded.


## Unix based
TODO 


# To build and run: (Navigate into the cloned directory first)
---
### 1. Configure build. 
* Set appropriate paths for SDL3 by appending `-DSDL3="[/path/to/SDL3]" -DSDL3_image="[/path/to/SDL3_image]" -DSDL3_ttf="[/path/to/SDL3_ttf]"` to below or modifying `CMakeLists.txt` in the root directory.
```bash
cmake -S . -B build
```
### 2. Compile
```bash
cmake --build build
```
### 3. Run executable
For Unix based systems:
```bash
./build/bin/birdgame
```
For Windows:
TODO 
