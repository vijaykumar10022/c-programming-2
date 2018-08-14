#include "eval.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int card_ptr_comp(const void * vp1, const void * vp2) {
    const card_t * const * cp1 = vp1;
    const card_t * const * cp2 = vp2;
    if ((**cp1).value > (**cp2).value) {
        return -1;
    }
    else if ((**cp1).value < (**cp2).value) {
        return 1;
    }
    else {
        if ((**cp1).suit > (**cp2).suit) {
            return -1;
        }
        else if ((**cp1).suit < (**cp2).suit) {
            return 1;
        }
        else {
            return 0;
        }
    }
}

suit_t flush_suit(deck_t * hand) {
    int size = (int)(hand -> n_cards);
    card_t ** card_ptr = (hand -> cards);
    int count_array[] = {0, 0, 0, 0, 0};
    for (int i = 0; i < size; i++) {
       card_t card = **card_ptr;
       (*(count_array + card.suit))++;
       card_ptr++;
    }
    for (int j = 0; j < 4; j++) {
        if (*(count_array + j) > 4) {
            return j;
        }
    }
    return NUM_SUITS;
}

unsigned get_largest_element(unsigned * arr, size_t n) {
    unsigned max_val = 0;
    for (int i = 0; i < (int)n; i++) {
        if (*arr > max_val) {
            max_val = *arr;
        }
        arr++;
    }
    return max_val;
}

size_t get_match_index(unsigned * match_counts, size_t n, unsigned n_of_akind){
    for (size_t i = 0; i < n; i++) {
        if (*match_counts == n_of_akind) {
            return i;
        }
        match_counts++;
    }
    return -1;
}

ssize_t  find_secondary_pair(deck_t * hand,
			     unsigned * match_counts,
			     size_t match_idx) {
    size_t first = -1;
    size_t second = -1;
//    card_t ** cards_ptr = hand -> cards;
    size_t size = hand -> n_cards;
//    size_t indx_pre = get_match_index(match_counts, match_idx + 1, 2);
    unsigned match_val = *(match_counts + match_idx);
    if (match_idx > 0) {
        first = get_match_index(match_counts, match_idx, 2);
    }
    
    if (match_idx + (size_t)match_val < size){
        second = get_match_index((match_counts + (unsigned)match_idx +  match_val), size - match_idx - match_val, 2);
    }
    if (second != -1) {
        second = second + match_idx + (size_t)match_val;
    }
    if (first != -1) {
        return first;
    }
    return second;
    
    //char match_val = value_letter(**(cards_ptr + match_idx));
    //char compr_val = value_letter(**(cards_ptr + match_idx + 2));

    //if (match_val == compr_val) {
    //    size_t indx_pos = get_match_index(match_counts + match_idx + 3, size - match_idx - 3, 2);
    //    if (indx_pos != -1) {
    //        return indx_pos;
    //    }
    //}
    //else {
    //    size_t indx_pos = get_match_index(match_counts + match_idx + 2, size - match_idx - 2, 2);
    //    if (indx_pos != -1) {
    //        return indx_pos;
    //    }
    //}
    //return -1;

}

int is_n_length_staright_at(deck_t * hand, size_t index, suit_t fs, int n) {
    card_t ** cards_ptr = hand -> cards;
    size_t size = hand -> n_cards;
    
    if (fs != NUM_SUITS && (*(cards_ptr + index)) -> suit != fs) {
        return EXIT_FAILURE;
    } 
    unsigned last_val = (**(cards_ptr + index)).value;
    unsigned cur_val = last_val;
    suit_t cur_suit = (**(cards_ptr + index)).suit;
    
    int mach = 1;
    if (index == size -1 && n != 1) {
        return EXIT_FAILURE;
    }
    for (size_t i = index + 1; i < size; i++) {
        cur_val = (**(cards_ptr + i)).value;
        cur_suit = (**(cards_ptr + i)).suit;
        if (cur_val == last_val - 1) {
            if (fs != NUM_SUITS) {
                if (cur_suit == fs) {
                    last_val = cur_val;
                    mach++;
                }
            }
            else {
                last_val = cur_val;
                mach++;
            }
            if (mach == n) {
                return EXIT_SUCCESS;
            }
        }
        else if (cur_val < last_val - 1) {
            return EXIT_FAILURE;
        }
    }
    return EXIT_FAILURE;
}

