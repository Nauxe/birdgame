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

