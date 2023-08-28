#include <iostream>
#include <cstdlib>
#include "deckheader.h"



/*********************************************************************** 
** Function: Deck()
** Description: default constructor for deck class
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
************************************************************************/

Deck::Deck(){
    
    n_cards = 52;
    set_cards();

}



/*********************************************************************** 
** Function: get_n_cards()
** Description: gets the number of cards remaining in the deck
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
************************************************************************/

int Deck::get_n_cards(){

    return n_cards;

}



/*********************************************************************** 
** Function: set_n_cards()
** Description: increments n_cards for deck down by 1 because
** it will only go down by one at a time
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
************************************************************************/

void Deck::set_n_cards(){ // no paramaters because n_cards decreases by increment of 1

    n_cards--;

}



/*********************************************************************** 
** Function: set_cards()
** Description: sets all the cards within the deck to a seperate card
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
************************************************************************/

void Deck::set_cards(){ // only needs to be run once during program as deck is constant

    int new_rank = 0;
    int new_suit = 0;

    for(int i = 0; i < 52; i++){

        cards[i].set_rank(new_rank);
        cards[i].set_suit(new_suit);

        if(new_suit == 3){

            new_suit = 0;
            new_rank++;

        }
        else{
            new_suit++;
        }

    }

}



/*********************************************************************** 
** Function: draw_card(int)
** Description: draws a card of a specific index from the deck
** Parameters: index of the card
** Pre-Conditions: none
** Post-Conditions: none
************************************************************************/

Card Deck::draw_card(int index){

    return this->cards[index];

}



/*********************************************************************** 
** Function: get_card_rank(int)
** Description: gets the rank of a card from a specific index of the deck
** basically just here for encapsulation reasons
** Parameters: index of the card
** Pre-Conditions: none
** Post-Conditions: none
************************************************************************/

int Deck::get_card_rank(int index){

    return cards[index].get_rank();

}



/*********************************************************************** 
** Function: get_card_mapping(int)
** Description: gets the mapping of a card from the deck literally only
** used once so program doesnt break encapsulation
** Parameters: index of card
** Pre-Conditions: none
** Post-Conditions: none
************************************************************************/

std::string Deck::get_card_mapping(int index){

    return cards[index].map_rank();

}



/*********************************************************************** 
** Function: shuffle_card()
** Description: shuffles the cards in the deck a random amount of times (atleast once)
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
************************************************************************/

void Deck::shuffle_cards(){

    int rand_index;
    Card temp;

    for(int i = 0; i < ((rand() % 20) + 1); i++){ // shuffles deck a random amount of times

        for(int i = 0; i < 52; i++){ // shuffles deck

            rand_index = (rand() % 51);

            temp = cards[i];
            cards[i] = cards[rand_index];
            cards[rand_index] = temp;

        }

    }

}