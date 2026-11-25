#include <string>
#include "Pieces.h"
#include "Board.h"

Pieces::Pieces(const std::string &colour, char symbol): colour{colour}, symbol{symbol} {}

std::string Pieces::getColour() const { return colour; }
char Pieces::getSymbol() const { return symbol; }

std::vector<Position> Pieces::slide(const Board &board, Position from, const std::vector<Position> &directions, bool captures) const {
    std::vector<Position> moves;
    for (Position direction : directions){
        Position to{from.row + direction.row, from.col + direction.col};
        while (inBounds(to)){
            Pieces *target = board.getPieceAt(to);
            if (!target){
                if (!captures) moves.push_back(to);
            } else {
                if (captures && target->getColour() != getColour()) { moves.push_back(to); }
                break;
            }
            to.row += direction.row;
            to.col += direction.col;
        }
    }

    return moves;
}