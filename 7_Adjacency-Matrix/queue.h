#ifndef QUEUE
#define QUEUE

#include <stddef.h>
#include <stdbool.h>

#define MAX_LENGTH 256

typedef struct {
    size_t buf[MAX_LENGTH];
    size_t start;
    size_t length;
} queue_t;

size_t          q_pop(queue_t* Queue);
size_t          q_push(queue_t* Queue, size_t x);
size_t          q_peek(queue_t* Queue);
queue_t *       q_init();
queue_t *       q_destroy(queue_t* Queue);
bool            q_isempty(queue_t* Queue);
bool            q_has(queue_t* Queue, size_t x);
void            q_print(queue_t* Queue);
#endif
