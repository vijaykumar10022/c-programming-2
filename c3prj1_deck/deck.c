#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"

//struct deck_tag {
//  card_t ** cards;
//  size_t n_cards;
//};

void pntr_swap(card_t ** pntr1, card_t ** pntr2) {
    card_t * temp = *pntr1;
    *pntr1 = *pntr2;
    *pntr2 = temp;
}

void print_hand(deck_t * hand){
    card_t ** card_pntr = hand -> cards;
    for (int i = 0; i < (hand -> n_cards); i++) {
        print_card(**card_pntr);
        printf("%s", " ");
        card_pntr++;
    }
}

int deck_contains(deck_t * d, card_t c) {
    card_t ** card_pntr = d -> cards;
    for (int i = 0; i < (d -> n_cards); i++) {
        if (suit_letter(**card_pntr) == suit_letter(c) && value_letter(**card_pntr) == value_letter(c)) {
            return 1;
        }
        card_pntr++;
    }
    return 0;
}

void shuffle(deck_t * d){
    card_t ** card_pntr = d -> cards;
    int size = (int)(d -> n_cards);
    for (int i = 0; i < (d -> n_cards); i++) {
        int new_pos = ((int)rand())%size;
        pntr_swap(card_pntr + i, card_pntr + new_pos);
    }
}

void assert_full_deck(deck_t * d) {
    card_t ** card_pntr = d -> cards;
    deck_t temp_deck;
    temp_deck.cards = d -> cards;
    for (int i = 0; i < (d -> n_cards); i++) {
        card_t temp_card = **card_pntr;
        assert_card_valid(temp_card);
        
        if (i > 0) {
            temp_deck.n_cards = (size_t)i;
            assert(!deck_contains(&temp_deck, temp_card));
        }
        card_pntr++;
    } 
}
