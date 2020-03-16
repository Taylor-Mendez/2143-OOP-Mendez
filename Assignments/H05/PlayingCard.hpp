#include "termio.h"
#include <algorithm> // std::random_shuffle
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
  ██████╗ █████╗ ██████╗ ██████╗
 ██╔════╝██╔══██╗██╔══██╗██╔══██╗
 ██║     ███████║██████╔╝██║  ██║
 ██║     ██╔══██║██╔══██╗██║  ██║
 ╚██████╗██║  ██║██║  ██║██████╔╝
  ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═════╝
*/

class Card {
private:
    const string spade = "♠";
    const string diamond = "♦";
    const string heart = "♥";
    const string club = "♣";

    const string suits[4] = {"♠", "♦", "♣", "♥"};

    // Black background        blue ,  red , blue , red
    const string colors2[4] = {"&60", "&20", "&60", "&20"};

    // Colored background      blue  , red  , blue , red
    const string colors[4] = {"&16", "&12", "&16", "&12"};

    // Card labels (could be "Iron Man" or "Charmander" or "Elf" ... anything)
    const string ranks[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

    int suitNum;        // value 0-3 : num index of suit
    int rank;           // 0-13      : num value of rank
    int number;         // 1-52      : unique value determines card
    int value;          // 1-14      : numeric value used for comparison
    string suitChar;    // "♠", "♦", "♣", "♥"
    string rankChar;    // Ace, 1 ,2 ,3 ... Q, K
    string color;       // Spade=blue, Diamond=red, etc.
    string backcolor;   // background color of card
    string charcolor;   // character color of card
    string numbercolor; // color of numbers on card

public:
    struct ForeGround{
        string red;
        string blue;
        string black;
        string defaultcolor;

        ForeGround(){
            red = "&12";
            blue = "&15";
            black = "&11";
            defaultcolor = "&10";
        }
    };
    struct BackGround{
        string red;
        string blue;
        string black;
        string defaultcolor;

        BackGround(){
            red = "&20";
            blue = "&50";
            black = "&10";
            defaultcolor = "&00";
        }
    };
    friend ostream;

    Card(int);
    string Repr();
    bool operator<(const Card &);
    bool operator>(const Card &);
    bool operator==(const Card &);
    bool operator!=(const Card &);
    bool operator()(const Card &);
    void setForegroundColor(string color);       // set foreground color of card
    void setBackgroundColor(string color);      // set background color of card
    void setColors(string fore,string back);      // set fore and back
    void setCharacterColor(string color);        // set symbol color 
    void setNumberColor(string color);          // set number color
    void setColors(string fore, string back, string symbol, string number);
};

/**
     * Public : setForegroundColor
     *
     * Description:
     *      sets/updates the color of a card foreground
     *
     * Params:
     *      string : represents the color of the card foreground
     *
     * Returns:
     *      None
     */

void Card::setForegroundColor(string color){
    ForeGround temp;
    if (color == "red")
        color = temp.red;
    else if (color == "blue")
        color = temp.blue;
    else if (color == "black")
        color = temp.black;
    else 
        color = temp.defaultcolor;
}

/**
     * Public : setBackgroundColor
     *
     * Description:
     *      sets/updates the color of a card backgroundground
     *
     * Params:
     *      string : represents the color of the card backgroundground
     *
     * Returns:
     *      None
     */

void Card::setBackgroundColor(string color){
    BackGround temp;
    if (color == "red")
        backcolor = temp.red;
    else if (color == "blue")
        backcolor = temp.blue;
    else if (color == "black")
        backcolor = temp.black;
    else 
        backcolor = temp.defaultcolor;
}

/**
     * Public : setColors
     *
     * Description:
     *      sets/updates the color of a card foreground and background
     *
     * Params:
     *      string : represents the color of the card foreground
     *      string : represents the color of the card background
     *
     * Returns:
     *      None
     */

void Card::setColors(string fore,string back){
    setForegroundColor(fore);
    setBackgroundColor(back);

}

/**
     * Public : setCharacterColor
     *
     * Description:
     *      sets/updates the color of a card character (i.e. "♠", "♦", "♣", "♥")
     *
     * Params:
     *      string : represents the color of the card character color
     *
     * Returns:
     *      None
     */

void Card::setCharacterColor(string color){
    ForeGround temp;
    if (color == "red")
        charcolor = temp.red;
    else if (color == "blue")
        charcolor = temp.blue;
    else if (color == "black")
        charcolor = temp.black;
    else 
        charcolor = temp.defaultcolor;
}

/**
     * Public : setNumberColor
     *
     * Description:
     *      sets/updates the color of a card number
     *
     * Params:
     *      string : represents the color of the card character color
     *
     * Returns:
     *      None
     */

void Card::setNumberColor(string color){
    ForeGround temp;
    if (color == "red")
        numbercolor = temp.red;
    else if (color == "blue")
        numbercolor = temp.blue;
    else if (color == "black")
        numbercolor = temp.black;
    else 
        numbercolor = temp.defaultcolor;
}

/**
     * Public : setColors
     *
     * Description:
     *      sets/updates all colors of each element of a card including the foreground,
     *      background, character, and number.
     *
     * Params:
     *      string : represents the color of card foreground
     *      string : represents color of background
     *      string : represents the color of the card character color
     *      string : represents the color of the card number
     *
     * Returns:
     *      None
     */

void Card::setColors(string fore, string back, string symbol, string number){
    setForegroundColor(fore);
    setBackgroundColor(back);
    setCharacterColor(symbol);
    setNumberColor(number);
}


/**
     * Public : Card
     *
     * Description:
     *      Represents a single card in a deck of cards to include a
     *      value along with rank and suit. We are assuming a standard
     *      card type in a deck of playing cards.
     *
     * Params:
     *      int :  value from 0 - 51 that represents a card in a deck.
     *
     * Returns:
     *      None
     */
Card::Card(int num) {
    const string spade = "♠";
    const string diamond = "♦";
    const string heart = "♥";
    const string club = "♣";

    const string suits[4] = {"♠", "♦", "♣", "♥"};

    // Card labels (could be "Iron Man" or "Charmander" or "Elf" ... anything)
    const string ranks[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

    // instance of ForeGround so that i can assign value to color
    ForeGround temp;
    // same for background
    BackGround  temp2;

    number = num;
    suitNum = number / 13;
    suitChar = suits[suitNum];
    if (suitNum % 2 == 0)          // foreground color
        color = temp.blue;
    else
        color = temp.red;
    
    backcolor =  temp2.black;  // background color
    charcolor = temp.black;    // character color
    numbercolor = temp.black;   // color of numbers on card
    rank = number % 13;
    rankChar = ranks[rank];
}

/**
     * Public : Repr
     *
     * Description:
     *      Returns a string representation of the card class with
     *      colors embedded.
     *
     * Params:
     *      None
     *
     * Returns:
     *      [string] - representation of card
     */
string Card::Repr() {
    string s = "";
    s += color + "┌────┐&00 \n";
    s += color + "│";
    if (rank != 9) {
        s += color + " ";
    }
    s += color + rankChar + " " + suitChar + "│&00 \n";
    s += color + "└────┘&00 ";
    return s;
}

/**
 * Public : operator <<
 *
 * Description:
 *      Overload ostream and send the string representation "Repr"
 *      of the card.
 *
 *      We don't need the scope resolution operator (Card::) since
 *      this is a "friend" of card.
 *
 * Params:
 *      [ostream&] : os
 *      [Card]     : obj
 *
 * Returns:
 *      [ostream&]
 */
ostream &operator<<(ostream &os, Card obj) {

    os << obj.Repr();

    return os;
}

bool Card::operator<(const Card &rhs) {
    return this->rank < rhs.rank;
}

bool Card::operator>(const Card &rhs) {
    return this->rank > rhs.rank;
}

bool Card::operator==(const Card &rhs) {
    return this->rank == rhs.rank;
}

bool Card::operator!=(const Card &rhs) {
    return this->rank != rhs.rank;
}

bool Card::operator()(const Card &rhs) {
    return (this->rank < rhs.rank);
}

/*
  ██████╗ █████╗ ██████╗ ██████╗  ██████╗ ██████╗ ███╗   ██╗████████╗ █████╗ ██╗███╗   ██╗███████╗██████╗
 ██╔════╝██╔══██╗██╔══██╗██╔══██╗██╔════╝██╔═══██╗████╗  ██║╚══██╔══╝██╔══██╗██║████╗  ██║██╔════╝██╔══██╗
 ██║     ███████║██████╔╝██║  ██║██║     ██║   ██║██╔██╗ ██║   ██║   ███████║██║██╔██╗ ██║█████╗  ██████╔╝
 ██║     ██╔══██║██╔══██╗██║  ██║██║     ██║   ██║██║╚██╗██║   ██║   ██╔══██║██║██║╚██╗██║██╔══╝  ██╔══██╗
 ╚██████╗██║  ██║██║  ██║██████╔╝╚██████╗╚██████╔╝██║ ╚████║   ██║   ██║  ██║██║██║ ╚████║███████╗██║  ██║
  ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═════╝  ╚═════╝ ╚═════╝ ╚═╝  ╚═══╝   ╚═╝   ╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝╚══════╝╚═╝  ╚═╝
*/

class CardContainer {
protected:
    Term::IO io;
    vector<Card *> Cards;
    int RandomIndex();
    struct CardCompare {
        bool operator()(Card *l, Card *r) {
            return *l < *r;
        }
    };

public:
    CardContainer(int);
    void Add(Card *);
    bool isEmpty();
    void Order();
    Card *Remove();
    void Reset();
    void Shuffle();
    int Size();
};

CardContainer::CardContainer(int numCards) {
    for (int i = 0; i < numCards; i++) {
        Cards.push_back(new Card(i));
    }
}

void CardContainer::Add(Card *card) {
    // check if card already in container?
    // allow go over 52 ??

    Cards.push_back(card);
    //currentCount = Cards.size();
}

bool CardContainer::isEmpty() {
    return Cards.empty();
}

void CardContainer::Order() {
    sort(Cards.begin(), Cards.end(), CardCompare());
}

Card *CardContainer::Remove() {
    Card *temp = Cards.back();
    Cards.pop_back();
    return temp;
}

void CardContainer::Reset() {
    for (int i = 0; i < Cards.size() - 1; i++) {
        delete Cards[i];
        Cards[i] = new Card(i);
    }
}

void CardContainer::Shuffle() {
    for (int i = 0; i < Cards.size() - 1; i++) {
        int j = i + rand() % (Cards.size() - i);
        swap(Cards[i], Cards[j]);
    }
}

int CardContainer::Size() {
    return Cards.size();
}

/*
 ██████╗ ███████╗ ██████╗██╗  ██╗
 ██╔══██╗██╔════╝██╔════╝██║ ██╔╝
 ██║  ██║█████╗  ██║     █████╔╝
 ██║  ██║██╔══╝  ██║     ██╔═██╗
 ██████╔╝███████╗╚██████╗██║  ██╗
 ╚═════╝ ╚══════╝ ╚═════╝╚═╝  ╚═╝
*/

class Deck : public CardContainer {
protected:
    int deckSize;

public:
    Deck(int);
    Card *Draw();
    void Print(int, bool);
};

Deck::Deck(int size) : CardContainer(size) {
    deckSize = size;
}

Card *Deck::Draw() {
    Card *temp = Cards.back();
    Cards.pop_back();
    return temp;
}

void Deck::Print(int columns = 1, bool clear = false) {
    int i = 0;
    vector<string> cards;

    if (clear) {
        io << Term::clear;
    }

    for (auto c : Cards) {
        cards.push_back(c->Repr());

        i++;
        if (i == columns) {
            io << Term::fuse(cards) << "\n";
            i = 0;
            cards.clear();
        }
    }

    // any cards left in the vector should be
    // printed out.
    if (cards.size() > 0) {
        io << Term::fuse(cards) << "\n";
    }
}

/*
 ██╗  ██╗ █████╗ ███╗   ██╗██████╗
 ██║  ██║██╔══██╗████╗  ██║██╔══██╗
 ███████║███████║██╔██╗ ██║██║  ██║
 ██╔══██║██╔══██║██║╚██╗██║██║  ██║
 ██║  ██║██║  ██║██║ ╚████║██████╔╝
 ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═════╝
*/

class Hand {
protected:
public:
    Hand();
    void Print();
};

void Hand::Print() {
    return;
}

/*
  ██████╗  █████╗ ███╗   ███╗███████╗
 ██╔════╝ ██╔══██╗████╗ ████║██╔════╝
 ██║  ███╗███████║██╔████╔██║█████╗
 ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝
 ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗
  ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝
*/

class Game {
protected:
public:
};