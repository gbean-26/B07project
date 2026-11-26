#ifndef BOARD_H
#define BOARD_H
#include <string>
#include "Move.h"
#include "BoardSetup.h"
using namespace std;

class Pieces; // board store into pieces
class Board {
private:
    Pieces *grid[8][8] = {}; // default nullptr
    std::string currentTurn = "white";

public:
    // creates starting position (custom or defult)
    void initialize(const BoardSetup &setup);

    // returns the piece at a square, or nullptr if empty.
    Pieces *getPieceAt(Position square) const;

    // returns whose turn it is.
    std::string whoseTurn() const;

    // checks if move is able to be played (eg. doesnt get king in check)
    bool isLegal(const Move &move) const;

    /*
        theres more methods.. did not add all
    */

};

#endif