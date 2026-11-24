#ifndef KING_H
#define KING_H

#include <string>
#include <vector>
#include "Pieces.h"
#include "Position.h"

class King: public Pieces {
    public:
        explicit King(const std::string &colour);
        std::vector<Position> possibleMoves(const Board &board, Position from) const override;
        std::vector<Position> captureMoves(const Board &board, Position from) const override;

        // isInCheck should be handled from Board class.
};

#endif