#ifndef MOVE_H
#define MOVE_H
#include <string>
#include "Position.h"

struct Move {
    Position from;
    Position to;
    std::string promotionChoice; // empty for normal move
};

#endif