/* This section of the code was written by: Ken Su */
#include "player.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/* Need to include for rand and srand */
#include <stdlib.h> 
#include <time.h>

/* Need to include this for NULL */
#include <unistd.h> // https://github.com/microsoft/vscode-cpptools/issues/2607

//int book_index = 0;
int add_card(struct player* target, struct card* new_card){

    /* Allocate space for new element */
    struct hand* next_hand;
    next_hand = (struct hand*)malloc(sizeof(struct hand));
    if (next_hand == NULL) { return -1; }
    
    /* Initialize new element */
    next_hand->top = *new_card;  // next_hand->:payload == (next_hand*).payload
    next_hand->next = target->card_list;
    
    /* Set list to temp, the new front of list*/
    target->card_list = next_hand;

    /* Updated hand_size */
    target->hand_size+=1;

    // printf("/* Add Card */\n");
    // printf("Rank: %s\t", next_hand->top.rank);
    // printf("Suit: %c\n", next_hand->top.suit);
    
    return 0;
}

int remove_card(struct player* target, struct card* old_card){
    
    struct hand* iterator = target->card_list;
    struct hand* previous = NULL;
    if (iterator == NULL) { return 0; }         // reach end of the list

    // while the current card is not old_card move iterator
    while (iterator->top.rank[0] != old_card->rank[0] || iterator->top.suit != old_card->suit) {              
        previous = iterator;
        iterator = iterator->next;
        if (iterator == NULL)                   // if iterator reaches the front
            return 0;
        }
        
        /* Iterator found the last item; break out of loop */
        if (previous != NULL) 
            previous->next = iterator->next;
        else {
            target->card_list = iterator->next;
        }
        
        /* Free memory of item we are removing */
        free(iterator);
        
        /* Updated hand_size */
        target->hand_size-=1;

        /* Return true; we found and removed the item */
        return 1;

};

char check_add_book(struct player* target) {
    if (target->hand_size == 0) {
        return 0; // check if the player has cards to begin with
    }

    struct hand* cards = target->card_list;
    struct hand* previous = NULL;
    while (cards != NULL) {
        struct card tcard = cards->top;   // get current card
        int count = 0;                      // count how many of the cards had been matched
        struct card card_remove[4];
        int index = 0;
        int cardIndex = 0;
        // Iterate through the hand to count matching cards
        struct hand* current = target->card_list;
        while (current != NULL) {
            struct card scard = current->top;
            if (tcard.rank[0] == scard.rank[0]) {
                count++;
                // indexes[index] = cardIndex;
                card_remove[index] = scard;
                index++;
            }
            current = current->next;
            cardIndex++;
        }

        

        // if there are 4 cards with the same rank
        if (count == 4) {
            // add rank to book
            target->book[target->book_index] = tcard.rank[0]; // not for 10
            // remove those cards
            for (int i = 0; i < 4; i++) {
                // printf("card_remove = %c, %s\n",card_remove[i].suit,card_remove[i].rank);
                remove_card(target, &card_remove[i]);
            }

            // increase book index
            target->book_index++;

            //print which card the target got
            if(target==&user){
                printf("\t- Player 1 books %s\n",tcard.rank);
            }else{
                printf("\t- Player 2 books %s\n",tcard.rank);
            }

            return tcard.rank[0];
        }
        previous = cards;
        cards = cards->next;
    }
    return '0';
}

void search_and_print_cards(struct player* src, struct player* dest, char rank){   // returns an array of found cards
    
    if (src->hand_size == 0) {
        return;  // No cards to transfer
    }
    
    // Check for the players (dest) cards
    struct hand* dest_card = dest->card_list;
    struct hand* previousDest = NULL;
    struct card player_cards[4];
    int player_index = 0;

    while (dest_card != NULL) {
        struct card tcard = dest_card->top;
        if (tcard.rank[0] == rank) {
            // add card to the opponents card
            player_cards[player_index] = tcard;
            player_index++;
            // Check next cards
            previousDest = dest_card;
            dest_card = dest_card->next;
        } else {
            // Move to the next card in the linked list
            previousDest = dest_card;
            dest_card = dest_card->next;
        }
    }

    // Check for the opponents (src) cards
    struct hand* src_card = src->card_list;
    struct hand* previousSrc = NULL;
    bool found = false;

    struct card opponent_cards[4];
    int opponent_index = 0;

    while (src_card != NULL) {
        struct card tcard = src_card->top;
        if (tcard.rank[0] == rank) {
            // If card is found, set found to true
            found = true;
            // add card to the opponents card
            opponent_cards[opponent_index] = tcard;
            opponent_index++;
            // Check next cards
            previousSrc = src_card;
            src_card = src_card->next;
        } else {
            // Move to the next card in the linked list
            previousSrc = src_card;
            src_card = src_card->next;
        }
    }

    

    if(found==true){
        if(src==&computer){
            printf("\t - Player 2 has ");
            struct card tcard;
            for(int i=0;i<player_index;i++){
                tcard = player_cards[0];
                printf("%s%c ",tcard.rank,tcard.suit);
            }
            printf("\n");
            printf("\t - Player 1 has ");
            for(int i=0;i<opponent_index;i++){
                tcard = opponent_cards[0];
                printf("%s%c ",tcard.rank,tcard.suit);
            }
            printf("\n");
        } else {
            printf("\t - Player 1 has ");
            struct card tcard;
            for(int i=0;i<player_index;i++){
                tcard = player_cards[0];
                printf("%s%c ",tcard.rank,tcard.suit);
            }
            printf("\n");
            printf("\t - Player 2 has ");
            for(int i=0;i<opponent_index;i++){
                tcard = opponent_cards[0];
                printf("%s%c ",tcard.rank,tcard.suit);
            }
            printf("\n");
        }
        
    }
}
   
