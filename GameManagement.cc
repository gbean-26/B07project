#include "GameManagement.h"
#include <iostream>
#include <string>
using namespace std;

void GameManagement::handleSetup(const string &command) {
}

void GameManagement::startGame() {
}

// main running function
void GameManagement::run() {
    while (true) {
        string command = readsCommand(); // stores current command
        if (!cin) { // input fails
            break;
        }
        if (command.empty()) {
            continue;
        }

        /*
        to impl
         split the line into the command name and arguments.
         if in setup mode, pass to handleSetup().
         else, identify the command:
            game -> validate player types, then startGame()
            move -> validate arguments, then handleMoves()
            setup -> enter setup mode if no game is running
            resign -> resign() if a game is running
        Report invalid commands or arguments.
        */

    }
    printScore();
}

string GameManagement::readsCommand() {
    string command;
    getline(cin, command); // reads input
    return command;
}

bool GameManagement::handleMoves(const Move &move) {
    return false;
}

void GameManagement::endGame() {
    gameRunning = false;
}

void GameManagement::resign() {
    if (!gameRunning) {
        cout << "No game is currently running.\n";
        return;
    }

    // board class provides turn
    string winner = (board.whoseTurn() == "white") ? "black" : "white"; // deep copy, switch colour
    updateScore(winner);
    if (winner == "white") {
        cout << "White wins!\n";
    } else {
        cout << "Black wins!\n";
    }
    endGame();
}

void GameManagement::updateScore(const string &result) {
    if (result == "white") {
        whiteScore += 1;
    } else if (result == "black") {
        blackScore += 1;
    } else if (result == "draw") {
        whiteScore += 0.5;
        blackScore += 0.5;
    }
}

void GameManagement::printScore() const {
    cout << "Final Score:\n";
    cout << "White: " << whiteScore << '\n';
    cout << "Black: " << blackScore << '\n';
}