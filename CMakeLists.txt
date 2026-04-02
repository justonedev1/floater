cmake_minimum_required(VERSION 3.31)

project(floater CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options(-Wall -Wextra -Wpedantic)

enable_testing()

include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.13.0 # or a later release
)

FetchContent_MakeAvailable(Catch2)
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)

add_subdirectory(src)
add_subdirectory(tests)

add_executable(floater-exe
  main.cpp
)

target_link_libraries(floater-exe PRIVATE
  floater
)
