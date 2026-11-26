#include "player.h"
#include <iostream>
#include <string>
using namespace std;

Player::Player(const string &colour) : colour{colour} {}

string Player::getColour() const {
    return colour;
}

ostream &operator<<(ostream &out, const Player &player) {
    // to impl

    return out;
}
