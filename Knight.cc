#include <string>
#include <vector>
#include "Knight.h"
#include "Board.h"
#include "Directions.h"

Knight::Knight(const std::string &colour): Pieces(colour, colour == "white" ? 'N' : 'n'){}

std::vector<Position> Knight::possibleMoves(const Board &board, Position from) const {
    std::vector<Position> moves;

    for (Position direction : knightDirections){
        Position to = from + direction;
        if (inBounds(to) && !board.getPieceAt(to)) {
            moves.push_back(to);
        }
    }
    return moves;
}

std::vector<Position> Knight::captureMoves(const Board &board, Position from) const {
    std::vector<Position> moves;
    for (Position direction : knightDirections){
        Position to = from + direction;
        if (!inBounds(to)) {
            continue;
        }
        Pieces *target = board.getPieceAt(to);
        if (target && target->getColour() != getColour()) {
            moves.push_back(to);
        }
    }
    return moves;
}
