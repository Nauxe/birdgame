add_library(textures "")

target_sources(textures
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/textures.cpp
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/textures.h
  )
target_include_directories(textures
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )
target_link_libraries(textures PUBLIC SDL3::SDL3 SDL3_image::SDL3_image)

