#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <string>
#include "Move.h"
using namespace std;

class Board; // player only reads the board, forward declare is enough

// abstract base class for human and computer players
class Player {
protected:
    string colour; // "white" or "black"

public:
    explicit Player(const std::string &colour);
    virtual ~Player() = default;

    // returns the move this player wants to make on the current board
    virtual Move chooseMove(const Board &board) = 0;

    // true for Human, false for Computer
    // lets GameManagement know if "move" needs arguments (eg. move e2 e4)
    virtual bool isHuman() const = 0;

    // returns the colour this player controls
    string getColour() const;

    // prints the player
    friend ostream &operator<<(ostream &out, const Player &player);
};

#endif
