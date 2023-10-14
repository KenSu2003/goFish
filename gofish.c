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

    printf("Computer's Cards\n");
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
  char request[2];
  getHand(target);

  // Determine which player is playing
  if(target == &user){
    opponent = &computer;
    printf("User's turn\n");
    
    // Let user choose a card from the opponent
    request[0] = user_play(target);

    // Transfer cards from opponent to player
    int error = transfer_cards(opponent, target, request[0]);
    if(error<0){
      printf("Error: Card not transfered correctly.\n");
    } else if (error == 0){
      printf("No card(s) found.\n");
      
      // if card not found in opponent GOFISH
      struct card* top_card = next_card();
      printf("Card Added: ");
      printf("Rank: %s\t", top_card->rank);
      printf("Suit: %c\n", top_card->suit);
      add_card(target, top_card);       
    } else {
      printf("%d card(s) transfered.\n",error);
    }

  } else {
    opponent = &user;
    printf("Computer's turn\n");
  }  
  // Show player's updated hand
  printf("Player's Hand\n");
  getHand(target);

  /* Check if the Player has won */
  // char added[1] = check_add_book(target);       // Check for a full book
  // game_over(target);
  

}