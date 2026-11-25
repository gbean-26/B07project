#include "Board.h"
#include "Pieces.h"
#include "Pawn.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

Board::~Board() {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            delete grid[row][col];
        }
    }
}

void Board::initialize(const BoardSetup &setup) {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            delete grid[row][col];
            grid[row][col] = nullptr;
            const string &symbol = setup.layout[row][col]; // find piece
            if (symbol.empty()) {
                continue;
            }
            string colour;
            // validate
            if (symbol[0] >= 'A' && symbol[0] <= 'Z') {
                colour = "white";
            } else {
                colour = "black";
            }
            if (symbol == "P" || symbol == "p") {
                grid[row][col] = new Pawn(colour);
            } else if (symbol == "N" || symbol == "n") {
                grid[row][col] = new Knight(colour);
            } else if (symbol == "B" || symbol == "b") {
                grid[row][col] = new Bishop(colour);
            } else if (symbol == "R" || symbol == "r") {
                grid[row][col] = new Rook(colour);
            } else if (symbol == "Q" || symbol == "q") {
                grid[row][col] = new Queen(colour);
            } else if (symbol == "K" || symbol == "k") {
                grid[row][col] = new King(colour);
            }
        }
    }
    currentTurn = setup.startingColour;
}

Pieces *Board::getPieceAt(Position square) const {
    if (!Pieces::inBounds(square)) { // not in board
        return nullptr;
    }
    return grid[square.row][square.col];
}

string Board::whoseTurn() const {
    return currentTurn;
}

bool Board::isLegal(const Move &move) const {
    // check king
    return false;
}

bool Board::updateBoard(const Move &move) {
    // validate, apply move, then next tu rn
    return false;
}

bool Board::isAttacked(Position square, const string &byColour) const {
    if (!Pieces::inBounds(square)) {
        return false;
    }
    // ...
}

