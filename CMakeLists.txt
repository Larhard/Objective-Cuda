cmake_minimum_required(VERSION 2.8)

project(Objective-Cuda)

find_package(CUDA REQUIRED)

set(CUDA_HOST_COMPILER ${CMAKE_C_COMPILER})

include(CMakeLocal.txt OPTIONAL)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CUDA_GENERATED_OUTPUT_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_definitions(-DCUDA_PTX_PREFIX="cuda_compile_ptx_generated_")
# TODO should be cleaner solution

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${CUDA_TOOLKIT_INCLUDE})

add_subdirectory(src)
add_subdirectory(examples)
