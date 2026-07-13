# Prerequisites
---
`cmake`, `conan`

The libraries `SDL3`, `SDL3_image`, `SDL3_ttf` are installed via `conan`.

# To build and run: (Navigate into the cloned directory first)
---
### 1. Configure build and install dependencies. 
```bash
conan install . --build=missing
cmake --preset conan-release # Requires cmake>=3.23
```
### 2. Compile
```bash
cmake --build --preset conan-release 
```
### 3. Run executable
For Unix based systems:
```bash
./build/bin/birdgame
```
For Windows:
TODO 

# References and Attributions
---
Visuals made using `Aseprite`.
Sounds made using `Bosca Ceoil: The Blue Album`.
