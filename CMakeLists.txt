cmake_minimum_required(VERSION 3.30)
project(birdgame)

# SDL3, SDL3_image, and SDL3_ttf development libraries are required for compilation

# You can pass the SDL3 location to CMake like so: -DSDL3="C:/work/libraries/SDL3-3.2.12"

# Or alternatively, specify the SDL3 location below:
# set(SDL3 "C:/work/libraries/SDL3-3.2.16")
# On macOS, Homebrew was used to install SDL3, SDL3_image, SDL3_ttf, the location may be something like this:
# set(SDL3 "/opt/homebrew/Cellar/sdl3/3.2.16")
# set(SDL3_image "/opt/homebrew/Cellar/sdl3_image/3.2.4")
# set(SDL3_ttf "/opt/homebrew/Cellar/sdl3_ttf/3.2.2")

# Set SDL3 include and library paths for non Windows machines 
if (NOT(WIN32) AND (DEFINED SDL3))
  include_directories(${SDL3}/include)
  link_directories(${SDL3}/lib)
endif()

if (NOT(WIN32) AND (DEFINED SDL3_image))
  include_directories(${SDL3_image}/include)
  link_directories(${SDL3_image}/lib)
endif()

if (NOT(WIN32) AND (DEFINED SDL3_ttf))
  include_directories(${SDL3_ttf}/include)
  link_directories(${SDL3_ttf}/lib)
endif()

# Set SDL3 include and library paths for Windows
if (WIN32)
  # Only do this when not in debug mode
  if (NOT (CMAKE_BUILD_TYPE STREQUAL "Debug"))
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mwindows")
  endif (NOT (CMAKE_BUILD_TYPE STREQUAL "Debug"))

  # If the location of SDL3, SDL3_image, or SDL3_ttf is not specified, we will try to guess it.
  if (NOT(DEFINED SDL3))
    cmake_policy(SET CMP0015 NEW) # suppress warning about relative paths
    set(SDL3 "../../SDL3-3.2.16")
  endif()

  if (NOT(DEFINED SDL3_image))
    cmake_policy(SET CMP0015 NEW) # suppress warning about relative paths
    set(SDL3_image "../../SDL3_image-3.2.4")
  endif()

  if (NOT(DEFINED SDL3_ttf))
    cmake_policy(SET CMP0015 NEW) # suppress warning about relative paths
    set(SDL3_ttf "../../SDL3_ttf-3.2.2")
  endif()

  # Automatically detect whether we need the x86 or x64 version of the SDL3 library.
  if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(SDL3_ARCH "x86_64-w64-mingw32")
  else()
    set(SDL3_ARCH "i686-w64-mingw32")
  endif()

  include_directories(${SDL3}/${SDL3_ARCH}/include)
  link_directories(${SDL3}/${SDL3_ARCH}/lib)

  include_directories(${SDL3_image}/${SDL3_ARCH}/include)
  link_directories(${SDL3_image}/${SDL3_ARCH}/lib)

  include_directories(${SDL3_ttf}/${SDL3_ARCH}/include)
  link_directories(${SDL3_ttf}/${SDL3_ARCH}/lib)
endif()

# Make sure that SDL3 packages are available
find_package(SDL3 REQUIRED) # Find the SDL3 package
find_package(SDL3_image REQUIRED) # Find the SDL3_image package
find_package(SDL3_ttf REQUIRED) # Find the SDL3_image package

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

# Link SDL3 library
target_link_libraries(birdgame PRIVATE SDL3::SDL3 SDL3_image::SDL3_image SDL3_ttf::SDL3_ttf)

# Add asan
add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)
