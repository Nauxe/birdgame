add_executable(birdgame main.cpp)

add_subdirectory(bird)
add_subdirectory(sounds)
add_subdirectory(textures)
add_subdirectory(utils)

target_link_libraries(birdgame
  PRIVATE
    SDL3::SDL3
    SDL3_image::SDL3_image
    SDL3_ttf::SDL3_ttf-static
    bird
    sounds
    textures
    utils
)
