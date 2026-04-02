add_library(floater INTERFACE)


target_sources(floater INTERFACE
  floater/bit_representation.hpp
)

target_include_directories(floater INTERFACE
  ${CMAKE_CURRENT_SOURCE_DIR}
)
