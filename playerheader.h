#ifndef PLAYERHEADER_H
#define PLAYERHEADER_H

#include <iostream>
#include "handheader.h"
#include "deckheader.h"

class Player{

    private:

        Hand hand;
        int *books; // holds ranks of cards that player has books for
        int n_books;

    public:

        Player();

        Player& operator=(const Player&);

        Player(const Player&);

        ~Player();

        Hand get_hand();

        int get_n_books();

        void set_hand(Card);

        void new_book(int);

        void detect_book();

        void print_book();

        void swap_cards(int, Player&);

        int check_rank();

        int computer_turn(Player&, Deck&);

        void print_hand();

        bool check_empty();


};

#endif