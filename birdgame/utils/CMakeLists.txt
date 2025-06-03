add_library(utils "")

target_sources(utils
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/utils.cpp
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/utils.h
  )
target_include_directories(utils
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )
