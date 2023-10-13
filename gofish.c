#include <stdio.h>
#include <stdlib.h>
#include "gofish.h"
#include "player.h"
#include "deck.h"
#include <stdbool.h>
#include <string.h>


struct player user;
struct player computer;

int game_state = 1;


void getHand(struct player* target);
void player_turn(struct player* target);

int main(int args, char* argv[]) 
{

  while(game_state){

    /* Initizlize Game */
    int player_wins = 0;
    int computer_wins = 0;

    /* Start Game */
    
    // 1. shuffle deck
    shuffle();

    // 2. deal cards
    printf("Dealing players cards\n");
    deal_player_cards(&user);
    deal_player_cards(&computer);

    // 3. play game
    printf("Game Starting\n");
    player_turn(&user);

    game_state = 0;
  }

}


void getHand(struct player* target){
  
  struct hand* iterator = target->card_list;

  // if hand is empty
  if (iterator == NULL) {
    printf("Player has an empty hand.\n");
  }       
  
  // if hand is not empty
  int card_number = 1;
  while (iterator != NULL){

    // print the current card
    if(iterator->top.rank[0] != 'T'){
    // if(strcmp(iterator->top.rank, "T") != 0){
      printf("%d) ",card_number);
      printf("Rank: %s\t", iterator->top.rank);
      printf("Suit: %c\n", iterator->top.suit);
      card_number++;
    } else if(iterator->top.rank[0] == 'T'){
      printf("%d) ",card_number);
      printf("Rank: 10\t");
      printf("Suit: %c\n", iterator->top.suit);
      card_number++;
    }

    // move to next card
    iterator = iterator->next;

  }
}

void player_turn(struct player* target){
  printf("Player 1's hand\n");
  while(1){
    getHand(&user);
  }
}
