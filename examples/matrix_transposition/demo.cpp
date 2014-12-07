#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <ctime>

#include "cuda.h"

#include "transpose.h"

using namespace std;

void test_001() {
    // int w = 1 << (rand() % 13);
    // int h = 1 << (rand() % 13);

    int w = 1 << 12;
    int h = 1 << 12;

    printf("%d x %d\n", w, h);

    int *a = new int[w*h];
    for (int i = 0; i < w*h; ++i) {
        a[i] = rand();
    }
    int *b = transpose(a, h, w);
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            assert(a[i*w+j] == b [j*h+i]);
        }
    }

    delete[] a;
    delete[] b;
    printf("[ OK ]\n");
}

void test_002() {
    int w = 1 << 6;
    int h = 1 << 5;

    printf("%d x %d\n", w, h);

    int *a = new int[w*h];
    for (int i = 0; i < w*h; ++i) {
        a[i] = i % 32;
    }
    int *b = transpose(a, h, w);
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            printf("%2d ", a[i*w+j]);
        }
        printf("\n");
    }
    printf("\n\n");

    for (int i = 0; i < w; ++i) {
        for (int j = 0; j < h; ++j) {
            printf("%2d ", b[i*h+j]);
        }
        printf("\n");
    }

    delete[] a;
    delete[] b;
    printf("[ OK ]\n");
}

int main(){
    srand(time(NULL));

    /*
     * int *c, *d;
     * int n=32, m=32;
     * c = new int[m*n];
     * for (int j=0; j<n; ++j){
     *     for (int i=0; i<m; ++i){
     *         c[j*m + i] = i%5;
     *     }
     * }
     * d = transpose(c, n, m);
     * for (int j=0; j<m; ++j){
     *     for (int i=0; i<n; ++i){
     *         printf("%d ", d[j*n + i]);
     *     }
     *     printf("\n");
     * }
     * delete [] c;
     * delete [] d;
     */

    for (int i = 0; i < 3; ++i) {
        test_001();
    }
    // test_002();

    return 0;
}
