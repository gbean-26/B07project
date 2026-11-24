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
    if (inBounds(one) && !board.getPieceAt(one)){
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

    // normal captures: one square diagonally forward
    for (int side : {-1, 1}){
        Position diagonal{from.row + direction, from.col + side};
        if (!inBounds(diagonal)){
            continue; // check before calling getPieceAt
        }
        Pieces *target = board.getPieceAt(diagonal);
        if (target && target->getColour() != getColour()){
            moves.push_back(diagonal);
        }
    }

    // en passant: enPassantTarget() is the enemy pawn that just moved 2 squares
    Position targetPosition = board.enPassantTarget();
    if (inBounds(targetPosition) && targetPosition.row == from.row && (targetPosition.col == from.col - 1 || targetPosition.col == from.col + 1)){
        Pieces *target = board.getPieceAt(targetPosition);
        if (target && target->getColour() != getColour()){
            moves.push_back(Position{from.row + direction, targetPosition.col});
        }
    }

    return moves;
}