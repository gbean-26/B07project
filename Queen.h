#ifndef QUEEN_H
#define QUEEN_H

#include <string>
#include <vector>
#include "Pieces.h"
#include "Position.h"

class Queen: public Pieces {
    public:
        explicit Queen(const std::string &colour);
        std::vector<Position> possibleMoves(const Board &board, Position from) const override;
        std::vector<Position> captureMoves(const Board &board, Position from) const override;
};

#endif