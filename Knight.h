#ifndef KNIGHT_H
#define KNIGHT_H

#include <string>
#include <vector>
#include "Pieces.h"
#include "Position.h"

class Knight: public Pieces {
    public:
        explicit Knight(const std::string &colour);
        std::vector<Position> possibleMoves(const Board &board, Position from) const override;
        std::vector<Position> captureMoves(const Board &board, Position from) const override;
};

#endif