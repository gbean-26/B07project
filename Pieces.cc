#include <string>
#include "Pieces.h"

Pieces::Pieces(const std::string &colour, char symbol): colour{colour}, symbol{symbol} {}

std::string Pieces::getColour() const { return colour; }
char Pieces::getSymbol() const { return symbol; }