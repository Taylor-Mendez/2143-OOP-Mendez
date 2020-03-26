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