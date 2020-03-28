/*
 * The adjacency matrix of a graph G is a matrix A that holds a value true or false
 * in element A[i][j] if there is an arc from node i to node j.
 * At this point, can you use an adjacency matrix to conduct a breadth-first search in a graph G?
 * Can you find connected components? Can you find a spanning tree?
 * TODO: connected components, spanning tree
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "queue.h"

bool bfs(size_t m, bool G[m][m], size_t start, size_t end);

bool G[5][5] = {{false, true, false, false, false},
    {true, false, true, false, false},
    {false, false, true, true, false},
    {false, false, false, false, true},
    {false, false, false, false, false},
};

int main() {
    printf("%s\n", bfs(5, G, 0, 4) ? "true" : "false");
    return 0;
}

bool bfs(size_t m, bool G[m][m], size_t start, size_t end) {
    int colors[m];
    for (size_t i = 0; i < m; ++i)
        colors[i] = 0;
    queue_s* Queue = q_init();

    q_push(Queue, start);
    colors[start] = 1;

    while (!q_isempty(Queue)) {
        size_t curr = q_pop(Queue);
        colors[curr] = 2;
        if (curr == end) {
            q_destroy(Queue);
            return true;
        }

        for (size_t i = 0; i < m; i++)
            if (G[curr][i] && colors[i] == 0) {
                q_push(Queue, i);
                colors[i] = 1;
            }
    }
    q_destroy(Queue);
    return false;
}
