#ifndef GAME_MANAGEMENT_H
#define GAME_MANAGEMENT_H
#include <string>
#include <memory>
#include "Move.h"
#include "Board.h"
#include "player.h"
#include "BoardSetup.h"

class GameManagement {
private:
    Board board;
    double whiteScore = 0;
    double blackScore = 0;
    bool gameRunning = false; // ingame check
    bool setupMode = false;
    // ptr for player object for current game
    std::unique_ptr<Player> whitePlayer;
    std::unique_ptr<Player> blackPlayer;
    BoardSetup customSetup;
    bool hasCustomSetup = false;

    // handles setup command for custom position
    void handleSetup(const std::string &command);

    // starts game using selected player and position, 0 means human, and 1–4 are computer levels
    void startGame(int whiteLevel, int blackLevel);

    // reads commmand from user
    std::string readsCommand();

    // attemps to make move, returns true of move successful
    bool handleMoves(const Move &move);

    // ends current game
    void endGame();

    // handles resignation by declaring win for opponent
    void resign();

    // updates cumulative score
    void updateScore(const std::string &result);

    // prints cumulative score for session
    void printScore() const;

public:
    // reads and validates user command
    void run();
};

#endif