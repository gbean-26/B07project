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

    public:
        std::string getColour() const;
        char getSymbol() const;
        virtual std::vector<Position> possibleMoves(const Board &board, Position from) const = 0;
        virtual std::vector<Position> captureMoves(const Board &board, Position from) const = 0;
        virtual ~Pieces() = default;
};

#endif