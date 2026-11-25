#include <string>
#include <vector>
#include "King.h"
#include "Board.h"
#include "Directions.h"

King::King(const std::string &colour): Pieces(colour, colour == "white" ? 'K' : 'k'){}

std::vector<Position> King::possibleMoves(const Board &board, Position from) const {
    std::vector<Position> moves;
    for (Position direction: allDirections){
        Position to = from + direction;
        if (inBounds(to) && !board.getPieceAt(to)){
            moves.push_back(to);
        }
    }
    return moves;
}

std::vector<Position> King::captureMoves(const Board &board, Position from) const {
    std::vector<Position> moves;
    for (Position direction: allDirections){
        Position to = from + direction;
        if (!inBounds(to)) {
            continue;
        }
        Pieces *target = board.getPieceAt(to);
        if (target && target->getColour() != getColour()){
            moves.push_back(to);
        }
    }
    return moves;
}