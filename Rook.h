#ifndef ROOK_H
#define ROOK_H

#include <string>
#include <vector>
#include "Pieces.h"
#include "Position.h"

class Rook: public Pieces {
    public:
        explicit Rook(const std::string &colour);
        std::vector<Position> possibleMoves(const Board &board, Position from) const override;
        std::vector<Position> captureMoves(const Board &board, Position from) const override;
};

#endif