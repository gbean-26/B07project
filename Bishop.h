#ifndef BISHOP_H
#define BISHOP_H

#include <string>
#include <vector>
#include "Pieces.h"
#include "Position.h"

class Bishop: public Pieces {
    public:
        explicit Bishop(const std::string &colour);
        std::vector<Position> possibleMoves(const Board &board, Position from) const override;
        std::vector<Position> captureMoves(const Board &board, Position from) const override;
};

#endif