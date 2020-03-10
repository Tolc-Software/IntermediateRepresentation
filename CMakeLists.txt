cmake_minimum_required(VERSION 3.15...3.16)

project(
  IR
  VERSION 0.8
  LANGUAGES CXX)

# The IR specification
add_library(IR INTERFACE)
target_include_directories(IR INTERFACE include)

add_library(IR::IR ALIAS IR)
