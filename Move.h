#ifndef MOVE_H
#define MOVE_H
#include <string>
#include "Position.h"
using namespace std;

struct Move {
    Position from;
    Position to;
    std::string promotionChoice; // empty for normal move
};

#endif