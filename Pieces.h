#ifndef PIECES_H
#define PIECES_H

#include <string>
#include <vector>
#include "Position.h"

class Board;
class Pieces {
    private:
        std::string colour;
        char symbol;
    
    protected:
        Pieces(const std::string &colour, char symbol);

        // Helper function for bishop, rook, queen move calculation.
        // captures = true for captureMoves(), false for possibleMoves()
        std::vector<Position> slide(const Board &board, Position from, 
                                    const std::vector<Position> &directions, bool captures) const;

    public:
        // helper: true if p is on the 8x8 board
        static bool inBounds(Position p);

        std::string getColour() const;
        char getSymbol() const;
        virtual std::vector<Position> possibleMoves(const Board &board, Position from) const = 0;
        virtual std::vector<Position> captureMoves(const Board &board, Position from) const = 0;
        virtual ~Pieces() = default;
};

#endif