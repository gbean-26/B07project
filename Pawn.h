#ifndef PAWN_H
#define PAWN_H

#include <string>
#include <vector>
#include "Pieces.h"
#include "Position.h"

class Pawn: public Pieces {
    public:
        explicit Pawn(const std::string &colour);
        std::vector<Position> possibleMoves(const Board &board, Position from) const override;
        std::vector<Position> captureMoves(const Board &board, Position from) const override;

        // Promotion should be dealt inside Board class.
};


#endif