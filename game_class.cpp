#include <iostream>
#include "gameheader.h"



/*********************************************************************** 
** Function: Game()
** Description: default constuctor for game class
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
************************************************************************/

Game::Game(){

    // deck is initialized with 52 cards
    // players are initialized with 0 cards in their hand and 0 books

    d.shuffle_cards(); // shuffle the cards

    for(int i = 0; i < 2; i++){ // fill those hands so we can play some go fish!

        for(int j = (52 - d.get_n_cards()); j < (i * 7) + 7; j++){

            players[i].set_hand(d.draw_card(j)); // draws card from deck

            d.set_n_cards(); // increment num of cards in deck down by one

        }

    }

}



/*********************************************************************** 
** Function: player_fishes(int, int)
** Description: checks if the player needs to go fish
** Parameters: index of the player, rank of requested card
** Pre-Conditions: none
** Post-Conditions: player must draw card
************************************************************************/

bool Game::player_fishes(int index, int rank){

    bool go_fish = false; // initially, player does not need to fish

    if(players[index].get_hand().search_hand(rank) == 0){ // if no cards are of the correct rank are in the hand

        if(d.get_n_cards() < 53){ // if cards are left in the deck, the player will be going and they will be fishing

            go_fish = true;

        }

    }
    // if correct card found, player will be doing no going and fishing

    return go_fish;

}



/*********************************************************************** 
** Function: check_hand(int, bool)
** Description: combines the way that the human and computer request cards
** into a one function and includes extra error checking to make sure
** the players hand isnt empty
** Parameters: index of the current player, truth value of cheat_mode
** Pre-Conditions: none
** Post-Conditions: none
************************************************************************/

int Game::check_hand(int index, bool cheat_mode){

    int rank;

    while(true){

        if(players[index % 2].check_empty() == false){ // if hand is not empty

            if((index % 2) == 0){ // get user requested card

                rank = players[0].check_rank();

            }
            else{ // computer card

                rank = players[1].computer_turn(players[0], d);

            }

            break;

        }
        else{ // if hand is empty, we will draw a card then ask for a rank

            draw_card(index, -1, cheat_mode); // -1 for the rank because the user has not requested a card yet

        }

    }

    return rank;

}



/*********************************************************************** 
** Function: players_swap_cards(int, bool)
** Description: this is where all the magic happens! this function goes through 
** all the steps of getting a new card one a turn. (Asks for rank -> swaps card/ draws card)
** Parameters: index of player, truth value of cheat_mode
** Pre-Conditions: none
** Post-Conditions: none
************************************************************************/

void Game::players_swap_cards(int index, bool cheat_mode){

    bool go_again = false;

    while(true){ // loop for if the player draws the same card that they request

        int rank = check_hand(index, cheat_mode); // performs all error checking and gets the correct requested rank

        if(players[(index + 1) % 2].check_empty() == false){ // if opposite players hand is not empty

            if(player_fishes(( (index + 1) % 2), rank) == false){ // check if card in opposite hand

                this->players[ (index % 2) ].swap_cards(rank, this->players[(index + 1) % 2]); // if it is, players exchange cards
                
                players[index % 2].detect_book();
                print_player_hand(index, cheat_mode); // print new hand
                
                go_again = true; // player gets to request another card

                if(players[0].get_n_books() + players[1].get_n_books() == 13){

                    go_again = false; /* makes sure it doesnt try to make the player draw another card 
                    when the game is over */

                }
                
            }
            else{ // not in opposite hand, draw a card

                go_again = draw_card(index, rank, cheat_mode);

            }

        }
        else{ // opposite hand empty, draw a card

            go_again = draw_card(index, rank, cheat_mode);

        }

        if(go_again == false){ // if the player doesnt have another turn, the game goes to the next turn

            break;

        }

    }

    players[index % 2].detect_book();

}
// function is 16 lines but this is where all the magic happens so that should be alright.... right.......?



/*********************************************************************** 
** Function: 
** Description: 
** Parameters: 
** Pre-Conditions: 
** Post-Conditions: 
************************************************************************/

bool Game::draw_card(int index, int rank, bool cheat_mode){

    bool go_again = false;

    if(d.get_n_cards() != 0){ // amount of cards in deck is greater than 0

        std::cout << "Go fish!\n";

        players[ (index % 2) ].set_hand( d.draw_card( 52 - d.get_n_cards() )); // draw card

        if(index % 2 == 0){

            std::cout << "You drew a " << d.get_card_mapping( 52 - d.get_n_cards() ) << "!\n";

        }
        else if(index % 2 == 1 && cheat_mode == true){

            std::cout << "Computer drew a " << d.get_card_mapping( 52 - d.get_n_cards() ) << "!\n";

        }

        if( d.get_card_rank( 52 - d.get_n_cards() ) != rank){

            d.set_n_cards();

        }
        else{    

            d.set_n_cards();
            players[index % 2].detect_book();

            if(d.get_n_cards() != 0){

                go_again = true;

            }

            if(index % 2 == 0 || cheat_mode == true){

                print_player_hand(index, cheat_mode);

            }
            
        }

    }
    // if there are no cards left in the deck, we dont do anything

    return go_again;

}
// i know the function looks long but excluding the couts and the initializaions, its only 13 lines



/*********************************************************************** 
** Function: print_player_hand(int, bool)
** Description: prints the hand of the player (or players)
** Parameters: index of the player, truth value of cheat_mode
** Pre-Conditions: none
** Post-Conditions: none
************************************************************************/

void Game::print_player_hand(int index, bool cheat_mode){

    if(index % 2 == 0 && cheat_mode == true){

        std::cout << "You:\n\n";

    }

    players[0].print_hand();

    std::cout << "Your ";
    players[0].print_book();

    if(cheat_mode == true){

        std::cout << "Computer:\n\n";

        players[1].print_hand();
        

    }

    std::cout << "Computers ";
    players[1].print_book();

}



/*********************************************************************** 
** Function: game_over()
** Description: checks if the game is over for the players
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
************************************************************************/

bool Game::game_over(){

    bool game_over = false;

    if((players[0].get_n_books() + players[1].get_n_books()) == 13){

        game_over = true;

        if(players[0].get_n_books() > players[1].get_n_books()){

            std::cout << "\n\nYou are the winner!\n\n";

        }
        else{

            std::cout << "\n\nThe computer wins!\n\n";

        }

    }

    return game_over;

}



/*********************************************************************** 
** Function: play_again()
** Description: checks if the player would like to play again
** Parameters: none
** Pre-Conditions: the game must be over
** Post-Conditions: none
************************************************************************/

bool Game::play_again(){

    bool play_again = false;

    char input;

    while(true){

        std::cout << "Would you like to play again? (t or f): ";
        std::cin >> input;

        if(tolower(input) == 't'){

            play_again = true;
            break;

        }
        else if(tolower(input) == 'f'){

            play_again = false;
            break;

        }
        else{

            std::cout << "Please enter a valid input!\n";

        }

    }

    return play_again;

}