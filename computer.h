#ifndef COMPUTER_H
#define COMPUTER_H
#include <random>
#include <string>
#include "player.h"
#include "Move.h"

class Computer : public Player {
private:
    int level; // difficulty level (1 - 4)
    mutable std::mt19937 rng; // random engine, seeded once in constructor

    // level 1: random legal move
    Move levelOneMove(const Board &board) const;

    // level 2: prefers capturing moves and checks
    Move levelTwoMove(const Board &board) const;

    // level 3: prefers avoiding capture, capturing moves, and checks
    Move levelThreeMove(const Board &board) const;

    // level 4: something more sophisticated (optional)
    Move levelFourMove(const Board &board) const;

public:
    Computer(const std::string &colour, int level);

    // picks a move based on difficulty level
    Move chooseMove(const Board &board) override;

    bool isHuman() const override;

    int getLevel() const;
};

#endif
