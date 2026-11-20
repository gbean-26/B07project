#include "GameManagement.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

void GameManagement::handleSetup(const string &command) {
}

void GameManagement::startGame(const string &whiteType, const string &blackType) {
    // Create White's player using whiteType.
    // Create Black's player using blackType.

    // Use the saved custom setup, or build the standard setup.
    // Initialize Board with that setup.

    gameRunning = true;
    board.print();
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
        if (setupMode) { // jump to setup mode after, setupMode is changed last run
                handleSetup(command);
                continue;
            }

        if (action == "move") {
            if (!gameRunning) {
                cout << "No game is currently running.\n";
                board.print();
                continue;
            }

            // computer turn 
            if (currentPlayer->isComputer()) {
                string extra;
                if (input >> extra) {
                    cout << "Computer turn, enter only: move\n";
                    board.print();
                    continue;
                }
                Move move = currentPlayer->chooseMove(board);
                if (!handleMoves(move)) {
                    cout << "Illegal move.\n";
                    board.print();
                }
                board.print();
                continue;
            }

            // human player turn
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
                    board.print();
                    continue;
                }
                // checks promotion
                // check if only one letter, or if letter is not found in String
                if (promotion.size() != 1 || string{"QRBNqrbn"}.find(promotion[0]) == string::npos) {
                    cout << "Invalid promotion choice.\n";
                    board.print();
                    continue;
                }
            }

            // validate cord.
            if (from.size() != 2 || to.size() != 2) {
                // invalid cord.
                cout << "Invalid coordinate, format example: e2 or a1\n";
                board.print();
                continue;
            }
            // check cord. bounds
            if (from[0] < 'a' || from[0] > 'h' ||
                    to[0] < 'a' || to[0] > 'h' ||
                    from[1] < '1' || from[1] > '8' ||
                    to[1] < '1' || to[1] > '8') {
                cout << "Coordinates out of bound, must be between a1 and h8.\n";
                board.print();
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
            board.print();

        } else if (action == "resign") {
            string extra;
            if (input >> extra) {
                cout << "Too many arguments.\n";
                board.print();
                continue;
            }
            resign();

        } else if (action == "game") {
            if (gameRunning) {
                cout << "Game is already running.\n";
                board.print();
                continue;
            }
            string whiteType;
            string blackType;
            string extra;

            if (!(input >> whiteType >> blackType) || (input >> extra)) { // invalid input 
                cout << "Invalid input use: game <white-player> <black-player>\n";
                board.print();
                continue;
            }

            // possible values for white and black player
            bool validWhite =
                whiteType == "human" ||
                whiteType == "computer[1]" ||
                whiteType == "computer[2]" ||
                whiteType == "computer[3]" ||
                whiteType == "computer[4]";
            bool validBlack =
                blackType == "human" ||
                blackType == "computer[1]" ||
                blackType == "computer[2]" ||
                blackType == "computer[3]" ||
                blackType == "computer[4]";

            if (!validWhite || !validBlack) { // not in possible values
                cout << "Players must be human or computer[1] through computer[4].\n";
                board.print();
                continue;
            }
            startGame(whiteType, blackType);

        } else if (action == "setup") {
            string extra;
            if (input >> extra) {
                cout << "Invalid input use: setup\n";
                board.print();
                continue;
            }
            if (gameRunning) {
                cout << "Cannot enter setup during a game.\n";
                board.print();
                continue;
            }
            setupMode = true;

        } else {
            cout << "Unknown command.\n";
        }
    }
    printScore(); // break out from !cin
}

string GameManagement::readsCommand() {
    string command;
    getline(cin, command); // reads input
    return command;
}

bool GameManagement::handleMoves(const Move &move) {
    if (!gameRunning || !board.updateBoard(move)) { // no game or no move
        return false;
    }
    string nextPlayer = board.whoseTurn();

    if (board.isCheckmate(nextPlayer)) {
        string winner = (nextPlayer == "white") ? "black" : "white";

        if (winner == "white") {
            cout << "Checkmate! White wins!\n";
        } else {
            cout << "Checkmate! Black wins!\n";
        }
        updateScore(winner);
        endGame();

    } else if (board.isStalemate(nextPlayer)) {
        cout << "Stalemate!\n";
        updateScore("draw");
        endGame();

    } else if (board.isInCheck(nextPlayer)) {
        if (nextPlayer == "white") {
            cout << "White is in check.\n";
        } else {
            cout << "Black is in check.\n";
        }
    }
    return true;
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