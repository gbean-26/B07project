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

    // Castling
    if (!hasMoved()) {
        int backRow = (getColour() == "white") ? 7 : 0;
        Position kingPosition{backRow, 4};

        // is it on its starting square?
        if (from == kingPosition) {

            // Kingside: rook on h-file, f and g must be empty
            Pieces *rook = board.getPieceAt(Position{backRow, 7});
            if (rook && rook->getType() == 'R' && rook->getColour() == getColour() && !rook->hasMoved() &&
                !board.getPieceAt(Position{backRow, 5}) && !board.getPieceAt(Position{backRow, 6})) {
                moves.push_back(Position{backRow, 6});   // king goes to g-file
            }

            // Queenside: rook on a-file, b, c and d must be empty
            rook = board.getPieceAt(Position{backRow, 0});
            if (rook && rook->getType() == 'R' && rook->getColour() == getColour() && !rook->hasMoved() &&
                !board.getPieceAt(Position{backRow, 1}) && !board.getPieceAt(Position{backRow, 2}) &&
                !board.getPieceAt(Position{backRow, 3})) {
                moves.push_back(Position{backRow, 2});   // king goes to c-file
            }
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