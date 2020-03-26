#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

size_t Find(size_t parent[static 1], size_t target);
void FindReplace(size_t parent[static 1], size_t target_pos, size_t value);
size_t FindCompress(size_t parent[static 1], size_t target_pos);
void MakeSingleton(size_t parent[static 1], size_t size);
size_t Union(size_t parent[static 1], size_t a, size_t b);
void Show(size_t parent[static 1], size_t size);

int main() {
  size_t parent[SIZE] = {0};
  MakeSingleton(parent, SIZE);
  for (size_t i = 1; i < SIZE; ++i) {
    parent[i] = i - 1;
  }
  Show(parent, SIZE);
  FindReplace(parent, SIZE - 1, 0);
  Show(parent, SIZE);
  return EXIT_SUCCESS;
}

void MakeSingleton(size_t parent[static 1], size_t size) {
  for (size_t i = 0; i < size; ++i)
    parent[i] = SIZE_MAX;
}

size_t Find(size_t parent[static 1], size_t target) {
  size_t curr = target;
  while (parent[curr] != SIZE_MAX)
    curr = parent[curr];
  return curr;
}

void FindReplace(size_t parent[static 1], size_t target_pos, size_t value) {
  size_t curr = target_pos, tmp = target_pos;
  while (parent[curr] != SIZE_MAX) {
    tmp = curr;
    curr = parent[curr];
    parent[tmp] = value;
  }
  if (curr != value)
    parent[curr] = value;
}

size_t FindCompress(size_t parent[static 1], size_t target_pos) {
  size_t curr = target_pos, tmp = target_pos;
  size_t root = Find(parent, target_pos);
  while (parent[curr] != SIZE_MAX) {
    tmp = curr;
    curr = parent[curr];
    parent[tmp] = root;
  }
  return root;
}

size_t Union(size_t parent[static 1], size_t a, size_t b) {
  size_t root = FindCompress(parent, a);
  FindReplace(parent, b, root);
  return root;
}

void Show(size_t parent[static 1], size_t size) {
  for (size_t i = 1; i < size; ++i) {
    printf("%zu -> %zu root = %zu\n", i, parent[i], Find(parent, i));
  }
}
