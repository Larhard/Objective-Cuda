file(GLOB_RECURSE cufiles *.cu)
cuda_compile_ptx(ptxfiles ${cufiles})

add_executable(matrix_transposition demo.cpp transpose.cpp ${ptxfiles})

target_link_libraries(matrix_transposition objective_cuda cuda)
