#include <iostream>
#include "cardheader.h"
#include "deckheader.h"
#include "handheader.h"



/*********************************************************************** 
** Function: Hand()
** Description: default constructor for hand class
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
************************************************************************/

Hand::Hand(){ // sets n_cards to zero so we use card_to_hand function to fill initial array of cards

    n_cards = 0;

}



/*********************************************************************** 
** Function: Hand(const Hand&)
** Description: copy constructor for hand class
** Parameters: constant hand variable passed by reference (const so the original hand is not
** manipulated within the copy constructor). Makes deep copy of hand class.
** Pre-Conditions: A hand class must be initialized and set equal to a seperate hand class
** Post-Conditions: none
************************************************************************/

Hand::Hand(const Hand &hand){

    Hand temp_hand; // temp hand is initialized with n_cards = 0

    if(hand.n_cards > 0){ // if hand to copy is not zero, copy hand

        temp_hand.n_cards = hand.n_cards;
        this->n_cards = temp_hand.n_cards; // dont think we need to deep copy this but just to be safe

        temp_hand.cards = new Card[this->n_cards];
        this->cards = new Card[this->n_cards]; // 2 new arrays for deep copy

        for(int i = 0; i < hand.n_cards; i++){

            temp_hand.cards[i] = hand.cards[i];
            this->cards[i] = temp_hand.cards[i]; // set indexes equal so they are deep copy

        }

    }
    // if hand were copying from is also empty, we do nothing

}



/*********************************************************************** 
** Function: operator=(const Hand&)
** Description: assignment overload operator for hand class. (Once again,
** const so the Hand class passed by reference is not manipulated). Makes it
** so we can set an existing class equal to another
** Parameters: constant hand class passed by reference
** Pre-Conditions: existing hand class is set equal to another hand class
** Post-Conditions: none
************************************************************************/

Hand& Hand::operator=(const Hand &hand){

    int temp_n_cards;
    Card* temp_cards;

    if(this->n_cards > 0){

        delete[] this->cards;

    }

    temp_n_cards = hand.n_cards;
    this->n_cards = temp_n_cards;
    
    temp_cards = new Card[temp_n_cards];
    this->cards = new Card[temp_n_cards];

    for(int i = 0; i < temp_n_cards; i++){

        temp_cards[i] = hand.cards[i];
        this->cards[i] = temp_cards[i];

    }

    delete[] temp_cards;

    return *this;

}



/*********************************************************************** 
** Function: ~Hand()
** Description: Destructor for the hand class. Deletes the allocated memory
** if present.
** Parameters: none
** Pre-Conditions: hand class must go out of scope
** Post-Conditions: none
************************************************************************/

Hand::~Hand(){

    if(n_cards > 0){ // deletes hand if it has cards in it

        delete[] this->cards;

        this->cards = NULL;

    }

}



/*********************************************************************** 
** Function: get_n_cards()
** Description: gets the number of cards within a hand
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
************************************************************************/

int Hand::get_n_cards(){

    return n_cards;

}



/*********************************************************************** 
** Function: get_card(int)
** Description: gets a card from the hand of a specific index
** Parameters: index of the card within the hand
** Pre-Conditions: index of desired card must be found
** Post-Conditions: none
************************************************************************/

Card Hand::get_card(int index){

    return this->cards[index];

}



/*********************************************************************** 
** Function: get_card_rank(int)
** Description: gets the rank of a card within the hand. Basically only used
** to follow encapsulation
** Parameters: index of the card 
** Pre-Conditions: index of card must be found
** Post-Conditions: none
************************************************************************/

int Hand::get_card_rank(int index){

    return this->cards[index].get_rank();

}



/*********************************************************************** 
** Function: card_to_hand(Card)
** Description: this is where a lot of the magic happens! This is how a
** card is added to a players hand
** Parameters: the card being added to the hand 
** Pre-Conditions: none
** Post-Conditions: none
************************************************************************/

