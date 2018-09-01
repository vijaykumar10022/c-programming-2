#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

int findEqSign(char *prob_str) {
    char c = *prob_str;
    int count = 0;

    while (c != '=') {
            count++;
            c = *(prob_str + count);
            if (c == '=') {
                return count;
            }
        }
    return -1;
}

char *getKeyFromStr(char *prob_str) {
    int eq_sign_idx = findEqSign(prob_str);
    if (eq_sign_idx == -1) {
        return NULL;
    }
    char *ret_str = malloc((eq_sign_idx + 1)*sizeof(*ret_str));
    strncpy(ret_str, prob_str, eq_sign_idx + 1);
    ret_str[eq_sign_idx] = '\0';
    return ret_str;
}

char *getValFromStr(char *prob_str) {
    int eq_sign_idx = findEqSign(prob_str);
    if (eq_sign_idx == -1) {
        return NULL;
    }
    char *ret_str = NULL;
    size_t str_len = strlen(prob_str);
    if (prob_str[str_len - 1] != '\n') {
        ret_str = realloc(ret_str, ((int)str_len - eq_sign_idx)*sizeof(*ret_str));
        strcpy(ret_str, (prob_str + eq_sign_idx + 1));
        ret_str[(int)str_len - eq_sign_idx - 1] = '\0';
    }
    else {
        ret_str = realloc(ret_str, ((int)str_len - eq_sign_idx - 1)*sizeof(*ret_str));
        strncpy(ret_str, (prob_str + eq_sign_idx + 1), (int)str_len - eq_sign_idx - 1);
        ret_str[(int)str_len - eq_sign_idx - 2] = '\0';
    }
    return ret_str;
}

kvpair_t *crtKVPairFrStr(char *prob_str) {
    kvpair_t *work_kv = malloc(sizeof(*work_kv));
    work_kv->key = getKeyFromStr(prob_str);
    if (work_kv->key == NULL) {
        return NULL;
    }
    work_kv->value = getValFromStr(prob_str);
    if (work_kv->value == NULL) {
        return NULL;
    }
    return work_kv;

}

kvarray_t * readKVs(const char * filename) {
    FILE * work_file = fopen(filename, "r");

    kvarray_t *ret_arr = malloc(sizeof(*ret_arr));
    ret_arr->array = NULL;
    char *line = NULL;
    size_t size = 0;
    size_t sz = 0;
    if (work_file == NULL) {
        return NULL;
    }
    while ((getline(&line, &size, work_file)) >= 0) {
        ret_arr->array = realloc(ret_arr->array, (sz + 1)*sizeof(ret_arr->array));
        ret_arr->array[sz] = crtKVPairFrStr(line);
        if (ret_arr->array[sz] == NULL) {
            return NULL;
        }
        sz++;
    }
    free(line);
    ret_arr->sz = sz;
    fclose(work_file);
    return ret_arr;
}

void freeKVs(kvarray_t * pairs) {
    size_t sz = pairs->sz;
    for (size_t i = 0; i < sz; i++) {
        free((pairs->array[sz - 1 - i])->value);
        free((pairs->array[sz - 1 - i])->key);
        free(pairs->array[sz - 1 - i]);
    }
    free(pairs->array);
    free(pairs);
}

void printKVs(kvarray_t * pairs) {
    size_t sz = pairs->sz;
    kvpair_t *temp_kvp; 
    for (size_t i = 0; i < sz; i++) {
        temp_kvp = pairs->array[i];
        printf("key = '%s' value = '%s'\n", temp_kvp->key, temp_kvp->value);
    }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
    size_t sz = pairs->sz;
    for (size_t i = 0; i < sz; i++) {
        if (strcmp(key, (pairs->array[i])->key) == 0) {
            return (pairs->array[i])->value;
        }
    }
    return NULL;
}
