#include <iostream>
#include <cstdlib>
#include "playerheader.h"
#include "handheader.h"



/*********************************************************************** 
** Function: Player()
** Description: default constructor for the player class
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
************************************************************************/

Player::Player(){ // initialize player class

    n_books = 0;

}



/*********************************************************************** 
** Function: operator=(const Player&)
** Description: assignment overload operator for player class
** Parameters: constant player class passed by reference
** Pre-Conditions: exisiting player is set equal to another player
** Post-Conditions: none
************************************************************************/

Player& Player::operator=(const Player &player){

    Player temp_player = player; // copy constructor to automatically set temp_player equal to player

    if(this->n_books > 0){

        delete[] this->books;

    }

    this->n_books = temp_player.n_books;
    this->books = new int[temp_player.n_books];

    for(int i = 0; i < temp_player.n_books; i++){

        this->books[i] = temp_player.books[i];

    }


    return *this; // destructor should get rid of temp player

}



/*********************************************************************** 
** Function: Player(const Player&)
** Description: copy constructor for player class
** Parameters: player class passed by reference
** Pre-Conditions: Player class is initialized to the value of another player
** class
** Post-Conditions: none
************************************************************************/

Player::Player(const Player &player){

    Player temp_player;

    this->hand = player.hand; // using AOO we can just set these equal and get a deep copy
    this->n_books = player.n_books;

    if(this->n_books > 0){

        temp_player.books = new int[this->n_books];
        this->books = new int[this->n_books]; 

        for(int i = 0; i < this->n_books; i++){

            temp_player.books[i] = player.books[i]; 
            this->books[i] = temp_player.books[i]; // deep copy

        }

        delete[] temp_player.books;
        temp_player.books = NULL;

    }

}



/*********************************************************************** 
** Function: ~Player()
** Description: destructor for player class
** Parameters: none
** Pre-Conditions: player class must go out of scope
** Post-Conditions: none
************************************************************************/

Player::~Player(){

    if(n_books > 0){

        delete[] books;
        books = NULL;

    }

}



/*********************************************************************** 
** Function: get_n_books()
** Description: gets the number of books that a player has
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
************************************************************************/

int Player::get_n_books(){

    return this->n_books;

}



/*********************************************************************** 
** Function: new_book()
** Description: this function makes a new book of a rank for a player.
** this is the only place that I could think to use the CC and AOO
** for the player class. Lmk if I could've used it somewhere else
** Parameters: new book rank
** Pre-Conditions: player must have 4 cards of same rank in their hand
** Post-Conditions: none
************************************************************************/

void Player::new_book(int rank){

    Player temp_player = *this; // get deep copy of player

    if(temp_player.n_books > 0){ // delete the previous books if they exist

        delete[] temp_player.books;

    }

    temp_player.n_books++;
    temp_player.books = new int[temp_player.n_books]; // make a new array of books that is a greater size

    for(int i = 0; i < temp_player.n_books; i++){

        if(i < temp_player.n_books - 1){ // add previous array values

            temp_player.books[i] = this->books[i];

        }
        else{ // add new book to array

            temp_player.books[i] = (rank + 1);

        }

    }

    *this = temp_player; // use AOO to return deep copy of new player

    // destructor deletes temp_player as it goes out of scope

}
// 10 lines



/*********************************************************************** 
** Function: detect_book()
** Description: a wonderful function where we detect books
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
************************************************************************/

void Player::detect_book(){ 

    for(int i = 0; i < (this->hand.get_n_cards() - 2); i++){ // for loop goes until a book is impossible

        int count = 0;
        
        for(int j = i + 1; j < i + 4; j++){ // hands are sorted so we check the next 3 cards to look for book

            if(j != this->hand.get_n_cards()){ // makes sure function doesnt look for book outside of array

                if(this->hand.get_card(i).get_rank() == this->hand.get_card(j).get_rank()){ // BREAKS THE THING RULE THING

                    count++; // if original card matches next card, count goes up and loop runs again

                }
                else{

                    break; // if card doesnt match cards for book, count will not properly go to 3

                }

            }
            else{ // if outside of array, break array

                break;

            }

        }

        if(count == 3){

            new_book(this->hand.get_card_rank(i));

            for(int j = i; j < i + 4; j++){

                this->hand.card_from_hand(j - (j - i)); // makes it so that j doesnt change index when removing cards

            }

        }

    }

}
// 13 lines... cutting it close.



/*********************************************************************** 
** Function: print_hand()
** Description: prints a players hand
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
************************************************************************/

void Player::print_hand(){

    std::cout << "\nHand:" << " \n\n";

    if(this->hand.get_n_cards() > 0){ // if hand has cards

        std::cout << "[ ";

        for(int i = 0; i < this->hand.get_n_cards(); i++){

            this->hand.print_card(i);

            if(i == this->hand.get_n_cards() - 1){ // if statement for end of array

                std::cout << " ]\n";

            }
            else{ // any other time, we seperate with a comma and a space

                std::cout << ", ";

            }

        }

    }
    else{ // does not have cards in hand

        std::cout << "No Cards!\n";

    }

}



