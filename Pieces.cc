#include <string>
#include <cctype>
#include "Pieces.h"
#include "Board.h"

Pieces::Pieces(const std::string &colour, char symbol): colour{colour}, symbol{symbol} {}

std::string Pieces::getColour() const { return colour; }
char Pieces::getSymbol() const { return symbol; }
char Pieces::getType() const { return std::toupper(static_cast<unsigned char>(symbol)); }
bool Pieces::hasMoved() const { return moved;}
void Pieces::setMoved() { moved = true; }

std::vector<Position> Pieces::slide(const Board &board, Position from, const std::vector<Position> &directions, bool captures) const {
    std::vector<Position> moves;
    for (Position direction : directions){
        Position to = from + direction;
        while (inBounds(to)){
            Pieces *target = board.getPieceAt(to);
            if (!target){
                if (!captures) moves.push_back(to);
            } else {
                if (captures && target->getColour() != getColour()) { moves.push_back(to); }
                break;
            }
            to += direction;
        }
    }

    return moves;
}