#include "transpose.h"

extern "C" {
    __global__
        void transpose_naive(int *dest, const int *src, const int height, const int width) {
            int x = (blockIdx.x * blockDim.x) + threadIdx.x;
            int y = (blockIdx.y * blockDim.y) + threadIdx.y;

            dest[x*height+y] = src[y*width+x];
        }

    __global__
        void transpose_with_shared_mem(int* dest, const int* src) {
            __shared__ int tmp[TILE_DIM][TILE_DIM+1];
            /* int x = (blockIdx.x * blockDim.x); */
            /* int y = (blockIdx.y * blockDim.x); */

            int width = gridDim.x * TILE_DIM;
            int height = gridDim.y * TILE_DIM;

            int x = (blockIdx.x * blockDim.x) + threadIdx.x;
            int y = (blockIdx.y * blockDim.x);

            for (int i = threadIdx.y; i < blockDim.x; i += blockDim.y) {
                tmp[i][threadIdx.x] = src[(y + i) * width + x];
            }
            __syncthreads();

            x = (blockIdx.x * blockDim.x);
            y = (blockIdx.y * blockDim.x) + threadIdx.x;

            for (int i = threadIdx.y; i < blockDim.x; i += blockDim.y) {
                dest[(x + i) * height + y] = tmp[threadIdx.x][i];
            }
        }
}
