#ifndef BOARD_H
#define BOARD_H
#include <string>
#include "Move.h"
#include "BoardSetup.h"
#include "Position.h"
#include <vector>

class Pieces; // board store into pieces
class Board {
private:
    Pieces *grid[8][8] = {}; // default nullptr
    std::string currentTurn = "white";

public:
    Board() = default;
    ~Board();
    // prevents copying
    Board(const Board &) = delete;
    Board &operator=(const Board &) = delete;

    // creates starting position (custom or defult)
    void initialize(const BoardSetup &setup);

    // returns the piece at a square, or nullptr if empty.
    Pieces *getPieceAt(Position square) const;

    // returns whose turn it is.
    std::string whoseTurn() const;

    // checks if move is able to be played (eg. doesnt get king in check)
    bool isLegal(const Move &move) const;

    bool updateBoard(const Move &move);

    bool isAttacked(Position square, const std::string &byColour) const;
    
    bool isInCheck(const std::string &colour) const;
    
    bool isCheckmate(const std::string &colour) const;

    bool isStalemate(const std::string &colour) const;

    // Returns all legal moves for the specified colour.
    std::vector<Move> legalMoves(const std::string &colour) const;

    // Pawn piece needs board to check if en passant is possible. 
    // Return coordinate of captureable target, or {-1, -1} if none.
    Position enPassantTarget() const;

    void print() const;
};

#endif
