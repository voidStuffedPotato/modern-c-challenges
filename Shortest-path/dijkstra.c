/*
 * Extend the idea of an adjecency matrix of a graph G to a distance matrix D
 * that holds the distance whem going from point i to point j.
 * Mark the absence of a direct arc with a very large value, such as SIZE_MAX.
 * Can you find the shortest path between two nodes x and y given as input?
 */

#include <stdio.h>
#include <stdint.h>
#include <malloc.h>

enum colors { COLOR_WHITE, COLOR_BLACK, };

void        dijkstra(size_t x, size_t y, size_t m, size_t D[m][m]);
size_t      next_vertex(size_t start, size_t m, size_t labels[m], size_t weights[m]);

size_t D[7][7] = {{SIZE_MAX, SIZE_MAX, SIZE_MAX, 3       , SIZE_MAX, SIZE_MAX, SIZE_MAX, },
                  {SIZE_MAX, SIZE_MAX, 2       , SIZE_MAX, SIZE_MAX, SIZE_MAX, SIZE_MAX, },
                  {SIZE_MAX, SIZE_MAX, SIZE_MAX, 3       , SIZE_MAX, SIZE_MAX, SIZE_MAX, },
                  {SIZE_MAX, SIZE_MAX, SIZE_MAX, SIZE_MAX, 4       , SIZE_MAX, SIZE_MAX, },
                  {SIZE_MAX, SIZE_MAX, SIZE_MAX, SIZE_MAX, SIZE_MAX, 5       , SIZE_MAX, },
                  {SIZE_MAX, SIZE_MAX, SIZE_MAX, SIZE_MAX, SIZE_MAX, SIZE_MAX, SIZE_MAX, },
                  {SIZE_MAX, SIZE_MAX, SIZE_MAX, SIZE_MAX, SIZE_MAX, SIZE_MAX, SIZE_MAX, },
};

int main() {
    dijkstra(0, 5, 7, D);
    return 0;
}

void
dijkstra(size_t x, size_t y, size_t m, size_t D[m][m]) {
    size_t* labels = malloc(sizeof(size_t) * m);
    size_t* weights = malloc(sizeof(size_t) * m);
    size_t* pred = malloc(sizeof(size_t) * m);
    size_t curr = x, hops = 0, *path = 0;

    for (size_t i = 0; i < m; ++i) {
        labels[i] = COLOR_WHITE;
        weights[i] = SIZE_MAX;
        pred[i] = SIZE_MAX;
    }

    weights[x] = 0;

    do {
        for (size_t i = 0; i < m; ++i) {
            if (labels[i] == COLOR_WHITE && D[curr][i] < SIZE_MAX && weights[i] > weights[curr] + D[curr][i]) {
                weights[i] = weights[curr] + D[curr][i];
                pred[i] = curr;
            }
        }
        labels[curr] = COLOR_BLACK;
        curr = next_vertex(x, m, labels, weights);
    } while (curr != x);

    for (curr = y; pred[curr] != SIZE_MAX;) {
        ++hops;
        curr = pred[curr];
    }

    path = malloc(sizeof(size_t) * (hops + 1));

    if (path) {
        for (size_t i = hops, curr = y; pred[curr] != SIZE_MAX;) {
            path[i] = curr;
            --i;
            curr = pred[curr];
        }
    }

    if (!hops) {
        puts("No path found");
    } else {
        for (size_t i = 0; i < hops + 1; ++i) {
            printf("%zu\t", path[i]);
        }
        puts("");
    }

    free(path);
    free(weights);
    free(pred);
    free(labels);
}

size_t
next_vertex(size_t start, size_t m, size_t labels[m], size_t weights[m]) {
    size_t min = SIZE_MAX, vertex = start;

    for (size_t i = 0; i < m; ++i) {
        if ((labels[i] == COLOR_WHITE) && (weights[i] < min) && (i != start)) {
            min = weights[i];
            vertex = i;
        }
    }
    return vertex;
}
