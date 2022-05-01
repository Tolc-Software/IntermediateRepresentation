cmake_minimum_required(VERSION 3.15...3.16)

project(
  IR
  VERSION 0.15.1
  LANGUAGES CXX)

configure_file(docs/ReleaseNotes/version.in
               ${CMAKE_CURRENT_LIST_DIR}/docs/ReleaseNotes/version @ONLY)

# The IR specification
add_library(IR INTERFACE)
target_include_directories(
  IR INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
               $<INSTALL_INTERFACE:include>)

set_target_properties(IR PROPERTIES PUBLIC_HEADER
                                    ${CMAKE_CURRENT_LIST_DIR}/include/IR/ir.hpp)

target_compile_features(IR INTERFACE cxx_std_17)

add_library(IR::IR ALIAS IR)

# Only build tests and benchmarks if building this project directly
if(PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  option(ENABLE_PACKAGING "Enables install and packaging via CPack" OFF)
  if(ENABLE_PACKAGING)
    add_subdirectory(tools/packaging)
  endif()
endif()
