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

#define MAX_LENGTH 256

bool bfs(size_t m, bool G[m][m], size_t start, size_t end);
size_t q_pop();
size_t q_push(size_t x);
size_t q_peek();
bool q_isempty();
bool q_has(size_t x);
void q_print();

typedef struct queue queue;
struct queue {
    size_t buf[MAX_LENGTH];
    size_t start;
    size_t length;
};

static queue Queue;

bool G[5][5] = {{false, true, false, false, false},
                {false, false, false, false, false},
                {false, false, false, true, false},
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

    q_push(start);
    colors[start] = 1;

    while (!q_isempty()) {
        size_t curr = q_pop();
        colors[curr] = 2;
        if (curr == end)
            return true;

        for (size_t i = 0; i < m; i++)
            if (G[curr][i] && colors[i] == 0)
                q_push(i);
    }
    return false;
}

size_t q_pop() {
    if (Queue.length > 0) {
        size_t last = (Queue.start + Queue.length - 1) % MAX_LENGTH;
        Queue.length -= 1;
        return Queue.buf[last];
    }
    return SIZE_MAX;
}

size_t q_push(size_t x) {
    if (Queue.length == MAX_LENGTH)
        return SIZE_MAX;
    Queue.start = (Queue.start - 1) % MAX_LENGTH;
    Queue.length += 1;
    Queue.buf[Queue.start] = x;
    return 0;
}

size_t q_peek() {
    if (Queue.length) {
        return Queue.buf[(Queue.start + Queue.length - 1) % MAX_LENGTH];
    }
    return SIZE_MAX;
}

void q_print() {
    size_t last = (Queue.start + Queue.length) % MAX_LENGTH;
    for (size_t i = Queue.start; i != last; i = (i + 1) % MAX_LENGTH)
        printf("%zu\t", Queue.buf[i]);
    puts("");
}

bool q_isempty() {
    return (!Queue.length);
}

bool q_has(size_t x) {
    size_t last = (Queue.start + Queue.length) % MAX_LENGTH;
    for (size_t i = Queue.start; i != last; i = (i + 1) % MAX_LENGTH)
        if (Queue.buf[i] == x)
            return true;
    return false;
}
