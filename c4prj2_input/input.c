#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"

size_t strToInt(char *str) {
    size_t len = strlen(str);
    size_t res = 0;
    size_t delta = 0;
    for (size_t i = 0; i < len; i++) {
        delta = str[i] - '0';
        for (size_t j = 0; j < len - i - 1; j++) {
            delta = delta*10;
        }
        res = res + delta;
    }
    return res;
}

void lineToStr(char *line) {
    size_t len = strlen(line);
    if (line[len - 1] == '\n') {
        line[len - 1] = '\0';
    }
}


deck_t * hand_from_string(const char * str, future_cards_t * fc) {
    char *c_name = NULL;
    int count = 0;
    int c_count = 0;
    int g_count = 0;
    size_t idx = 0;
    card_t *add_card;
    deck_t *ret_d = (deck_t *)malloc(sizeof(*ret_d));
    ret_d->n_cards = 0;
    ret_d->cards = NULL;
    do {
        if (str[g_count] == ' ' || str[g_count] == '\0') {
            if (c_name != NULL) {
                if (strlen(c_name) < 2) {
                    break;
                }
            }
            count++;
            if (c_name[0] == '?') {
                idx = strToInt(c_name + 1);
                add_card = add_empty_card(ret_d);
                add_future_card(fc, idx, add_card);
                c_count = 0;
            }
            else {
                add_card_to(ret_d, card_from_letters(c_name[0], c_name[1]));
                c_count = 0;
            }
        }
        else {
            c_count++;
            c_name = (char *)realloc(c_name, (c_count + 1)*sizeof(*c_name));
            c_name[c_count - 1] = str[g_count];
            c_name[c_count] = '\0';
        }
        g_count++;
    }
    while (str[g_count - 1] != '\0');

    free(c_name);
    if (count < 5) {
        fprintf(stderr, "Not enough cards");
        return NULL;
    }
    return ret_d;
}

deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc) {
    char *line = NULL;
    size_t n = 0;
    deck_t **ret_ar = NULL;
    while (getline(&line, &n, f) >= 0) {
        ret_ar = (deck_t **)realloc(ret_ar, (*n_hands + 1)*sizeof(*ret_ar));
        lineToStr(line);
        ret_ar[*n_hands] = hand_from_string(line, fc);
        (*n_hands)++;
    }
    free(line);
    return ret_ar;
}
