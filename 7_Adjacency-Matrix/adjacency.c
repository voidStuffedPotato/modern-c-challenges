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

enum {COLOR_WHITE, COLOR_GREY, COLOR_BLACK, } node_color_t;

bool            bfs(size_t m, bool G[m][m], size_t start, size_t end);
size_t          get_conn_comps(size_t m, bool G[m][m], bool show);
bool            spanning_tree(size_t m, bool G[m][m]);

bool G[5][5] = {{false, true, false, false, false},
                {false, false, true, false, false},
                {false, false, false, true, false},
                {false, false, false, false, true},
                {true, false, false, false, false},
};

int
main() {
    printf("%s\n", bfs(5, G, 0, 4) ? "true" : "false");
    get_conn_comps(5, G, false);
    spanning_tree(5, G);
    return 0;
}

bool
bfs(size_t m, bool G[m][m], size_t start, size_t end) {
    int colors[m];
    for (size_t i = 0; i < m; ++i)
        colors[i] = COLOR_WHITE;
    queue_t* Queue = q_init();

    q_push(Queue, start);
    colors[start] = COLOR_GREY;

    while (!q_isempty(Queue)) {
        size_t curr = q_pop(Queue);
        colors[curr] = COLOR_BLACK;
        if (curr == end) {
            q_destroy(Queue);
            return true;
        }

        for (size_t i = 0; i < m; i++)
            if (G[curr][i] && colors[i] == COLOR_WHITE) {
                q_push(Queue, i);
                colors[i] = COLOR_GREY;
            }
    }
    q_destroy(Queue);
    return false;
}

size_t
get_conn_comps(size_t m, bool G[m][m], bool show) {
    queue_t* comps[m];
    int colors[m];
    size_t num_comps = 0;

    for (size_t i = 0; i < m; ++i) {
        comps[i] = 0;
        colors[i] = COLOR_WHITE;
    }

    for (size_t root = 0; root < m; ++root) {
        if (colors[root] == COLOR_WHITE) {
            bool G_conn[m][m];
            if (show) {
                for (size_t i = 0; i < m; i++)
                    for (size_t j = 0; j < m; ++j)
                        G_conn[i][j] = false;
            }

            /* DFS for all nodes in current component */

            comps[num_comps] = q_init();
            queue_t* curr_queue = comps[num_comps];
            q_push(curr_queue, root);
            colors[root] = COLOR_GREY;

            while (!q_isempty(curr_queue)) {

                size_t curr = q_pop(curr_queue);
                if (curr != SIZE_MAX) {
                    colors[curr] = COLOR_BLACK;

                    for (size_t i = 0; i < m; ++i) {
                        if (G[curr][i] && colors[i] == COLOR_WHITE) {
                            q_push(curr_queue, i);
                            colors[i] = COLOR_GREY;
                            if (show) {
                                G_conn[curr][i] = true;
                            }
                        }
                    }

                }
            }

            /* Printing out connected component */

            if (show) {
                printf("\n");
                for (size_t i = 0; i < m; i++) {
                    for (size_t j = 0; j < m; ++j)
                        printf("%u\t", G_conn[i][j]);
                    printf("\n");
                }
                printf("\n");
            }

            ++num_comps;
        }
    }
    for (size_t i = 0; i < num_comps; ++i)
        q_destroy(comps[i]);

    return num_comps;
}

bool
spanning_tree(size_t m, bool G[m][m]) {
    if (get_conn_comps(m, G, false) != 1) {
        return false;
    } else {
        return !!get_conn_comps(m, G, true);
    }
}
