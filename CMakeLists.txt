cmake_minimum_required(VERSION 3.15)

project(
  IR
  VERSION 0.1
  LANGUAGES CXX)

# Export compile flags to compile_commands.json database. Useful for linters and
# autocompletion
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add custom scripts
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# Define project_warnings and project_options targets
include(WarningsAndOptions)

include(TargetHelpers)

# The IR specification
create_target(
  TARGET
  IR
  IS_INTERFACE
  PUBLIC_INCLUDE
  include
  LINK_LIBRARIES
  project_warnings
  project_options)

add_library(IR::IR ALIAS IR)
