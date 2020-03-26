#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void print_arr(int target[static 1], size_t size);
void merge_sort(int target[static 1], size_t left, size_t right);
void merge(int target[static 2], size_t left, size_t center, size_t right);
void quick_sort(int target[static 1], int left, int right);
bool is_sorted(int target[static 1], size_t size);
int partition(int target[static 2], int left, int right);

int main() {

    int array[6] = {
        [0] = 5, [1] = 7, [2] = -24, [3] = 17, [4] = 0, [5] = 1,
    };

    print_arr(array, 6);
    quick_sort(array, 0, 6);
    print_arr(array, 6);

    if (is_sorted(array, 6))
        fputs("Sorting succeded\n", stderr);
    else
        fputs("Sorting failed\n", stderr);

    return EXIT_SUCCESS;
}

void print_arr(int target[static 1], size_t size) {
    for (size_t i = 0; i < size; ++i) {
        printf("%d\t", target[i]);
    }
    putchar('\n');
}

bool is_sorted(int target[static 1], size_t size) {
    for (size_t i = 0; i < size - 1; ++i) {
        if (target[i] > target[i + 1])
            return false;
    }
    return true;
}

void merge_sort(int target[static 1], size_t left, size_t right) {
#if !NDEBUG
    printf("Merge: l=%zu\tr=%zu\n", left, right);
#endif
    if (right - left <= 1)
        return;
    else {
        merge_sort(target, left, (left + right) / 2);
        merge_sort(target, (left + right) / 2, right);
        merge(target, left, (left + right) / 2, right);
    }
}

void merge(int target[static 2], size_t left, size_t center, size_t right) {
    size_t tmpsize = right - left;
    int temp[tmpsize];
    for (size_t i = 0; i < tmpsize; ++i)
        temp[i] = 0;

    for (size_t i = left, j = center, k = 0; k < tmpsize; ++k) {
        if (i < center && (j == right || (target[i] <= target[j]))) {
            temp[k] = target[i];
            ++i;
        } else if (j < right && (i == center || (target[i] > target[j]))) {
            temp[k] = target[j];
            ++j;
        }
    }

    for (size_t k = 0; k < tmpsize; ++k)
        target[left + k] = temp[k];
}

void quick_sort(int target[static 1], int left, int right) {
    if (right <= left)
        return;
    else {
        int center = partition(target, left, right);
        quick_sort(target, left, center);
        quick_sort(target, center + 1, right);
    }
}

int partition(int target[static 2], int left, int right) {
    int pivot = target[right - 1];
    int i = left - 1;
#if !NDEBUG
    printf("l = %d, r = %d\n", left, right);
#endif
    for (int j = left; j <= right - 2; ++j) {
        if (target[j] <= pivot) {
            ++i;
            int tmp = target[i];
            target[i] = target[j];
            target[j] = tmp;
        }
    }
    int tmp = target[right - 1];
    target[right - 1] = target[i + 1];
    target[i + 1] = tmp;
    return i + 1;
}
