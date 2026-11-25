#include <string>
#include <vector>
#include "Rook.h"
#include "Board.h"
#include "Directions.h"

Rook::Rook(const std::string &colour): Pieces(colour, colour == "white" ? 'R' : 'r'){}

std::vector<Position> Rook::possibleMoves(const Board &board, Position from) const {
    return slide(board, from, straightDirections, false);
}

std::vector<Position> Rook::captureMoves(const Board &board, Position from) const {
    return slide(board, from, straightDirections, true);
}