/*
 * Can you compare the time efficency of your sorting algorithms with data sizes of several
 * orders of magnitude? Be careful to check that you have some randomness in the creation
 * of the data and that the data size does not exceed the available memory of your computer
 * For both algorithms, you should roughly observe a behavior that is proportional to NlogN,
 * where N is the number of elements that are sorted.
 */

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include "sorts.h"

#define RANGE 1024

int*            generate(size_t size);
clock_t         measure(size_t size, size_t n, void f(int*, size_t, size_t));

int
main(int argc, char const * const argv[argc]) {
    size_t size, n;
    srand(time(NULL));
    if (argc > 2 && argv[1] && argv[2]) {
        size = strtoull(argv[1], 0, 0);
        n = strtoull(argv[2], 0, 0);
        clock_t time_q = measure(size, n, quick_sort);
        clock_t time_m = measure(size, n, merge_sort);
        printf("Quick sort: average %ld ms, %zu times, %zu elements\n", time_q, n, size);
        printf("Merge sort: average %ld ms, %zu times, %zu elements\n", time_m, n, size);
    } else {
        puts("Usage: ./performance (Number of elements) (Number of iterations)");
    }
    return 0;
}

clock_t
measure(size_t size, size_t n, void f(int*, size_t, size_t)) {
    int* tmp = 0;
    clock_t now = 0, avg = 0;
    for (size_t iter = 0; iter < n; ++iter) {
        tmp = generate(size);
        if (tmp) {
            now = clock();
            f(tmp, 0, size);
            now = (clock() - now) / (CLOCKS_PER_SEC / 1000);
            free(tmp);
        }
        avg += now;
    }
    if (n)
        avg /= n;
    return avg;
}

int *
generate(size_t size) {
    int* ret_val = malloc(sizeof(int) * size);
    if (ret_val) {
        for (size_t i = 0; i < size; ++i) {
            ret_val[i] = rand() % RANGE;
        }
    }
    return ret_val;
}
