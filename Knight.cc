#include <string>
#include <vector>
#include "Knight.h"
#include "Board.h"

Knight::Knight(const std::string &colour): Pieces(colour, colour == "white" ? 'N' : 'n'){}

static const std::vector<Position> knightDirections = {
    {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
    { 1, -2}, { 1, 2}, { 2, -1}, { 2, 1}
};

std::vector<Position> Knight::possibleMoves(const Board &board, Position from) const {
    std::vector<Position> moves;

    for (Position direction : knightDirections){
        Position to{from.row + direction.row, from.col + direction.col};
        if (to.row >= 0 && to.row < 8 && to.col >= 0 && to.col < 8 && !board.getPieceAt(to)) {
            moves.push_back(to);
        }
    }
    return moves;
}

std::vector<Position> Knight::captureMoves(const Board &board, Position from) const {
    std::vector<Position> moves;
    for (Position direction : knightDirections){
        Position to{from.row + direction.row, from.col + direction.col};
        if (to.row < 0 || to.row >= 8 || to.col < 0 || to.col >= 8) {
            continue;
        }
        Pieces *target = board.getPieceAt(to);
        if (target && target->getColour() != getColour()) {
            moves.push_back(to);
        }
    }
    return moves;
}
