#ifndef QUEUE
#define QUEUE

#define MAX_LENGTH 256

typedef struct queue_s queue_s;
struct queue_s {
    size_t buf[MAX_LENGTH];
    size_t start;
    size_t length;
};
size_t q_pop(queue_s* Queue);
size_t q_push(queue_s* Queue, size_t x);
size_t q_peek(queue_s* Queue);
queue_s* q_init();
queue_s* q_destroy(queue_s* Queue);
bool q_isempty(queue_s* Queue);
bool q_has(queue_s* Queue, size_t x);
void q_print(queue_s* Queue);
#endif
