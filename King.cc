#include <string>
#include <vector>
#include "King.h"
#include "Board.h"

King::King(const std::string &colour): Pieces(colour, colour == "white" ? 'K' : 'k'){}

static const std::vector<Position> kingDirections = {
    {-1,-1}, {-1,0}, {-1,1}, {0,-1}, {0,1}, {1,-1}, {1,0}, {1,1}
};

std::vector<Position> King::possibleMoves(const Board &board, Position from) const {
    std::vector<Position> moves;
    for (Position direction: kingDirections){
        Position to{from.row + direction.row, from.col + direction.col};
        if (to.row >= 0 && to.row < 8 && to.col >= 0 && to.col < 8 && !board.getPieceAt(to)){
            moves.push_back(to);
        }
    }
    return moves;
}

std::vector<Position> King::captureMoves(const Board &board, Position from) const {
    std::vector<Position> moves;
    for (Position direction: kingDirections){
        Position to{from.row + direction.row, from.col + direction.col};
        if (to.row < 0 || to.row >= 8 || to.col < 0 || to.col >= 8) {
            continue;
        }
        Pieces *target = board.getPieceAt(to);
        if (target && target->getColour() != getColour()){
            moves.push_back(to);
        }
    }
    return moves;
}