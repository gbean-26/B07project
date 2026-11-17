#ifndef GAME_MANAGEMENT_H
#define GAME_MANAGEMENT_H
#include <string>
#include "Move.h"

class GameManagement {
private:
    double whiteScore = 0;
    double blackScore = 0;
    bool gameRunning = false; // ingame check

public:
    // handles setup command for custom position
    void handleSetup(const std::string& command);

    // starts game using selected player and position, sets default position if no custom is set
    void startGame();

    // reads and validates user command
    void run();

    // reads commmand from user
    std::string readsCommand();

    // attemps to make move, returns true of move successful
    bool handleMoves(const Move& move);

    // ends current game
    void endGame();

    // handles resignation by declaring win for opponent
    void resign();

    // updates cumulative score
    void updateScore(const std::string& result);

    // prints cumulative score for session
    void printScore() const;
};

#endif