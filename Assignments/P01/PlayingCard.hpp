#include "termio.h"
#include <algorithm> // std::random_shuffle
#include <iostream>
#include <string>
#include <vector>
#include <deque>

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
    string ReprBack();                           // used for displaying cards facedown
    bool operator<(const Card &);
    bool operator>(const Card &);
    bool operator==(const Card &);
    bool operator!=(const Card &);
    bool operator()(const Card &);
    void setForegroundColor(string color);       // set foreground color of card
    void setBackgroundColor(string color);       // set background color of card
    void setColors(string fore,string back);     // set fore and back
    void setCharacterColor(string color);        // set symbol color 
    void setNumberColor(string color);           // set number color
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
 * 
 */
string Card::ReprBack() {
    string color = "&10";
    string s = "";
    s += color + "┌────┐&00 \n";
    s += color + "│";
    s += color + "    " + "│&00 \n";
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
    deque<Card *> Cards;      // Made cardcontainer a deque instead of a vector
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
    Card *Back();
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

/**
 * Public : Back
 * 
 * Description : 
 *      allows us the get the last card in a CardContainer without
 *      removing it from the container
 * 
 * Params : 
 *      none
 * 
 * Returns : 
 *      Card* : a pointer to a card
 */

Card *CardContainer::Back() {
    Card *temp = Cards.back();

    return temp;
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

class Hand : public CardContainer {
    protected:
        int handsize;
    public: 
        Hand(int);
        void Print();
        void AddFront(Card *);
};

Hand::Hand(int size) : CardContainer(size) {
    handsize = size;
}

/*
 *
 * 
 * 
 * 
 * 
 */

void Hand::Print() {
    Term::IO io;
    Card temp = *(this->Remove());

    io << temp.Repr();

    using namespace std;
}

/**
 * Public : AddFront
 * 
 * Description : 
 *      allows us to add a card to the front of a hand
 * 
 * Params : 
 *      Card* : a pointer to a card
 * 
 * Returns : 
 *      none
 */

void Hand::AddFront(Card *card) {
    // check if card already in container?
    // allow go over 52 ??

    Cards.push_front(card);
    //currentCount = Cards.size();
}

/*
 /$$$$$$$  /$$        /$$$$$$  /$$     /$$ /$$$$$$$$ /$$$$$$$ 
| $$__  $$| $$       /$$__  $$|  $$   /$$/| $$_____/| $$__  $$
| $$  \ $$| $$      | $$  \ $$ \  $$ /$$/ | $$      | $$  \ $$
| $$$$$$$/| $$      | $$$$$$$$  \  $$$$/  | $$$$$   | $$$$$$$/
| $$____/ | $$      | $$__  $$   \  $$/   | $$__/   | $$__  $$
| $$      | $$      | $$  | $$    | $$    | $$      | $$  \ $$
| $$      | $$$$$$$$| $$  | $$    | $$    | $$$$$$$$| $$  | $$
|__/      |________/|__/  |__/    |__/    |________/|__/  |__/
*/

class Player {
    private:
        Hand hand{0}; 
        string id;
        friend class WarGame; // May not be the best way to fix the problem
    public:
        Player(int j){
            id = "player" + to_string(j);
        }

        void print (){
            cout << id;
        }
        Player& operator=(const Player &player) {
            hand = player.hand;
            id = player.id;

            return *this;
        }
};


/*
 /$$      /$$  /$$$$$$  /$$$$$$$   /$$$$$$   /$$$$$$  /$$      /$$ /$$$$$$$$
| $$  /$ | $$ /$$__  $$| $$__  $$ /$$__  $$ /$$__  $$| $$$    /$$$| $$_____/
| $$ /$$$| $$| $$  \ $$| $$  \ $$| $$  \__/| $$  \ $$| $$$$  /$$$$| $$      
| $$/$$ $$ $$| $$$$$$$$| $$$$$$$/| $$ /$$$$| $$$$$$$$| $$ $$/$$ $$| $$$$$   
| $$$$_  $$$$| $$__  $$| $$__  $$| $$|_  $$| $$__  $$| $$  $$$| $$| $$__/   
| $$$/ \  $$$| $$  | $$| $$  \ $$| $$  \ $$| $$  | $$| $$\  $ | $$| $$      
| $$/   \  $$| $$  | $$| $$  | $$|  $$$$$$/| $$  | $$| $$ \/  | $$| $$$$$$$$
|__/     \__/|__/  |__/|__/  |__/ \______/ |__/  |__/|__/     |__/|________/
*/

class WarGame {
    private:
        CardContainer table1{0};
        CardContainer table2{0};
        Deck D{52};
        Player player1{1};
        Player player2{2};
        bool flag = true;   // To get out of loop if player has less thatn 4 cards when going to war
        Card faceDown{0};   // Card to represent a facedown card
        Term::IO io;
    public:
        void deal();
        void compare();
        void displayWinner();
        void goToWar();
        void play();
};

void WarGame::deal() {
    cout << "deal" << endl;
    D.Shuffle();
    D.Shuffle();


    for (int i = 0; i < 52; i++) {
        if (i % 2 ==0)
            player1.hand.Add(D.Remove());
        else
            player2.hand.Add(D.Remove());
    }
}

void WarGame::compare() {
    table1.Add(player1.hand.Remove());
    table2.Add(player2.hand.Remove());


    // Player 1 Wins
    if (*(table1.Back()) > *(table2.Back())) {
        // Display winner and the cards put on the table
        io << Term::fuse((*(table1.Back())).Repr(), (*(table2.Back())).Repr(), false);
        io << "winner" << "\n";

        
        // Add cards on the table to the winning hand
        player1.hand.AddFront(table1.Remove());
        player1.hand.AddFront(table2.Remove());

        // Display each players number of cards after cards are awarded to the winner
        io << "  " << player1.hand.Size() << "      " << player2.hand.Size() << "\n" << "\n";

    }

    // Player 2 Wins
    else if (*(table2.Back()) > *(table1.Back())) {
        io << Term::fuse((*(table1.Back())).Repr(), (*(table2.Back())).Repr(), false);
        io << "       " << "winner" << "\n";


        // Add cards on the table to the winning hand
        player2.hand.AddFront(table2.Remove());
        player2.hand.AddFront(table1.Remove());

        // Display each players number of cards after cards are awarded to the winner
        io << "  " << player1.hand.Size() << "      " << player2.hand.Size() << "\n" << "\n";
    }

    // Payers Tie
    else {
        io << Term::fuse((*(table1.Back())).Repr(), (*(table2.Back())).Repr(), false);
        io << "  " << player1.hand.Size() << "      " << player2.hand.Size() << "\n";
        io << "    WAR" << "\n" << "\n";

        // Go to war
        goToWar();
    }
}

void WarGame::goToWar() {

    // Check to make sure each player has enough cards to go to war
    if (player2.hand.Size() < 4) {
        // put card back in hand
        while (table1.Size() != 0 || table2.Size() != 0) {
            player2.hand.Add(table2.Remove());
            player1.hand.Add(table1.Remove());
        }
        flag = false;
    }
    else if (player1.hand.Size() < 4) {
        // put card back in hand
        while (table1.Size() != 0 || table2.Size() != 0) {
            player2.hand.Add(table2.Remove());
            player1.hand.Add(table1.Remove());
        }
        flag = false;
    }

    // Each player has enough so play four cards to the table
    else {

        for (int i = 0; i < 4; i++) {
        table1.Add(player1.hand.Remove());
        table2.Add(player2.hand.Remove());
        }

        io << Term::fuse((faceDown.ReprBack()), (faceDown.ReprBack()), false);
        io << Term::fuse((faceDown.ReprBack()), (faceDown.ReprBack()), false);
        io << Term::fuse((faceDown.ReprBack()), (faceDown.ReprBack()), false);

        // Player 1 Wins
        if (*(table1.Back()) > *(table2.Back())) {
            // Display winner and the cards put on the table
            io << Term::fuse((*(table1.Back())).Repr(), (*(table2.Back())).Repr(), false);
            io << "winner" << "\n";

            
            // Add cards on the table to the winning hand
            while (table1.Size() != 0 || table2.Size() != 0) {
                player1.hand.AddFront(table1.Remove());
                player1.hand.AddFront(table2.Remove());
            }

            // Display each players number of cards after cards are awarded to the winner
            io << "  " << player1.hand.Size() << "      " << player2.hand.Size() << "\n" << "\n";

        }

        // Player 2 Wins
        else if (*(table2.Back()) > *(table1.Back())) {
            io << Term::fuse((*(table1.Back())).Repr(), (*(table2.Back())).Repr(), false);
            io << "       " << "winner" << "\n";


            // Add cards on the table to the winning hand
            while (table1.Size() != 0 || table2.Size() != 0) {
                player2.hand.AddFront(table2.Remove());
                player2.hand.AddFront(table1.Remove());
            }

            // Display each players number of cards after cards are awarded to the winner
            io << "  " << player1.hand.Size() << "      " << player2.hand.Size() << "\n" << "\n";
        }

        // Payers Tie
        else {
           io << Term::fuse((*(table1.Back())).Repr(), (*(table2.Back())).Repr(), false);
           io << "  " << player1.hand.Size() << "      " << player2.hand.Size() << "\n";
           io << "    WAR" << "\n" << "\n";

           // Go to war
           goToWar();
        }
    }
}

void WarGame::play() {
    
    while (flag && player1.hand.Size() != 0 && player2.hand.Size()) {
        compare();
    }

    if (!flag) {
        if (player1.hand.Size() > player2.hand.Size()) {
            io << "player 2 did not have enough cards to go to war" << "\n";
            io << "FINAL WINNER" << "\n";
            io << "------------" << "\n";
            io << "  player 1  " << "\n";
        }
        else {
            io << "player 1 did not have enough cards to go to war" << "\n";
            io << "FINAL WINNER" << "\n";
            io << "------------" << "\n";
            io << "  player 2  " << "\n";
            io << "final amounts in each hand:" << "\n";
            io << "player1: " << player1.hand.Size() << "\n";
            io << "player2: " << player2.hand.Size() << "\n";
        }
    }

    else if (player2.hand.Size() == 0) {
        io << "FINAL WINNER" << "\n";
        io << "------------" << "\n";
        io << "  player 1  " << "\n";
    }

    else {
        io << "FINAL WINNER" << "\n";
        io << "------------" << "\n";
        io << "  player 2  " << "\n";
    }
}

