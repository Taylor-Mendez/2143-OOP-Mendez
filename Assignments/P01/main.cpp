#include "PlayingCard.hpp"
#include <iostream>
#include <string>

using namespace std;

int main() {

    Term::IO io;


    WarGame war;

    war.deal();

    // test
    war.compare();
    war.compare();
    war.compare();

    return 0;
}