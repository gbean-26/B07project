#ifndef DIRECTIONS_H
#define DIRECTIONS_H

#include <vector>
#include "Position.h"

// Shared tables used by Pieces and Board
// "inline" (C++17+) gives one copy for the whole program

inline const std::vector<Position> knightDirections = {
    {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
    { 1, -2}, { 1, 2}, { 2, -1}, { 2, 1}
};

inline const std::vector<Position> diagonalDirections = {
    {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
};

inline const std::vector<Position> straightDirections = {
    {-1, 0}, {1, 0}, {0, -1}, {0, 1}
};

inline const std::vector<Position> allDirections = {
    {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}
};

#endif