int is_ace_low_straight_at(deck_t * hand, size_t index, suit_t fs) {
    card_t ** card_ptr = hand -> cards;
    
    card_t test_card = **card_ptr;
    if ((*(card_ptr + index)) -> value != VALUE_ACE) {
        return EXIT_FAILURE;
    }
    if (fs != NUM_SUITS && ((*(card_ptr + index)) -> suit != fs)) {
        return EXIT_FAILURE;
    }
    
    for (size_t i = 0; i < (hand -> n_cards); i++) {
        test_card = **(card_ptr + i);
        if (test_card.value == 5) {
            if (fs != NUM_SUITS) {
                if (test_card.suit == fs) {
                    return is_n_length_staright_at(hand, i, fs, 4);
                }
            }
            else {
                return is_n_length_staright_at(hand, i, fs, 4);
            }
        }
    }
    return EXIT_FAILURE;


//    card_t want_ace;
//    want_ace.suit = fs;
//    want_ace.value = 14;
//    int cond = 0;
//    if ((**(card_ptr + index)).value == 5) {
//        cond = is_n_length_staright_at(hand, index, fs, 4);
//        if (fs != NUM_SUITS) {
//            if (cond == EXIT_SUCCESS && deck_contains(hand, want_ace)){
//                return EXIT_SUCCESS;
//            }
//        }
//        else {
//            if (cond == EXIT_SUCCESS && (**card_ptr).value == 14) {
//                return EXIT_SUCCESS;
//            }
//        }
//    }
//    return EXIT_FAILURE;
}

int is_straight_at(deck_t * hand, size_t index, suit_t fs) {
    int ace_low_cond = is_ace_low_straight_at(hand, index, fs);
    int str_cond = is_n_length_staright_at(hand, index, fs, 5);
    if (str_cond == EXIT_SUCCESS) {
        return 1;
    }
    else if (ace_low_cond == EXIT_SUCCESS) {
        return -1;
    }
    else {
        return 0;
    }
}

//struct hand_eval_tag {
//  hand_ranking_t ranking;
//  card_t *cards[5];
//};
//typedef struct hand_eval_tag hand_eval_t;

hand_eval_t build_hand_from_match(deck_t * hand,
				  unsigned n,
				  hand_ranking_t what,
				  size_t idx) {
    
    hand_eval_t ans;
    ans.ranking = what;
    card_t ** dk_card_ptr = hand -> cards;
    card_t cur_card = **dk_card_ptr;
    unsigned n_k_val = (**(dk_card_ptr + idx)).value;

//    unsigned uidx = (unsigned)idx;
    unsigned delta_ptr = 0;
    
    while (delta_ptr < n) {
        *(ans.cards + delta_ptr) = *(dk_card_ptr + idx + delta_ptr);
        delta_ptr++;
    }


    while (delta_ptr < 5) {
        cur_card = **dk_card_ptr;
        if (cur_card.value != n_k_val) {
            *(ans.cards + delta_ptr) = *(dk_card_ptr);
            delta_ptr++;
        }
        dk_card_ptr++;
    }
    
//    for (unsigned i = 0; i < n; i++) {
//        *(ans.cards + i) = *(dk_card_ptr + uidx + i);
//    }
//    for (unsigned j = 0; j < 5 - n; j++) {
//        if (j < uidx) {
//            delta_ptr = j;
//        }
//        else {
//            delta_ptr = uidx + n + j;
//        }
//        *(ans.cards + n + j) = *(dk_card_ptr + delta_ptr);
//    }
    return ans;
}


int compare_hands(deck_t * hand1, deck_t * hand2) {
    
    size_t hand1_sz = hand1 -> n_cards;
    size_t hand2_sz = hand2 -> n_cards;

    qsort(hand1 -> cards, hand1_sz, sizeof(card_t), card_ptr_comp);
    qsort(hand2 -> cards, hand2_sz, sizeof(card_t), card_ptr_comp);

    hand_eval_t hand1_val = evaluate_hand(hand1); 
    hand_eval_t hand2_val = evaluate_hand(hand2);
    
    card_t ** hand1_ptr = hand1_val.cards;
    card_t ** hand2_ptr = hand2_val.cards;
    
    if (hand1_val.ranking != hand2_val.ranking) {
        if (hand1_val.ranking < hand2_val.ranking) {
            return 1;
        }
        else {
            return -1;
        }
    }
    else {
        unsigned cpr_val1 = (**hand1_ptr).value;
        unsigned cpr_val2 = (**hand2_ptr).value;
        for (int i = 0; i < 5; i++) {
            cpr_val1 = (**(hand1_ptr + i)).value;
            cpr_val2 = (**(hand2_ptr + i)).value;
            if (cpr_val1 > cpr_val2) {
                return 1;
            }
            else if (cpr_val1 < cpr_val2) {
                return -1;
            }
        }
    }
    return 0;
}



//You will write this function in Course 4.
//For now, we leave a prototype (and provide our
//implementation in eval-c4.o) so that the
//other functions we have provided can make
//use of get_match_counts.
unsigned * get_match_counts(deck_t * hand) ;

// We provide the below functions.  You do NOT need to modify them
// In fact, you should not modify them!


