cmake_minimum_required(VERSION 3.15)

project(IR VERSION 0.1 LANGUAGES CXX)

# Export compile flags to compile_commands.json database. Useful for linters and
# autocompletion
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Use ccache if available
find_program(CCACHE ccache)
if(CCACHE)
  set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE})
endif()

# If no build type is provided explicitly, set it to Release
if(NOT EXISTS ${CMAKE_BINARY_DIR}/CMakeCache.txt)
  if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
  endif()
endif()

# Add custom scripts
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# Define project_warnings and project_options targets
include(WarningsAndOptions)

# Define get_conan_helper
include(SetupConan)
get_conan_helper()
# Require that conan is installed
conan_check(REQUIRED)
conan_setup_remotes()
# Install dependencies (defined in conanfile.{txt,py})
conan_cmake_run(CONANFILE
                conanfile.txt
                BASIC_SETUP
                CONAN_COMMAND
                ${CONAN_CMD}
                CMAKE_TARGETS
                BUILD
                missing)


# Needed when using conanfile.txt and find_package.
# Relies on cmake_paths generator
include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

include(TargetHelpers)

# The IR specification
create_target(TARGET
              IR
              IS_INTERFACE
              PUBLIC_INCLUDE
              include
              LINK_LIBRARIES
              project_warnings
              project_options)

# Common helpers
create_target(TARGET
              IRHelpers
              IS_LIBRARY
              SOURCES
              src/helpers.cpp
              LINK_LIBRARIES
              IR
              project_warnings
              project_options)


# Only build tests and benchmarks if building this project directly
if(PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  option(ENABLE_TESTING "Build the testing tree" OFF)
  if(ENABLE_TESTING)
    # enable_testing()
    # add_subdirectory(tests)
    # TODO: Add benchmarks
  endif()

  option(ENABLE_BENCHMARKS "Build the benchmarks" OFF)
  if(ENABLE_BENCHMARKS)
    # TODO: Add benchmarks
  endif()
endif()
