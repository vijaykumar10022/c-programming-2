#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"

//struct _one_count_t {
//    char *value;
//    unsigned counts;
//};
//typedef struct _one_count_t one_count_t;
//
//struct _counts_t {
//    one_count_t **array;
//    size_t sz;
//    unsigned unknowns;
//}

one_count_t *createOCPtr(const char *name) {
    one_count_t *ret_ptr = malloc(sizeof(*ret_ptr));
    ret_ptr->value = NULL;
    int len = strlen(name);
    ret_ptr->value = realloc(ret_ptr->value,((size_t)len + 1)*sizeof(*(ret_ptr->value)));
    strcpy(ret_ptr->value, name);
    ret_ptr->counts = 1;
    return ret_ptr;
}

counts_t * createCounts(void) {
    counts_t *counts_ptr = malloc(sizeof(*counts_ptr));
    counts_ptr->unknowns = 0;
    counts_ptr->sz = 0;
    counts_ptr->array = NULL;
    return counts_ptr;
}

void addCount(counts_t * c, const char * name) {
    int find_flag = 0;
    if (name == NULL) {
        c->unknowns++;
    }
    else {
        for (size_t i = 0; i < c->sz; i++) {
            if (strcmp(name, (c->array[i])->value) == 0) {
                (c->array[i])->counts++;
                find_flag = 1;
                break;
            }
        }
        if (find_flag == 0) {
            c->array = realloc(c->array, (c->sz+1)*sizeof(*(c->array)));
            c->array[c->sz] = createOCPtr(name);
            c->sz++;
        }
    }
}
void printCounts(counts_t * c, FILE * outFile) {
    for (size_t i = 0; i < c->sz; i++) {
        fprintf(outFile, "%s: %d\n", c->array[i]->value, c->array[i]->counts);
    }
    if (c->unknowns > 0) {
        fprintf(outFile, "<unknown> : %d\n", c->unknowns);
    }
}

void freeCounts(counts_t * c) {
    for (size_t i = 0; i < c->sz; i++) {
        free(c->array[i]->value);
        free(c->array[i]);
    }
    free(c->array);
    free(c);
}
