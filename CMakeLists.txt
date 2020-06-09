cmake_minimum_required(VERSION 3.15...3.16)

project(
  IR
  VERSION 0.10
  LANGUAGES CXX)

# The IR specification
add_library(IR INTERFACE)
target_include_directories(
  IR INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
               $<INSTALL_INTERFACE:include>)

target_compile_features(IR INTERFACE cxx_std_17)

add_library(IR::IR ALIAS IR)
