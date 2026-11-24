#include <string>
#include <vector>
#include "Bishop.h"
#include "Board.h"

Bishop::Bishop(const std::string &colour): Pieces(colour, colour == "white" ? 'B' : 'b'){}

static const std::vector<Position> bishopDirections = {{-1,-1}, {-1,1}, {1,-1}, {1,1}};

std::vector<Position> Bishop::possibleMoves(const Board &board, Position from) const {
    return slide(board, from, bishopDirections, false);
}

std::vector<Position> Bishop::captureMoves(const Board &board, Position from) const {
    return slide(board, from, bishopDirections, true);
}