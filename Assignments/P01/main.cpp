///////////////////////////////////////////////////////////////////////////////
//                   
// Author:           Taylor Mendes
// Email:            tlmendez0302@my.msutexas.edu
// Label:            P01
// Title:            main.cpp
// Course:           CMPS 2143
// Semester:         Spring 2020
//
// Description:
//       This program simulates a game of war using the WarGame class 
//       and displayes winner of the game along with the amount of card
//       the winner has at the end. Winner is determined when one of the 
//       players hand equals zero or a player does not have enough cards
//       to go to war. 
//      
// Files:            
//      PlayingCard.hpp 
/////////////////////////////////////////////////////////////////////////////////
#include "PlayingCard.hpp"
#include <iostream>
#include <string>

using namespace std;

int main() {

    Term::IO io;

    WarGame war;

    war.deal();

    war.play();

    return 0;
}