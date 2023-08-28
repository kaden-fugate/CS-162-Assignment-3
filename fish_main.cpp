/******************************************************************************* 
** Program Filename: fish_main.cpp
** Author: Kaden ("The Kadenator") Fugate
** Date: November 6th, 2022
** Description: This program allows the player to play go fish against a very difficult computer
** Input: Cheat Mode, Requested Rank, Play Again
** Output: Players Hand, Players Book, (Maybe Computer Hand), Computer Books, Drawn Card, Winner
********************************************************************************/

#include <iostream>
#include <cstdlib>
#include "gameheader.h"
#include "one_header.h"

// im fully aware that my program has a god awful amount of functions and uses a truly horrid amount of memory

// didnt really understand classes until a few days ago

int main(){

    srand(time(0));

    bool cheat_mode = check_cheat_mode(); // Get status of cheat mode 

    while(true){

        Game go_fish; // initialize game class, (initializes player, players hands, and the deck), and shuffles deck

        int i = 0; // i counts the players turn

        while(true){

            std::cout << "===============================================================================\n\n";

            if(i % 2 == 0){

                std::cout << "Your turn!\n\n";

            }
            else{

                std::cout << "Computer's turn!\n\n";

            }

            go_fish.print_player_hand(i, cheat_mode); // Print the hand (or hands)

            go_fish.players_swap_cards(i, cheat_mode); // Players swap cards or player draws card

            i++; // next turn after player has taken / drawn all their cards

            if(go_fish.game_over() == true){

                break; // breaks game loop if 13 books are achieved

            }

        }

        if(go_fish.play_again() == false){

            break; // breaks the final loop if the player doesnt want to play again

        }
        // game is reset and re-initialized if the player wants to play again

    }

    return 0;

}
// uses 12 lines excluding couts and initializations
