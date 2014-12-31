#include <cassert>
#include <cstring>
#include <memory>

#include "transpose.h"
#include "objective_cuda.h"

std::auto_ptr<Cuda> cuda;
// Cuda* cuda = NULL;

void gpu_transpose_naive(int *dest, const int *src, int height, int width) {
    assert((width & (width - 1)) == 0);  // TODO
    assert((height & (height - 1)) == 0);

    cuda->set_default_module("transpose.ptx");
    CUfunction transpose_kernel = cuda->get_kernel("transpose_naive");

    int grid_dim_x = width / BLOCK_DIM_X;
    int grid_dim_y = height / BLOCK_DIM_Y;

    CUdeviceptr device_src;
    CUdeviceptr device_dest;
    cuMemAlloc(&device_src, width*height*sizeof(int));
    cuMemAlloc(&device_dest, width*height*sizeof(int));
    cuMemcpyHtoD(device_src, src, width*height*sizeof(int));

    void *args[] = {&device_dest, &device_src, &height, &width};
    cuda->launch_kernel_2d_sync(transpose_kernel,
            grid_dim_x, grid_dim_y,
            BLOCK_DIM_X, BLOCK_DIM_Y,
            args);

    cuMemcpyDtoH(dest, device_dest, width*height*sizeof(int));
    cuMemFree(device_src);
    cuMemFree(device_dest);
    cuda->ctx_synchronize();
}

void gpu_transpose_with_shared_mem(int *dest, const int *src, int height, int width) {
    assert((width & (width - 1)) == 0);  // TODO
    assert((height & (height - 1)) == 0);

    cuda->set_default_module(CUDA_PTX_PREFIX"transpose.cu.ptx");
    CUfunction transpose_kernel = cuda->get_kernel("transpose_with_shared_mem");

    int grid_dim_x = width / TILE_DIM;
    int grid_dim_y = height / TILE_DIM;

    CUdeviceptr device_src;
    CUdeviceptr device_dest;
    cuMemAlloc(&device_src, width*height*sizeof(int));
    cuMemAlloc(&device_dest, width*height*sizeof(int));
    cuMemcpyHtoD(device_src, src, width*height*sizeof(int));

    void *args[] = {&device_dest, &device_src};
    cuda->launch_kernel_2d_sync(transpose_kernel,
            grid_dim_x, grid_dim_y,
            TILE_DIM, 2,
            args);

    cuMemcpyDtoH(dest, device_dest, width*height*sizeof(int));
    cuMemFree(device_src);
    cuMemFree(device_dest);
    cuda->ctx_synchronize();
}

void cpu_transpose(int *dest, int *src, int height, int width) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            dest[j*height+i] = src[i*width+j];
        }
    }
}

int * transpose(int *matrix, int height, int width) {
    if (cuda.get() == NULL) {
        cuda.reset(new Cuda());
    }
    int *result;
    result = new int[height*width];
    if (width >= BLOCK_DIM_X && height >= BLOCK_DIM_X) {
        // gpu_transpose_naive(result, matrix, height, width);
        cuMemHostRegister(result, sizeof(int)*height*width, 0);  // TODO check result value
        gpu_transpose_with_shared_mem(result, matrix, height, width);
        cuMemHostUnregister(result);  // TODO check result value
    } else {
        cpu_transpose(result, matrix, height, width);
    }
    return result;
}
