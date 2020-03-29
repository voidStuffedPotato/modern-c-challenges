/*
 * The adjacency matrix of a graph G is a matrix A that holds a value true or false
 * in element A[i][j] if there is an arc from node i to node j.
 * At this point, can you use an adjacency matrix to conduct a breadth-first search in a graph G?
 * Can you find connected components? Can you find a spanning tree?
 * TODO: spanning tree
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "queue.h"

bool bfs(size_t m, bool G[m][m], size_t start, size_t end);
size_t print_conn_comps(size_t m, bool G[m][m]);

bool G[5][5] = {{false, false, false, false, false},
    {false, false, false, false, false},
    {false, false, false, false, false},
    {false, false, false, false, false},
    {false, false, false, false, false},
};

int main() {
    printf("%s\n", bfs(5, G, 0, 4) ? "true" : "false");
    print_conn_comps(5, G);
    return 0;
}

enum node_color {white, grey, black, };

bool bfs(size_t m, bool G[m][m], size_t start, size_t end) {
    int colors[m];
    for (size_t i = 0; i < m; ++i)
        colors[i] = white;
    queue_s* Queue = q_init();

    q_push(Queue, start);
    colors[start] = grey;

    while (!q_isempty(Queue)) {
        size_t curr = q_pop(Queue);
        colors[curr] = black;
        if (curr == end) {
            q_destroy(Queue);
            return true;
        }

        for (size_t i = 0; i < m; i++)
            if (G[curr][i] && colors[i] == white) {
                q_push(Queue, i);
                colors[i] = grey;
            }
    }
    q_destroy(Queue);
    return false;
}

size_t print_conn_comps(size_t m, bool G[m][m]) {
    queue_s* comps[m];
    int colors[m];
    size_t num_comps = 0;
    for (size_t i = 0; i < m; ++i) {
        comps[i] = 0;
        colors[i] = white;
    }

    for (size_t root = 0; root < m; ++root) {
        if (colors[root] == white) {
            bool G_conn[m][m];
            for (size_t i = 0; i < m; i++)
                for (size_t j = 0; j < m; ++j)
                    G_conn[i][j] = false;

            /* DFS for all nodes in current component */

            comps[num_comps] = q_init();
            queue_s* curr_queue = comps[num_comps];
            q_push(curr_queue, root);
            colors[root] = grey;
            while (!q_isempty(curr_queue)) {
                size_t curr = q_pop(curr_queue);
                printf("%zu\n", curr);
                if (curr != SIZE_MAX) {
                    colors[curr] = black;
                    for (size_t i = 0; i < m; ++i)
                        if (G[curr][i]) {
                            if (colors[i] == white)
                                q_push(curr_queue, i);
                            colors[i] = grey;
                            G_conn[curr][i] = true;
                        }
                }
            }

            /* Printing out connected component */

            printf("\n");
            for (size_t i = 0; i < m; i++) {
                for (size_t j = 0; j < m; ++j)
                    printf("%u\t", G_conn[i][j]);
                printf("\n");
            }
            printf("\n");

            ++num_comps;
        }
    }
    for (size_t i = 0; i < num_comps; ++i)
        q_destroy(comps[i]);

    return num_comps;
}
