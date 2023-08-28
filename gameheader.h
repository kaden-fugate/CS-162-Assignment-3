#ifndef GAMEHEADER_H
#define GAMEHEADER_H

#include <iostream>
#include "deckheader.h"
#include "playerheader.h"

class Game{

    private:

        Deck d;
        Player players[2];
    
    public:

        Game();

        bool player_fishes(int, int);

        int check_hand(int, bool);

        void players_swap_cards(int, bool);

        bool draw_card(int, int, bool);

        void print_player_hand(int, bool);

        bool game_over();

        bool play_again();
        

};

#endif