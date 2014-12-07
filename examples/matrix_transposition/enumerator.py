#!/usr/bin/python3

width = 64
height = 64
TRANSPOSE_GRADIENT = 32

def get_id(k):
    idx = k
    x = (idx // TRANSPOSE_GRADIENT) * TRANSPOSE_GRADIENT % width
    y = (idx % width)
    idx = idx % TRANSPOSE_GRADIENT
    return (x, y, idx)

for i in range(height * width):
    print(i, get_id(i))