int search(struct player* target, char rank){
    struct hand* cards = target->card_list;
    struct card tcard;
    // printf("Searched rank is %c\n",rank);
    while (cards != NULL){
        tcard = cards->top;
        // printf("Target has: %c\n",tcard.rank[0]);
        if(tcard.rank[0] == rank){

            // printf("Rank %c found in Target.\n",rank);
            return 1;
        }
        cards = cards->next;
    }
    
    return 0;
}

int transfer_cards(struct player* src, struct player* dest, char rank) {
    struct hand* current_card = src->card_list;
    struct hand* previous = NULL;
    bool found = false;
    int cards_transferred = 0;
    int error = -1;    

    if (src->hand_size == 0) {
        return 0;  // No cards to transfer
    }

    // Iterate through the linked list
    while (current_card != NULL) {
        struct card tcard = current_card->top;

        if (tcard.rank[0] == rank) {
            // If card is found, set found to true
            found = true;

            // Add transferred card(s) to dest
            error = add_card(dest, &tcard);

            // If there is an error return -1
            if (error != 0) {
                return -1;
            }

            // Remove transferred card(s) from src
            if (previous != NULL) {
                previous->next = current_card->next;
                current_card = previous->next; // Move to the next card in the linked list
            } else {
                src->card_list = current_card->next;
                current_card = src->card_list; // Move to the next card in the linked list
            }

            // Update hand_size
            src->hand_size -= 1;
            
            cards_transferred++;
        } else {
            // Move to the next card in the linked list
            previous = current_card;
            current_card = current_card->next;
        }
    }

    // If no cards are found return 0
    if (!found) {
        return 0;
    }

    // Return the number of cards transferred
    return cards_transferred;
}

int game_over(struct player* target){
    if(target->book_index>=7){ return 1; }
    return 0;
}

int reset_player(struct player* target){
    
    // Remove all the cards from the player
    struct hand* cards = target->card_list;
    struct hand* previous;
    struct card card;
    while (cards != NULL){
        previous = cards;
        cards = cards->next;
        card = previous->top;
        remove_card(target,&card);
    }
    

    // Reset the Player's book
    for (int i = 0; i < sizeof(target->book); i++) {
        target->book[i] = '\0';
    }

    // Reset the book index
    target->book_index = 0;

    return 0;
}

char computer_play(struct player* target){

    char ranks[13] = {'2', '3', '4', '5', '6', '7', '8', '9', '1', 'J', 'Q', 'K', 'A'};
    
    // Seed the random number generator
    srand(time(NULL));

    // Generate a random index within the valid range
    int randomIndex = rand()%13;

    char rank = ranks[randomIndex];
    int found = search(target,rank);   // see if computer has the card
    while(found!=true){   // found = 0, 
        rank = ranks[rand()%13];
        found = search(target,rank);
        if(found == 1){
            // printf("What is this returning: %c", rank);
            return rank;
        } 
    }
    return rank;
    
}

char user_play(struct player* target){
    char request[3];
    bool found = false;
    while(found == false){

        // Prompt player to choose a rank
        printf("Player 1's turn, enter a Rank: ");
        scanf("%s",request);     // limit input to oen character to prevent overflow
        // printf("Request = %s\n",request);

        // Search if opponent has of the rank
        if(search(target,request[0])==1){
            // printf("Request = %s\n",request);
            // printf("Rank %s found.\n",request);
            return request[0];

        // If not reprompt the player to choose a new rank
        } else {
            // printf("Rank %s is not found.\n",request);
            printf("Error - must have at least one card from rank to play.\n");
        }
    }
}