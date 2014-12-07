#ifndef TRANSPOSE_H
#define TRANSPOSE_H

#define NDEBUG

int * transpose(int *matrix, int height, int width);

#ifndef BLOCK_DIM_X
#define BLOCK_DIM_X 32
#endif // BLOCK_DIM_X

#ifndef BLOCK_DIM_Y
#define BLOCK_DIM_Y 32
#endif // BLOCK_DIM_Y

#ifndef TILE_DIM
#define TILE_DIM 32
#endif // TILE_DIM

#endif // TRANSPOSE_H
