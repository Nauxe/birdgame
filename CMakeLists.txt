cmake_minimum_required(VERSION 3.30)
project(birdgame)

# Make sure that SDL3 packages are available
find_package(SDL3 REQUIRED) # Find the SDL3 package
find_package(SDL3_image REQUIRED) # Find the SDL3_image package
find_package(SDL3_ttf REQUIRED) # Find the SDL3_ttf package

# Set the output directory for built objects.
include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
  ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
  ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
  ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

# Enable compile command export
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# defines targets and sources
add_subdirectory(birdgame)

# Add asan
add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)
