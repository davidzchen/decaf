cmake_minimum_required(VERSION 2.6)
project(decaf)

set(decaf_VERSION_MAJOR 0)
set(decaf_VERSION_MINOR 6)
set(decaf_VERSION_PATCH 0)

include_directories("${PROJECT_SOURCE_DIR}")

# Set CXXFLAGS
#set(CMAKE_CXX_FLAGS "-Werror -Wall")

# Generate CTest input files.
enable_testing()

# Find Packages
find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

add_subdirectory(arch/mips)
add_subdirectory(ast)
add_subdirectory(codegen)
add_subdirectory(decaf)
add_subdirectory(dcc)
