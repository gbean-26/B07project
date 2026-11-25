#include <string>
#include <vector>
#include "Bishop.h"
#include "Board.h"
#include "Directions.h"

Bishop::Bishop(const std::string &colour): Pieces(colour, colour == "white" ? 'B' : 'b'){}

std::vector<Position> Bishop::possibleMoves(const Board &board, Position from) const {
    return slide(board, from, diagonalDirections, false);
}

std::vector<Position> Bishop::captureMoves(const Board &board, Position from) const {
    return slide(board, from, diagonalDirections, true);
}