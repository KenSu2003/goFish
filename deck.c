#include "deck.h"
#include <stdio.h>

/* This part of the code was written by John Works */

struct deck deck_instance;

// This function works as intended
int shuffle(){
    printf("Shuffling deck....\n");
    char suits[] = {'C', 'D', 'H', 'S'};   // valid suits
    char ranks[] = {'2', '3', '4', '5', '6', '7', '8', '9',
    'T', 'J', 'Q', 'K', 'A'};  // T gets converted to 10 when inserted into the deck

    // fill the deck with cards
    for (int i = 0; i < 52; i++){
        deck_instance.list[i].suit = suits[i/13];
        if (i%13 != 8){
        deck_instance.list[i].rank[0] = ranks[i%13];
        deck_instance.list[i].rank[1] = '\0';  // terminate the string
        deck_instance.list[i].rank[2] = '\0';  // terminate the string
        }
        else{
        deck_instance.list[i].rank[0] = '1';
        deck_instance.list[i].rank[1] = '0';
        deck_instance.list[i].rank[2] = '\0';  // terminate the string
        }
    }
    // printf("Inital Deck: \n");
    // for (int k = 0; k < 52; k++){
    // printf("Rank: %s ", deck_instance.list[k].rank);
    // printf("Rank: %c%c ",deck_instance.list[k].rank[0], deck_instance.list[k].rank[1]);
    // printf("Suit: %c\n", deck_instance.list[k].suit);
    // }

    // Go through each card and switch it with a random card from the rest of the cards
    srand(2);   // set a seed for testing.
    for (int i = 51; i > 0; i--){   // 52, 51, 50, ..., 1
        int j = rand() % (i+1);   // random index from 0 to i

        // swap the cards
        struct card temp = deck_instance.list[i];        // set temp = ith card
        deck_instance.list[i] = deck_instance.list[j];   // ith card = jth card
        deck_instance.list[j] = temp;                    // ith card = ith card
    }
    deck_instance.top_card = 51;   // initialize top card to 51
    // printf("After Shuffle: \n");
    // for (int k = 0; k < 52; k++){
    // printf("Rank: %s ", deck_instance.list[k].rank);
    // printf("Suit: %c\n", deck_instance.list[k].suit);
    // }
return 0;
}

// test
int deal_player_cards(struct player* target){
    for (int i = 0; i<7; i++){
        struct card* top_card = next_card();
        // int add_card(struct player* target, struct card* new_card);
        if (top_card == NULL){return -1;}   // check that the deck has been initalized
        add_card(target, top_card);         // add card to player hand (implemented in player.c)
    }
return 0;   // executed successfully
}

// test
struct card* next_card(){
    if (deck_size()==0){   // check that there are cards in the deck
        return NULL;
    }
    struct card* top_card = &(deck_instance.list[deck_instance.top_card]);  // pointer to current top card
	deck_instance.top_card--;  // remove that card from the list
	return top_card;   // pointer to the top card
}

// test 
size_t deck_size(){   // size_t is a typedef int
    if (deck_instance.top_card < 0){
        deck_instance.top_card = 0;   // make sure that the top_card doesn't go out of bounds
    }
    return (size_t) deck_instance.top_card;   // return the current top_card which signifies the number of remaining cards
}