#include "GameManagement.h"
#include <iostream>
#include <string>
#include <sstream>
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

        istringstream input{command};
        string action;
        if (!(input >> action)) { // no word to read, then store in action
            continue;
        }

        if (action == "move") {
            if (!gameRunning) {
                cout << "No game is currently running.\n";
                continue;
            }
            string from;
            string to;
            string promotion;
            string extra; // checks if too many words

            if (!(input >> from >> to)) {
                cout << "Invalid input use: move <from> <to> [promotion]\n";
                continue;
            }
            if (input >> promotion) { // add to promotion
                if (input >> extra) { // check if extra words after promotion
                    cout << "Too many arguments.\n";
                    continue;
                }
                // checks promotion
                // check if only one letter, or if letter is not found in String
                if (promotion.size() != 1 || string{"QRBNqrbn"}.find(promotion[0]) == string::npos) {
                    cout << "Invalid promotion choice.\n";
                    continue;
                }
            }

            // validate cord.
            if (from.size() != 2 || to.size() != 2) {
                // invalid cord.
                cout << "Invalid coordinate, format example: e2 or a1\n";
                continue;
            }
            // check cord. bounds
            if (from[0] < 'a' || from[0] > 'h' ||
                    to[0] < 'a' || to[0] > 'h' ||
                    from[1] < '1' || from[1] > '8' ||
                    to[1] < '1' || to[1] > '8') {
                cout << "Coordinates out of bound, must be between a1 and h8.\n";
                continue;
            }
            // translates user input to move object to use in board
            Move move{
                Position{'8' - from[1], from[0] - 'a'}, // from, calculate row, col
                Position{'8' - to[1], to[0] - 'a'}, // to
                promotion
            };

            if (!handleMoves(move)) { // board fails move
                cout << "Illegal move.\n";
            }

        } else if (action == "resign") {
            resign();

        } else if (action == "game") {
            if (gameRunning) {
                cout << "\n";
            }


        } else if (action == "setup") {

        } else {
            cout << "Unknown command.\n";
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