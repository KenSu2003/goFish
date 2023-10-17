#ifndef GOFISH_H
#define GOFISH_H
#include "player.h"  // Include necessary headers

/*
   Print the target's hand
*/
void getHand(struct player* target);

/*
   Run the target's turn
*/
int player_turn(struct player* target);

/*
   Print the target's book
*/
void getBook(struct player* target);

/*
   Give the target a card from the deck.
   If deck is empty return;
*/
void goFish(struct player* target);

/*
   Intitialize the game by resetting the counters, the deck and the players
*/
void initializeGame();

/*
   Start the game by running through the game logics
*/
int startGame();

#endif
