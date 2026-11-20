#include "human.h"
#include "Board.h"
#include <string>
using namespace std;

Human::Human(const string &colour) : Player{colour} {}

void Human::setMove(const Move &move) {
    pendingMove = move;
}

Move Human::chooseMove(const Board &board) {
    // human input is already read and parsed by GameManagement,
    // legality is checked later by Board::isLegal()
    return pendingMove;
}

bool Human::isHuman() const {
    return true;
}
