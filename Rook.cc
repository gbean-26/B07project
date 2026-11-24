#include <string>
#include <vector>
#include "Rook.h"
#include "Board.h"

Rook::Rook(const std::string &colour): Pieces(colour, colour == "white" ? 'R' : 'r'){}

static const std::vector<Position> rookDirections = {{-1,0}, {1,0}, {0,-1}, {0,1}};

std::vector<Position> Rook::possibleMoves(const Board &board, Position from) const {
    return slide(board, from, rookDirections, false);
}

std::vector<Position> Rook::captureMoves(const Board &board, Position from) const {
    return slide(board, from, rookDirections, true);
}