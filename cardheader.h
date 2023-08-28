#ifndef CARDHEADER_H
#define CARDHEADER_H

#include <iostream>

class Card{

    private:

        int rank;
        int suit;

    public:

        Card();

        void set_rank(int);

        int get_rank();

        void set_suit(int);

        int get_suit();

        std::string map_suit();

        std::string map_rank();
        
        void printCard();

};

#endif