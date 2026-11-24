#include <string>
#include <vector>
#include "Pawn.h"
#include "Pieces.h"
#include "Position.h"
#include "Board.h"

Pawn::Pawn(const std::string &colour): Pieces(colour, colour == "white" ? 'P' : 'p'){}

std::vector<Position> Pawn::possibleMoves(const Board &board, Position from) const {
    std::vector<Position> moves;
    // White pawns start array row 6 and go up (row number decreases), black pawns vice versa
    int direction = (getColour() == "white" ? -1 : 1);
    int startRow = (getColour() == "white" ? 6 : 1);

    Position one{from.row + direction, from.col};
    if (one.row >= 0 && one.row < 8 && !board.getPieceAt(one)){
        moves.push_back(one);
        // if piece has never moved yet (on starting row), can move 2 squares
        Position two{from.row + direction * 2, from.col};
        if (from.row == startRow && !board.getPieceAt(two)){
            moves.push_back(two);
        }
    }

    return moves;
}
std::vector<Position> Pawn::captureMoves(const Board &board, Position from) const {
    std::vector<Position> moves;
    int direction = (getColour() == "white" ? -1 : 1);
    if (from.row + direction >= 0 && from.row + direction < 8){
        Position left{from.row + direction, from.col - 1};
        Position right{from.row + direction, from.col + 1};
        Pieces *target = board.getPieceAt(left);
        if (left.col >= 0 && left.col < 8 && target && target->getColour() != getColour()){
            moves.push_back(left);
        }
        if (right.col >= 0 && right.col < 8 && target && target->getColour() != getColour()){
            moves.push_back(right);
        }
    }
    // En passant
    Position target = board.enPassantTarget();
    if (target.row == from.row && (target.col == from.col - 1 || target.col == from.col + 1)){
        moves.push_back(target);
    }

    return moves;
}