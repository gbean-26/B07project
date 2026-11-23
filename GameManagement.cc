#include "GameManagement.h"
#include "human.h"
#include "computer.h"
#include <memory>
#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
using namespace std;

static int PlayerType(const string &type) { // local helper
    if (type == "human") {
        return 0;
    }
    for (int level = 1; level <= 4; ++level) {
        string digit = to_string(level);
        if (type == "computer" + digit || type == "computer[" + digit + "]") {
            return level;
        }
    }
    return -1;
}

void GameManagement::handleSetup(const string &command) {
    istringstream input{command};
    string action;
    string extra;

    if (!(input >> action)) { // no input
        return;
    }
    if (action == "+" || action == "-") { // add remove
        string piece;
        string square;
        if (action == "+") {
            if (!(input >> piece >> square) || (input >> extra)) {
                cout << "Invalid command use: + <piece> <square>\n";
                return;
            }
            if (piece.size() != 1 ||
                string{"KQRBNPkqrbnp"}.find(piece[0]) == string::npos) {
                cout << "Invalid piece symbol.\n";
                return;
            }
        } else {
            if (!(input >> square) || (input >> extra)) {
                cout << "Invalid command use: - <square>\n";
                return;
            }
        }

        if (square.size() != 2 ||
            square[0] < 'a' || square[0] > 'h' ||
            square[1] < '1' || square[1] > '8') {
            cout << "Coordinates must be between a1 and h8.\n";
            return;
        }
        // change size of board
        int row = '8' - square[1];
        int col = square[0] - 'a';

        if (action == "+") {
            customSetup.layout[row][col] = piece;
        } else {
            if (customSetup.layout[row][col].empty()) {
                return; // nothing to remove.
            }
            customSetup.layout[row][col] = "";
        }
        board.initialize(customSetup);
        board.print();

    } else if (action == "=") {
        string colour;
        if (!(input >> colour) || (input >> extra)) {
            cout << "Invalid command use: = <white|black>\n";
            return;
        }

        if (colour != "white" && colour != "black") {
            cout << "Colour must be white or black.\n";
            return;
        }
        customSetup.startingColour = colour;
        board.initialize(customSetup);

    } else if (action == "done") {
        if (input >> extra) {
            cout << "Invalid command use: done\n";
            return;
        }
        int whiteKings = 0;
        int blackKings = 0;
        bool invalidPawn = false;

        for (int row = 0; row < 8; ++row) {
            for (int col = 0; col < 8; ++col) {
                const string &piece = customSetup.layout[row][col];

                if (piece == "K") { // check king
                    ++whiteKings;
                } else if (piece == "k") {
                    ++blackKings;
                }

                // check pawn
                if ((piece == "P" || piece == "p") && (row == 0 || row == 7)) {
                    invalidPawn = true;
                }
            }
        }

        if (whiteKings != 1 || blackKings != 1) {
            cout << "Setup requires exactly one king of each colour.\n";
            return;
        }
        if (invalidPawn) {
            cout << "Pawns cannot be on the first or last rank.\n";
            return;
        }
        // run only after checking both kings exist
        if (board.isInCheck("white") || board.isInCheck("black")) {
            cout << "Neither king may be in check during setup.\n";
            return;
        }
        hasCustomSetup = true;
        setupMode = false;
        cout << "Setup complete.\n";

    } else {
        cout << "Setup commands are +, -, =, and done.\n";
    }
}

void GameManagement::startGame(int whiteLevel, int blackLevel) {
    if (gameRunning) {
        cout << "Game is already running.\n";
        return;
    }
    // make player object
    if (whiteLevel == 0) {
        whitePlayer = make_unique<Human>("white");
    } else {
        whitePlayer = make_unique<Computer>("white", whiteLevel);
    }
    if (blackLevel == 0) {
        blackPlayer = make_unique<Human>("black");
    } else {
        blackPlayer = make_unique<Computer>("black", blackLevel);
    }

    BoardSetup setup;
    if (hasCustomSetup) {
        setup = customSetup;
    } else {
        string blackBackRow = "rnbqkbnr"; // black lowercase
        string whiteBackRow = "RNBQKBNR";
        // set defult position
        for (int col = 0; col < 8; ++col) {
            setup.layout[0][col] = blackBackRow[col];
            setup.layout[1][col] = "p";
            setup.layout[6][col] = "P";
            setup.layout[7][col] = whiteBackRow[col];
        }
        setup.startingColour = "white"; // default
    }
    board.initialize(setup);

    // reset
    hasCustomSetup = false;
    setupMode = false;
    gameRunning = true;
    board.print();
    if (board.isStalemate(board.whoseTurn())) {
        cout << "Stalemate!\n";
        updateScore("draw");
        endGame();
    }
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

            Player *currentPlayer = (board.whoseTurn() == "white") 
                ? whitePlayer.get() : blackPlayer.get();
            
            // Computer turn.
            if (!currentPlayer->isHuman()) {
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
                continue;
            }

            // human player turn
            string from;
            string to;
            string promotion;
            string extra; // checks if too many words

            if (!(input >> from >> to)) {
                cout << "Invalid command use: move <from> <to> [promotion]\n";
                board.print();
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
            // make piece type upper, board determines colour
            if (!promotion.empty()) {
                promotion[0] = static_cast<char>(
                    std::toupper(static_cast<unsigned char>(promotion[0]))
                );
            }
            // translates user input to move object to use in board
            Move move{
                Position{'8' - from[1], from[0] - 'a'}, // from, calculate row, col
                Position{'8' - to[1], to[0] - 'a'}, // to
                promotion
            };

            Human *human = static_cast<Human *>(currentPlayer); // casting to human
            human->setMove(move);
            if (!handleMoves(human->chooseMove(board))) { // board fails move
                cout << "Illegal move.\n";
                board.print();
            }

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
                cout << "Invalid command use: game <white-player> <black-player>\n";
                board.print();
                continue;
            }

            // check player input
            int whiteLevel = PlayerType(whiteType);
            int blackLevel = PlayerType(blackType);

            if (whiteLevel == -1 || blackLevel == -1) {
                cout << "Use human, computer1 to computer4, "
                    << "or computer[1] to computer[4].\n";
                continue;
            }
            startGame(whiteLevel, blackLevel);

        } else if (action == "setup") {
            string extra;
            if (input >> extra) {
                cout << "Invalid command use: setup\n";
                board.print();
                continue;
            }
            if (gameRunning) {
                cout << "Cannot enter setup during a game.\n";
                board.print();
                continue;
            }
            // editing an empty board
            // runs handlesetup on the next loop
            customSetup = BoardSetup{};
            hasCustomSetup = false;
            setupMode = true;
            board.initialize(customSetup);
            board.print();

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
    board.print();
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