#ifndef HANDHEADER_H
#define HANDHEADER_H

#include <iostream>
#include "cardheader.h"

class Hand{

    private:

        Card *cards; // array of cards in hand
        int n_cards; // number of cards in hand
    
    public:

        Hand();

        Hand(const Hand&);

        Hand& operator=(const Hand&);

        ~Hand();

        int get_n_cards();

        Card get_card(int);

        int get_card_rank(int);
        
        Card* card_to_hand(Card);

        void card_from_hand(int);

        void sort_hand();

        void print_hand();

        int search_hand(int);

        void print_card(int);


};


#endif