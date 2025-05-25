cmake_minimum_required(VERSION 3.30)
project(birdgame)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# Enable compile command export
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set SDL3 include and library paths
include_directories(/opt/homebrew/Cellar/sdl3/3.2.12/include)
link_directories(/opt/homebrew/Cellar/sdl3/3.2.12/lib)

# Set SDL3_image include and library paths
include_directories(/opt/homebrew/Cellar/sdl3_image/3.2.4/include)
link_directories(/opt/homebrew/Cellar/sdl3_image/3.2.4/lib)

# Set SDL3_ttf include and library paths
include_directories(/opt/homebrew/Cellar/sdl3_ttf/3.2.2/include)
link_directories(/opt/homebrew/Cellar/sdl3_ttf/3.2.2/lib)

find_package(SDL3 REQUIRED) # Find the SDL3 package
find_package(SDL3_image REQUIRED) # Find the SDL3_image package
find_package(SDL3_ttf REQUIRED) # Find the SDL3_image package

add_executable(birdgame src/main.cpp)

# Link SDL3 library
target_link_libraries(birdgame PRIVATE SDL3::SDL3 SDL3_image::SDL3_image SDL3_ttf::SDL3_ttf)

# Add asan
add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)
