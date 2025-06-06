add_executable(birdgame main.cpp)

add_subdirectory(bird)
add_subdirectory(textures)
add_subdirectory(utils)

target_link_libraries(birdgame
  PRIVATE
    bird
    textures 
    utils
)
