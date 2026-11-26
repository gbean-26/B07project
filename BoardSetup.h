#ifndef BOARD_SETUP_H
#define BOARD_SETUP_H
#include <string>
using namespace std;

struct BoardSetup {
    std::string layout[8][8]; // store piece name, empty for no piece
    std::string startingColour = "white"; // default
};

#endif