/*********************************************************************** 
** Function: print_book()
** Description: prints the books that a player contains
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
************************************************************************/

void Player::print_book(){

    std::cout << "Books: ";

    if(this->n_books > 0){ // books present

        std::cout << "[ "; // start of array

        for(int i = 0; i < this->n_books; i++){

            std::cout << "[" << this->books[i] << "]"; // print element

            if(i == this->n_books - 1){

                std::cout << " ]\n\n"; // end array

            }
            else{

                std::cout << ", "; // seperate elements

            }

        }

    }
    else{ // not present

        std::cout << "No books!\n\n";

    }

}



/*********************************************************************** 
** Function: swap_cards(rank, Player&)
** Description: this player runs through the arrays of the players and checks
** if they need to give cards to the other player. If they do, players swap cards
** Parameters: requested rank, player that is giving the cards
** Pre-Conditions: none
** Post-Conditions: none
************************************************************************/

void Player::swap_cards(int rank, Player &card_giver){

    int count = 0; // hand index gets set back by 1 when a card is found, this accounts for shift

    for(int i = 0; i < card_giver.hand.get_n_cards() + count; i++){

        if(card_giver.hand.get_card_rank(i - count) == rank){

            this->hand.card_to_hand(card_giver.hand.get_card(i - count)); // give card

            card_giver.hand.card_from_hand(i - count); // lose card

            count++; // next card is in current i so i = i - 1 now

        }
        
    }

}



/*********************************************************************** 
** Function: check_rank()
** Description: checks if the rank that the player requests is valid
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
************************************************************************/

int Player::check_rank(){

    int rank;

    while(true){

        std::cout << "Requested rank (1 - 13): ";
        std::cin >> rank;
        
        if(rank > 0 && rank < 14){ // if entered rank is in correct range

            if(this->hand.search_hand(rank - 1) == 0){ // if card is not in hand

                std::cout << "Please enter a card within your hand\n\n";

            }
            else{ // if input is successful, break loop

                break;
                
            }

        }
        else{ // input is not within valid range

            std::cout << "\nPlease enter a valid input!\n\n";

        }

    }

    return (rank - 1); // rank - 1 so computer can recognize it correctly

}



/*********************************************************************** 
** Function: computer_turn(Player&, Deck&)
** Description: This is how the computer requests a card. It loops through the 
** array its own cards. First it checks if the next card in the deck is equal to a 
** card in its deck. If it isnt, it then loops through and checks if a card is equal
** to a card in the other players hand. If this also isnt true, computer requests its
** highest card as to give as little info about their hand as possible.
** Parameters: the users player class and the deck class
** Pre-Conditions: none
** Post-Conditions: none
************************************************************************/

int Player::computer_turn(Player &player, Deck &d){

    int rank = -1;

    for(int i = 0; i < this->hand.get_n_cards(); i++){ // check every card in the computers hand

        if(this->hand.get_card_rank(i) == d.get_card_rank(52 - d.get_n_cards())){ // check to see if next card in deck is in current hand index

            rank = this->hand.get_card_rank(i);
            break; // if computer can take next card in deck, they will before taking player cards

        }
        else{

            for(int j = 0; j < player.hand.get_n_cards(); j++){ // check every card in player hand everytime we check a computer card

                if(this->hand.get_card_rank(i) == player.hand.get_card_rank(j)){

                    rank = this->hand.get_card_rank(i); 
                    break; // value found, break loop to ask

                }

            }

            if(rank == -1 && i == this->hand.get_n_cards() - 1){ /* if computer cant do anything fancy,
            they only request their highest card to give the player as little knowledge of hand as possible*/

                rank = this->hand.get_card_rank(i);

            }
            else{

                if(rank != -1){ // if a card that matches player hand is found, break loop and ask for it

                    break;

                }

            }

        }

    }

    std::cout << "Computer picks: " << (rank + 1) << "\n";

    return rank;

}
// 14 lines when you ignore cout and initialization



/*********************************************************************** 
** Function: set_hand(Card)
** Description: adds a card to a players hand (basically just here for encapsulation)
** Parameters: new card
** Pre-Conditions: none
** Post-Conditions: none
************************************************************************/

void Player::set_hand(Card card){ // we only need to use this to let a player draw a card from the deck

    hand.card_to_hand(card);

}



/*********************************************************************** 
** Function: get_hand()
** Description: gets an entire hand class. Uses CC because returning the
** hand class itself would originally make it go out of scope and destruct.
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
************************************************************************/

Hand Player::get_hand(){

    Hand temp_hand = hand; // returning hand makes hand go out of scope

    return temp_hand;

}



/*********************************************************************** 
** Function: check_empty()
** Description: checks if a players hand is empty
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
************************************************************************/

bool Player::check_empty(){

    bool empty = false;

    if(this->hand.get_n_cards() == 0){

        empty = true;

    }

    return empty;

}
