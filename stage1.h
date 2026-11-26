#ifndef STAGE1_H
#define STAGE1_H
#include <random>
#include <string>
#include <vector>
#include "Move.h"
#include "Position.h"
using namespace std;

class Board;

// returns every legal move for the piece on square "from" (empty if none)
// reusable for later stages
std::vector<Move> legalMovesFrom(const Board &board, Position from);

// level 1 computer:
// picks a random piece of "colour" that has at least one legal move,
// then picks a random legal move for that piece
// returns a move with from = {-1, -1} if no legal move exists
Move stageOneMove(const Board &board, const std::string &colour, std::mt19937 &rng);

#endif
