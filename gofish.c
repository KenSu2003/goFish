#include <stdio.h>
#include <stdlib.h>
#include "gofish.h"
#include "player.h"
#include "deck.h"
#include <stdbool.h>
#include <string.h>


struct player user;
struct player computer;

int game_state = 0;
int restart = 1;

void getHand(struct player* target);
int player_turn(struct player* target);
void getBook(struct player* target);

int main(int args, char* argv[]) 
{

  while(game_state==0){

    /* Initizlize Game */
    int player_wins = 0;
    int computer_wins = 0;
    // user.book_index=0;
    // computer.book_index=0;

    /* Start Game */
    
    // 1. shuffle deck
    shuffle();
    printf("\n");
    // 2. deal cards
    // printf("Dealing players cards\n");
    deal_player_cards(&user);
    deal_player_cards(&computer);

    printf("Player 1's Hand - ");
    getHand(&user);
    printf("Player 2's Hand - ");
    getHand(&computer);
    printf("\nPlayer 1's Book - ");
    getBook(&user);
    printf("\nPlayer 2's Book - ");
    getBook(&computer);

    // 3. play game
    printf("\nGame Starting\n");
    game_state = player_turn(&user);
  }
  if(game_state == 1){
    printf("Player has won\n");
  } else if (game_state == 2){
    printf("Computer has won\n");
  }
  printf("Would you like to restart the game?");
}


void getHand(struct player* target){
  
  struct hand* iterator = target->card_list;

  // if hand is empty
  if (iterator == NULL) {
    printf("Player has an empty hand.\n");
  }       
  
  // if hand is not empty
  while (iterator != NULL){

    printf("%s%c ", iterator->top.rank, iterator->top.suit);
    // move to next card
    iterator = iterator->next;

  }
  printf("\n");
}

void getBook(struct player* target){
  printf("Book: ");
  for (int i=0;i<sizeof(target->book);i++){
    printf("%c, ",target->book[i]);
  }
}

int player_turn(struct player* target){
  struct player* opponent;
  char request[2];
  getHand(target);

  // Determine which player is playing
  if(target == &user){
    opponent = &computer;
    printf("User's turn\n");
    // Let user choose a card from the opponent
    request[0] = user_play(target);
  } else {
    opponent = &user;
    printf("Computer's turn\n");
    // Let user choose a card from the opponent
    request[0] = computer_play(target);
  }  

  
  // Transfer cards from opponent to player
  int error = transfer_cards(opponent, target, request[0]);
  if(error<0){
    printf("Error: Card not transfered correctly.\n");
  } else if (error == 0){
    printf("Opponent has no card found.\n");
    // if card not found in opponent GOFISH
    printf("GO FISH\n");
    struct card* top_card = next_card();
    printf("Card Added: ");
    printf("Rank: %s\t", top_card->rank);
    printf("Suit: %c\n", top_card->suit);
    add_card(target, top_card);       
  } else {
    printf("%d card(s) transfered.\n",error);
  }

  // Show player's updated hand
  printf("Player's Hand\n");
  getHand(target);

  /* Check if the Player has won */
  char added;
  added = check_add_book(target);       // Check for a full book
  if(added != '0'){ printf("Book found %c\n",added); }
  int won = game_over(target);
  if(won==1 && opponent==&computer){
    return 1; // user has won
  } else if (won==1 && opponent==&user) {
    return 2; // computer has won
  }
  return 0;
}