#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <malloc.h>
#include "queue.h"

size_t
q_pop(queue_t* queue) {
    if (queue && queue->length > 0) {
        size_t last = (queue->start + queue->length - 1) % MAX_LENGTH;
        queue->length -= 1;
        return queue->buf[last];
    }
    return SIZE_MAX;
}

size_t
q_push(queue_t* queue, size_t x) {
    if (!queue || queue->length == MAX_LENGTH)
        return SIZE_MAX;
    queue->start = (queue->start - 1) % MAX_LENGTH;
    queue->length += 1;
    queue->buf[queue->start] = x;
    return 0;
}

size_t
q_peek(queue_t* queue) {
    if (!queue)
        return SIZE_MAX;
    if (queue->length) {
        return queue->buf[(queue->start + queue->length - 1) % MAX_LENGTH];
    }
    return SIZE_MAX;
}

void
q_print(queue_t* queue) {
    if (queue) {
    size_t last = (queue->start + queue->length) % MAX_LENGTH;
    for (size_t i = queue->start; i != last; i = (i + 1) % MAX_LENGTH)
        printf("%zu\t", queue->buf[i]);
    puts("");
    }
}

bool
q_isempty(queue_t* queue) {
    if (queue)
        return (!(queue->length));
    else
        return true;
}

bool
q_has(queue_t* queue, size_t x) {
    if (queue) {
    size_t last = (queue->start + queue->length) % MAX_LENGTH;
    for (size_t i = queue->start; i != last; i = (i + 1) % MAX_LENGTH)
        if (queue->buf[i] == x)
            return true;
    }
    return false;
}

queue_t *
q_init() {
    queue_t* ret = calloc(1, sizeof(queue_t));
    return ret;
}

queue_t *
q_destroy(queue_t* queue) {
    free(queue);
    queue = 0;
    return 0;
}
