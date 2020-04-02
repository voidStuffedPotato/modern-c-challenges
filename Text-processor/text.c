/**
 * For a text processor, can you use a doubly linked list to store text?
 * The idea is to represent a "blob" of text through a struct that contains a string (for the text) and
 * and pointers to preceding and following blobs.
 * Can you build a function that splits a text blob in two at a given point?
 * One that runs through the entire text and puts it in the form of one blob per line?
 * Can you create a function that prints the entire text or prints until the text
 * is cut off due to the screen size?
 */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

typedef struct blob_t blob_t;
struct blob_t {
    char* buf;
    size_t size;
    size_t maxsize;
    blob_t* next;
    blob_t* prev;
};

blob_t*                 blob_init(size_t maxsize);
void                    blob_desroy(blob_t* target);
blob_t*                 blob_split(blob_t* target, size_t pos);
blob_t*                 blob_join(blob_t* a, blob_t* b);
blob_t*                 blob_from_lines(char* const text);
void                    blob_print(blob_t* target);


blob_t*
blob_init(size_t maxsize) {
    blob_t* ret_val = malloc(sizeof(blob_t));
    ret_val->buf = malloc(sizeof(char) * maxsize);
    ret_val->maxsize = maxsize;
    ret_val->size = 0;
    ret_val->next = 0;
    ret_val->prev = 0;
    return ret_val;
}

void
blob_desroy(blob_t* target) {
    free(target->buf);
    target->buf = 0;
    target->size = 0;
    target->maxsize = 0;
    target->next = 0;
    target->prev = 0;
    free(target);
}

blob_t*
blob_split(blob_t* target, size_t pos) {
    blob_t* new = blob_init(target->maxsize);
    if (new) {
        new->prev = target;
        if (target->next) {
            blob_t* tmp = target->next;
            target->next->prev = new;
            new->next = tmp;
        }
        target->next = new;
        strncpy(new->buf, (target->buf) + pos, (new->maxsize) - 1);
        new->buf[new->maxsize - 1] = 0;
        target->buf[pos] = 0;
    }
    return new;
}

blob_t*
blob_join(blob_t* a, blob_t* b) {
    blob_t* new =0;
    if (a && b){
        new = blob_init(a->maxsize + b->maxsize);
        strncpy(new->buf, a->buf, a->size);
        strncat(new->buf, b->buf, b->size);
        new->size = (a->size + b->size) < strlen(new->buf) ? strlen(new->buf) : ((a->size + b->size));
    } 
    return new;
}
