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
#include <malloc.h>
#include "queue.h"

size_t q_pop(queue_s* Queue) {
    if (Queue && Queue->length > 0) {
        size_t last = (Queue->start + Queue->length - 1) % MAX_LENGTH;
        Queue->length -= 1;
        return Queue->buf[last];
    }
    return SIZE_MAX;
}

size_t q_push(queue_s* Queue, size_t x) {
    if (!Queue || Queue->length == MAX_LENGTH)
        return SIZE_MAX;
    Queue->start = (Queue->start - 1) % MAX_LENGTH;
    Queue->length += 1;
    Queue->buf[Queue->start] = x;
    return 0;
}

size_t q_peek(queue_s* Queue) {
    if (!Queue)
        return SIZE_MAX;
    if (Queue->length) {
        return Queue->buf[(Queue->start + Queue->length - 1) % MAX_LENGTH];
    }
    return SIZE_MAX;
}

void q_print(queue_s* Queue) {
    if (Queue) {
    size_t last = (Queue->start + Queue->length) % MAX_LENGTH;
    for (size_t i = Queue->start; i != last; i = (i + 1) % MAX_LENGTH)
        printf("%zu\t", Queue->buf[i]);
    puts("");
    }
}

bool q_isempty(queue_s* Queue) {
    if (Queue)
        return (!(Queue->length));
    else
        return true;
}

bool q_has(queue_s* Queue, size_t x) {
    if (Queue) {
    size_t last = (Queue->start + Queue->length) % MAX_LENGTH;
    for (size_t i = Queue->start; i != last; i = (i + 1) % MAX_LENGTH)
        if (Queue->buf[i] == x)
            return true;
    }
    return false;
}

queue_s* q_init() {
    queue_s* ret = calloc(1, sizeof(queue_s));
    return ret;
}

queue_s* q_destroy(queue_s* Queue) {
    free(Queue);
    Queue = 0;
    return 0;
}