Card* Hand::card_to_hand(Card new_card){

    Card *temp_arr;

    temp_arr = cards; // for deep copy

    n_cards++;

    cards = new Card[n_cards]; // new card array with size with card added

    for(int i = 0; i < n_cards; i++){ // filters through every card in hand

        if(i < n_cards - 1){

            cards[i] = temp_arr[i]; // old cards

        }
        else{
        
            cards[i] = new_card; // new card

        }

    }

    sort_hand(); // sort the new hand

    if(n_cards > 1){ // if memory was allocated for temp_arr, delete it

        delete[] temp_arr;
        temp_arr = NULL;

    }

    return cards; 

}
// 12 lines of code excluding initialization


/*********************************************************************** 
** Function: search_hand(rank)
** Description: this function finds how many times a card of a certain rank
** appears within the players hand
** Parameters: rank of the desired card
** Pre-Conditions: none
** Post-Conditions: none
************************************************************************/

int Hand::search_hand(int rank){

    int rank_detector = 0;

    for(int i = 0; i < n_cards; i++){ // search through hand

        if(cards[i].get_rank() == rank){ // if rank of card is requested rank, rank_detector++

            rank_detector++;

        }

    }

    return rank_detector; // returns # of cards of a rank

}



/*********************************************************************** 
** Function: card_from_hand(int)
** Description: also a pretty magical function! This function removes a
** card from a players hand
** Parameters: index of the card being removed
** Pre-Conditions: none
** Post-Conditions: none
************************************************************************/

void Hand::card_from_hand(int index){

    Card* temp_arr; // for deep copy

    if(this->n_cards != 1){ // if deck has more than 1 card in it

        temp_arr = new Card[this->n_cards - 1]; // new array which is 1 less than previous

        for(int i = 0; i < this->n_cards; i++){ // still need to go over every index of the original array

            if(i < index){ // if i less than index to remove, behave normal

                temp_arr[i] = this->cards[i];

            }
            else if(i > index){ /* if i greater than index to remove, temp_arr[i-1] is the new current card in new deck
            this is because the i is indexing for the original array of a length of temp_arr length + 1*/

                temp_arr[i - 1] = this->cards[i];

            }
            // if i == index, we just skip it all together and ignore it

        }

    }
    // if cards in hand is 1, we can just delete the hand all together and skip all the fancy steps

    this->n_cards--;

    delete[] this->cards;
    cards = NULL;

    this->cards = temp_arr; // temp_arr shouldnt be deleted as were setting it as the new memory for this->cards

}
// 11 lines excluding encapsulation



/*********************************************************************** 
** Function: sort_hand()
** Description: sorts the hand of a player. Not required but makes everything
** so much easier
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
************************************************************************/

void Hand::sort_hand(){
    // not sure what sorting alg this is, i just wrote it and it worked. most likely inefficient

    Card temp;

    for(int i = 0; i < n_cards; i++){ // cycle through length of array

        for(int j = i + 1; j < n_cards; j++){ /* for the next card, cycle through the array until the end and check
        against i for every value. if less than, switch the values*/

            if(cards[j].get_rank() < cards[i].get_rank()){

                temp = cards[i];
                cards[i] = cards[j];
                cards[j] = temp;

            }

        }

    }
    // after both loops are finished, array should be sorted.

}



/*********************************************************************** 
** Function: print_hand()
** Description: prints a players hand
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
************************************************************************/

void Hand::print_hand(){

    std::cout << "\nHand:" << " \n\n";

    if(this->n_cards > 0){ // if hand has cards

        std::cout << "[ ";

        for(int i = 0; i < n_cards; i++){

            cards[i].printCard(); // gotta love the one function that isnt formatted with _'s (prints element)

            if(i == n_cards - 1){ // end of array

                std::cout << " ]\n"; 

            }
            else{ // seperate elements

                std::cout << ", ";

            }

        }

    }
    else{ // no cards in hand

        std::cout << "No cards!\n\n";

    }

}



/*********************************************************************** 
** Function: print_card(index)
** Description: prints a single card from the hand (basically just used for encapsulation)
** Parameters: index of desired card
** Pre-Conditions: none
** Post-Conditions: none
************************************************************************/

void Hand::print_card(int index){
    // for encapsulation purposes

    cards[index].printCard();

}