#include "computer.h"
#include "Board.h"
#include "stage1.h"
#include <chrono>
#include <random>
#include <string>
using namespace std;

// seeded with the clock (std::random_device gives the same numbers every run on MinGW)
Computer::Computer(const string &colour, int level)
    : Player{colour}, level{level},
      rng{static_cast<unsigned>(chrono::steady_clock::now().time_since_epoch().count())} {}

Move Computer::chooseMove(const Board &board) {
    switch (level) {
        case 1: return levelOneMove(board);
        case 2: return levelTwoMove(board);
        case 3: return levelThreeMove(board);
        default: return levelOneMove(board);
    }
}

bool Computer::isHuman() const {
    return false;
}

int Computer::getLevel() const {
    return level;
}

Move Computer::levelOneMove(const Board &board) const {
    return stageOneMove(board, colour, rng);
}

Move Computer::levelTwoMove(const Board &board) const {
    // prefer captures and checks, otherwise random legal move
    return Move{};
}

Move Computer::levelThreeMove(const Board &board) const {
    // prefer avoiding capture, then captures and checks, otherwise random
    return Move{};
}

