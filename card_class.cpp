#include <iostream>
#include "cardheader.h"



/*********************************************************************** 
** Function: Card()
** Description: default constructor for card class
** Parameters: none 
** Pre-Conditions: none
** Post-Conditions: none
************************************************************************/

Card::Card(){ // default construtcor

    rank = 12;
    suit = 3;

}



/*********************************************************************** 
** Function: set_rank(int)
** Description: sets the rank of a card
** Parameters: the new rank
** Pre-Conditions: new rank must exist
** Post-Conditions: none
************************************************************************/

void Card::set_rank(int newRank){ // mutator

    this->rank = newRank;

}



/*********************************************************************** 
** Function: get_rank()
** Description: gets the rank of a card
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
************************************************************************/

int Card::get_rank(){ // accessor

    return rank;

}



/*********************************************************************** 
** Function: set_suit(int)
** Description: sets the suit of a card
** Parameters: the new suit
** Pre-Conditions: the new suit must exist
** Post-Conditions: none
************************************************************************/

void Card::set_suit(int newSuit){ // mutator

    this->suit = newSuit;

}



/*********************************************************************** 
** Function: get_suit()
** Description: gets the suit of a card
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
************************************************************************/

int Card::get_suit(){ // accessor

    return suit;

}



/*********************************************************************** 
** Function: map_suit()
** Description: maps the suit of a card to a good display value
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
************************************************************************/

std::string Card::map_suit(){ // accessor ?

    std::string suitMap[4] = {"♣️", "♦️", "♥️", "♠️"};

    return suitMap[this->suit];

}



/*********************************************************************** 
** Function: map_rank()
** Description: maps the rank of a card to a good rank (1 = A, 11 = J, etc...)
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
************************************************************************/

std::string Card::map_rank(){ // accessor ?

    std::string rankMap[13] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};

    return rankMap[this->rank];

}



/*********************************************************************** 
** Function: printCard()
** Description: prints the values of a card
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
************************************************************************/

void Card::printCard(){

    if(this->rank != 9){

        std::cout << "[" << map_rank() << " " << map_suit() << "]";

    }
    else{ // keeps spacing all nice n tidy because 10 is the only 2 digit rank card

        std::cout << "[" << map_rank() << map_suit() << "]";

    }

}
