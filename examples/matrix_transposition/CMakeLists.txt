add_executable(matrix_transposition demo.cpp transpose.cpp)

target_link_libraries(matrix_transposition objective_cuda cuda)

cuda_compile_ptx(transpose transpose.cu)
