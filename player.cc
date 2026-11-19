#include "player.h"
#include <string>
using namespace std;

Player::Player(const string &colour) : colour{colour} {}

string Player::getColour() const {
    return colour;
}
