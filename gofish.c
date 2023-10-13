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

    getHand(&computer);
    // 3. play game
    printf("Game Starting\n");
    player_turn(&user);

    game_state = 0;     // end game
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
  struct player* opponent;
  if(target == &user){
    opponent = &computer;
    printf("User's turn\n");
  } else {
    opponent = &user;
    printf("Computer's turn\n");
  }

  // Show player their card(s)
  getHand(target);

  // Let player choose a card from the opponent
  char request[2];
  printf("Please choose a rank [2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K, A]: ");
  scanf("%s",request);     // limit input to oen character to prevent overflow
  if(strcmp(request,"10") == 0){
    request[0] = 'T'; 
    request[1] = '\0';
  }
  printf("Request = %s\n",request);
  
  if(search(opponent,request[0])==1){
    if(request[0]=='T'){
      printf("Rank 10 found.\n");
    } else {
      printf("Rank %s found.\n",request);
    }

    // transfer cards from opponent to player
    int error = transfer_cards(opponent, target, request[0]);
    if(error<0){
      printf("Error: Card not transfered correctly.\n");
    } else if (error == 0){
      printf("No card(s) found.\n");
    } else {
      printf("%d card(s) transfered.\n",error);
    }

  } else {
    if(request[0]=='T'){
      printf("Rank 10 is not found.\n");
    } else {
      printf("Rank %s is not found.\n",request);
    }
  }

  // Show player's updated hand
  getHand(target);

}