//This function copies a straight starting at index "ind" from deck "from".
//This copies "count" cards (typically 5).
//into the card array "to"
//if "fs" is NUM_SUITS, then suits are ignored.
//if "fs" is any other value, a straight flush (of that suit) is copied.
void copy_straight(card_t ** to, deck_t *from, size_t ind, suit_t fs, size_t count) {
  assert(fs == NUM_SUITS || from->cards[ind]->suit == fs);
  unsigned nextv = from->cards[ind]->value;
  size_t to_ind = 0;
  while (count > 0) {
    assert(ind < from->n_cards);
    assert(nextv >= 2);
    assert(to_ind <5);
    if (from->cards[ind]->value == nextv &&
	(fs == NUM_SUITS || from->cards[ind]->suit == fs)){
      to[to_ind] = from->cards[ind];
      to_ind++;
      count--;
      nextv--;
    }
    ind++;
  }
}


//This looks for a straight (or straight flush if "fs" is not NUM_SUITS)
// in "hand".  It calls the student's is_straight_at for each possible
// index to do the work of detecting the straight.
// If one is found, copy_straight is used to copy the cards into
// "ans".
int find_straight(deck_t * hand, suit_t fs, hand_eval_t * ans) {
  if (hand->n_cards < 5){
    return 0;
  }
  for(size_t i = 0; i <= hand->n_cards -5; i++) {
    int x = is_straight_at(hand, i, fs);
    if (x != 0){
      if (x < 0) { //ace low straight
	assert(hand->cards[i]->value == VALUE_ACE &&
	       (fs == NUM_SUITS || hand->cards[i]->suit == fs));
	ans->cards[4] = hand->cards[i];
	size_t cpind = i+1;
	while(hand->cards[cpind]->value != 5 ||
	      !(fs==NUM_SUITS || hand->cards[cpind]->suit ==fs)){
	  cpind++;
	  assert(cpind < hand->n_cards);
	}
	copy_straight(ans->cards, hand, cpind, fs,4) ;
      }
      else {
	copy_straight(ans->cards, hand, i, fs,5);
      }
      return 1;
    }
  }
  return 0;
}


//This function puts all the hand evaluation logic together.
//This function is longer than we generally like to make functions,
//and is thus not so great for readability :(
hand_eval_t evaluate_hand(deck_t * hand) {
  suit_t fs = flush_suit(hand);
  hand_eval_t ans;
  if (fs != NUM_SUITS) {
    if(find_straight(hand, fs, &ans)) {
      ans.ranking = STRAIGHT_FLUSH;
      return ans;
    }
  }
  unsigned * match_counts = get_match_counts(hand);
  unsigned n_of_a_kind = get_largest_element(match_counts, hand->n_cards);
  assert(n_of_a_kind <= 4);
  size_t match_idx = get_match_index(match_counts, hand->n_cards, n_of_a_kind);
  ssize_t other_pair_idx = find_secondary_pair(hand, match_counts, match_idx);
  free(match_counts);
  if (n_of_a_kind == 4) { //4 of a kind
    return build_hand_from_match(hand, 4, FOUR_OF_A_KIND, match_idx);
  }
  else if (n_of_a_kind == 3 && other_pair_idx >= 0) {     //full house
    ans = build_hand_from_match(hand, 3, FULL_HOUSE, match_idx);
    ans.cards[3] = hand->cards[other_pair_idx];
    ans.cards[4] = hand->cards[other_pair_idx+1];
    return ans;
  }
  else if(fs != NUM_SUITS) { //flush
    ans.ranking = FLUSH;
    size_t copy_idx = 0;
    for(size_t i = 0; i < hand->n_cards;i++) {
      if (hand->cards[i]->suit == fs){
	ans.cards[copy_idx] = hand->cards[i];
	copy_idx++;
	if (copy_idx >=5){
	  break;
	}
      }
    }
    return ans;
  }
  else if(find_straight(hand,NUM_SUITS, &ans)) {     //straight
    ans.ranking = STRAIGHT;
    return ans;
  }
  else if (n_of_a_kind == 3) { //3 of a kind
    return build_hand_from_match(hand, 3, THREE_OF_A_KIND, match_idx);
  }
  else if (other_pair_idx >=0) {     //two pair
    assert(n_of_a_kind ==2);
    ans = build_hand_from_match(hand, 2, TWO_PAIR, match_idx);
    ans.cards[2] = hand->cards[other_pair_idx];
    ans.cards[3] = hand->cards[other_pair_idx + 1];
    if (match_idx > 0) {
      ans.cards[4] = hand->cards[0];
    }
    else if (other_pair_idx > 2) {  //if match_idx is 0, first pair is in 01
      //if other_pair_idx > 2, then, e.g. A A K Q Q
      ans.cards[4] = hand->cards[2];
    }
    else {       //e.g., A A K K Q
      ans.cards[4] = hand->cards[4]; 
    }
    return ans;
  }
  else if (n_of_a_kind == 2) {
    return build_hand_from_match(hand, 2, PAIR, match_idx);
  }
  return build_hand_from_match(hand, 0, NOTHING, 0);
}
