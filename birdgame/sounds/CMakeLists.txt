add_library(sounds "")

target_sources(sounds
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/sounds.cpp
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/sounds.h
  )
target_include_directories(sounds
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )
target_link_libraries(sounds PUBLIC SDL3::SDL3)

