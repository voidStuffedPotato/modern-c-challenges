/*
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
#include <stdbool.h>
#include <stdint.h>

#define BUFSIZE 256

typedef struct blob_t blob_t;
struct blob_t {
    char* buf;
    size_t size;
    size_t maxsize;
    blob_t* next;
    blob_t* prev;
};

static size_t           newline_at(char* buffer, size_t size);
blob_t*                 blob_init(size_t maxsize);
void                    blob_desroy(blob_t* target);
blob_t*                 blob_split(blob_t* target, size_t pos);
blob_t*                 blob_join(blob_t* a, blob_t* b);
static blob_t*          blob_compress(blob_t* target);
blob_t*                 blob_from_lines();
void                    blob_print(blob_t* target);
void                    list_destroy(blob_t* first);

int
main() {
    blob_t* text = 0;
    text = blob_from_lines();
    if (text) {
        blob_print(text);
        list_destroy(text);
    }
    return 0;
}

blob_t *
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

blob_t *
blob_split(blob_t* target, size_t pos) {
    if (pos < target->size) {
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
    } else {
        return 0;
    }
}

blob_t *
blob_join(blob_t* a, blob_t* b) {
    blob_t* new = 0;
    if (a && b && a->next == b && b->prev == a) {
        new = blob_init(a->maxsize + b->maxsize);
        if (new) {
            strncpy(new->buf, a->buf, a->size);
            strncat(new->buf, b->buf, b->size);
            new->size = strlen(new->buf);
            if (a->prev) {
                a->prev->next = new;
                new->prev = a->prev;
            }
            if (b->next) {
                b->next->prev = new;
                new->next = b->next;
            }
            blob_desroy(a);
            blob_desroy(b);
        }
    }
    return new;
}

static size_t
newline_at(char* buffer, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        if (buffer[i] == '\n') {
            return i;
        }
    }
    return SIZE_MAX;
}

static blob_t *
blob_compress(blob_t* target) {
    blob_t* curr = 0;
    if (!target) {
        return target;
    } else {
        curr = target;
        while (curr) {
            bool flag = false;
            while (newline_at(curr->buf, curr->maxsize) == SIZE_MAX && curr->next) {
                if (curr == target) {
                    flag = true;
                }
                curr = blob_join(curr, curr->next);
                if (!curr) {
                    perror("Memory error");
                    exit(1);
                }
                if (flag) {
                    target = curr;
                }
            }
            curr = curr->next;
        }
    }
    return target;
}

blob_t *
blob_from_lines() {
    char buffer[BUFSIZE] = { 0 };
    blob_t* first = 0, *curr = 0, *prev = 0;
    while (fgets(buffer, BUFSIZE, stdin)) {
        curr = blob_init(BUFSIZE);
        if (curr) {
            strncpy(curr->buf, buffer, BUFSIZE);
            curr->size = strlen(curr->buf);
            if (!first) {
                first = curr;
            }
            if (prev) {
                prev->next = curr;
                prev->next->prev = prev;
            }
        }
        prev = curr;
    }
    if (!feof(stdin)) {
        perror("Error reading from stream");
        exit(1);
    }
    first = blob_compress(first);
    return first;
}

void
blob_print(blob_t* target) {
    blob_t* curr = target;
    for (size_t i = 0; curr; ++i) {
        printf("[%zu] %s", i, curr->buf);
        curr = curr->next;
    }
}

void
list_destroy(blob_t* first) {
    blob_t* curr = 0, *next = 0;
    if (first) {
        curr = first;
        while (curr->next) {
            next = curr->next;
            blob_desroy(curr);
            curr = next;
        }
        blob_desroy(curr);
    }
}
