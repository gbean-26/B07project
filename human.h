#ifndef HUMAN_H
#define HUMAN_H
#include <string>
#include "player.h"
#include "Move.h"

class Human : public Player {
private:
    Move pendingMove; // move parsed from the user's "move" command

public:
    explicit Human(const std::string &colour);

    // stores the move GameManagement parsed from input (eg. move e7 e8 Q)
    void setMove(const Move &move);

    // returns the move entered by the user
    Move chooseMove(const Board &board) override;

    bool isHuman() const override;
};

#endif
