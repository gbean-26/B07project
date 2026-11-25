#include <string>
#include <vector>
#include "Queen.h"
#include "Board.h"
#include "Directions.h"

Queen::Queen(const std::string &colour): Pieces(colour, colour == "white" ? 'Q' : 'q'){}

std::vector<Position> Queen::possibleMoves(const Board &board, Position from) const {
    return slide(board, from, allDirections, false);
}

std::vector<Position> Queen::captureMoves(const Board &board, Position from) const {
    return slide(board, from, allDirections, true);
}