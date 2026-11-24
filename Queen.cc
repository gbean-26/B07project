#include <string>
#include <vector>
#include "Queen.h"
#include "Board.h"

Queen::Queen(const std::string &colour): Pieces(colour, colour == "white" ? 'Q' : 'q'){}

static const std::vector<Position> queenDirections = {
    {-1,-1}, {-1,0}, {-1,1}, {0,-1}, {0,1}, {1,-1}, {1,0}, {1,1}
};

std::vector<Position> Queen::possibleMoves(const Board &board, Position from) const {
    return slide(board, from, queenDirections, false);
}

std::vector<Position> Queen::captureMoves(const Board &board, Position from) const {
    return slide(board, from, queenDirections, true);
}