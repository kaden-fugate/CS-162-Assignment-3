#include <iostream>
#include "one_header.h"



/*********************************************************************** 
** Function: check_cheat_mode
** Description: checks if you want to enable cheat mode
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
************************************************************************/

bool check_cheat_mode(){
    /* not gonna lie, kinda just felt funny to make only one function
    that wasnt a member function within a class*/

    bool cheat_mode = false;
    char input;

    while(true){

        std::cout << "Would you like to enable cheat mode? (t or f): ";
        std::cin >> input;

        if(tolower(input) == 't'){

            cheat_mode = true;
            break;

        }
        else if(tolower(input) == 'f'){

            break;

        }
        else{

            std::cout << "Please enter a valid input!\n";

        }

    }

    return cheat_mode;

}