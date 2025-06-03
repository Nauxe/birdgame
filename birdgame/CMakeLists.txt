add_executable(birdgame main.cpp)

add_subdirectory(textures)
add_subdirectory(utils)

target_link_libraries(birdgame
  PRIVATE
    textures 
    utils
)
