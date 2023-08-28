#ifndef DECKHEADER_H
#define DECKHEADER_H

#include <iostream>
#include <cstdlib>
#include "cardheader.h"


class Deck{

    private:

        Card cards[52];
        int n_cards; // number of cards remaining in deck
    
    public:

        Deck();

        int get_n_cards();

        void set_n_cards();

        void set_cards();

        void shuffle_cards();

        Card draw_card(int);

        int get_card_rank(int);

        std::string get_card_mapping(int);


};

#endif