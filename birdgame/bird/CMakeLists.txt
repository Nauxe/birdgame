add_library(bird "")

target_sources(bird
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/bird.cpp
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/bird.h
  )
target_include_directories(bird
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )
