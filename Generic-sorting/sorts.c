/*
 * Can you extend your sorting algorithms (challenge 1) to other sort keys?
 * Can you condense your functions for different sort keys to functions that have the
 * same signature as qsort: that is, receive generic pointers to data, size information,
 * and a comparison function as parameters?
 * Can you extend the performansce comparison of your sorting algorithms to the
 * C library function qsort?
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void            print_arr_double(double* target, size_t length);
void            print_arr_int(int* target, size_t length);
void            merge_sort(void* target, size_t size, size_t left, size_t right, int cmp(void*, void*));
void            merge(void* target, size_t size, size_t left, size_t center, size_t right, int cmp(void*, void*));
void            quick_sort(void* target, size_t size, int left, int right, int cmp(void*, void*));
bool            is_sorted(void* target, size_t size, size_t length, int cmp(void*, void*));
int             partition(void* target, size_t size, int left, int right, int cmp(void*, void*));
int             cmp_int(int*, int*);
int             cmp_double(double*, double*);

int
main() {
    int A[10] = {1488, 8, 228, -1488, 4, 32, 2, [9] = 0, [8] = 2323920,};

    merge_sort(A, sizeof(int), 0, 10, cmp_int);
    puts(is_sorted(A, sizeof(int), 10, cmp_int) ? "Sorted successfully" : "Not sorted");
    print_arr_int(A, 10);

    return 0;
}

int
cmp_double(double* a, double* b) {
    if (*a < *b) {
        return 1;
    } else if (*a > *b) {
        return -1;
    } else {
        return 0;
    }
}

int
cmp_int(int* a, int* b) {
    if (*a < *b) {
        return -1;
    } else if (*a > *b) {
        return 1;
    } else {
        return 0;
    }
}

void
print_arr_double(double* target, size_t length) {
    for (size_t i = 0; i < length; ++i) {
        printf("%f\t", target[i]);
    }
    putchar('\n');
}

void
print_arr_int(int* target, size_t length) {
    for (size_t i = 0; i < length; ++i) {
        printf("%d\t", target[i]);
    }
    putchar('\n');
}

bool
is_sorted(void* target, size_t size, size_t length, int cmp(void*, void*)) {
    for (size_t i = 0; i < (length - 1); ++i) {
        if (cmp(target + i * size, target + (i + 1) * size) < 0) {
            return false;
        }
    }
    return true;
}

void
merge_sort(void* target, size_t size, size_t left, size_t right, int cmp(void*, void*)) {
    if (right - left <= 1)
        return;
    else {
        merge_sort(target, size, left, (left + right) / 2, cmp);
        merge_sort(target, size, (left + right) / 2, right, cmp);
        merge(target, size, left, (left + right) / 2, right, cmp);
    }
}

void
merge(void* target, size_t size, size_t left, size_t center, size_t right, int cmp(void*, void*)) {
    size_t length = right - left;
    void* temp = calloc(length , size);

    for (size_t i = left, j = center, k = 0; k < length; ++k) {
        if (i < center && (j == right || (cmp(target + i * size, target + j * size) >= 0))) {
            memcpy(temp + k * size, target + i * size, size);
            ++i;
        } else if (j < right && (i == center || (cmp(target + i * size, target + j * size) < 0))) {
            memcpy(temp + k * size, target + j * size, size);
            ++j;
        }
    }

    memcpy(target + left * size, temp, length * size);
    free(temp);
}

void
quick_sort(void* target, size_t size, int left, int right, int cmp(void*, void*)) {
    if (right <= left)
        return;
    else {
        int center = partition(target, size, left, right, cmp);
        quick_sort(target, size, left, center, cmp);
        quick_sort(target, size, center + 1, right, cmp);
    }
}

int
partition(void* target, size_t size, int left, int right, int cmp(void*, void*)) {
    void* pivot = malloc(size);
    pivot = memcpy(pivot, target + size * (right - 1), size);
    int i = left - 1;

    for (int j = left; j <= right - 2; ++j) {
        if (cmp(target + j * size, pivot) > 0) {
            ++i;
            void* tmp = malloc(size);
            tmp = memcpy(tmp, (target + i * size), size);
            memcpy(target + i * size, target + j * size, size);
            memcpy(target + j * size, tmp, size);
            free(tmp);
        }
    }

    void* tmp = malloc(size);
    tmp = memcpy(tmp, (target + (right - 1) * size), size);
    memcpy(target + (right - 1) * size, (target + (i + 1) * size), size);
    memcpy(target + (i + 1) * size, tmp, size);
    free(tmp);
    free(pivot);
    return i + 1;
}
