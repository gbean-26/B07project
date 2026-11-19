#include "stage1.h"
#include "Board.h"
#include "Pieces.h"
#include <random>
#include <string>
#include <vector>
using namespace std;

// adds move to list if Board says it is legal and it is not already in list
static void addIfLegal(const Board &board, const Move &move, vector<Move> &moves) {
    for (const Move &m : moves) {
        if (m.to.row == move.to.row && m.to.col == move.to.col) {
            return; // duplicate (eg. square is in both possibleMoves and captureMoves)
        }
    }
    // possibleMoves/captureMoves only follow the piece's movement rules,
    // isLegal also checks the move doesnt leave own king in check
    if (board.isLegal(move)) {
        moves.push_back(move);
    }
}

vector<Move> legalMovesFrom(const Board &board, Position from) {
    vector<Move> moves;
    Pieces *piece = board.getPieceAt(from);
    if (!piece) {
        return moves;
    }

    for (const Position &to : piece->possibleMoves(board, from)) {
        addIfLegal(board, Move{from, to, ""}, moves);
    }
    for (const Position &to : piece->captureMoves(board, from)) {
        addIfLegal(board, Move{from, to, ""}, moves);
    }

    /*
        to impl
        pawn reaching last row needs promotionChoice (eg. "Q"),
        needs a way to know the piece is a pawn
    */

    return moves;
}

Move stageOneMove(const Board &board, const string &colour, mt19937 &rng) {
    // each entry holds the legal moves of one piece that can move
    vector<vector<Move>> movablePieces;

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Position square{row, col};
            Pieces *piece = board.getPieceAt(square);
            if (!piece || piece->getColour() != colour) {
                continue; // empty square or opponent piece
            }
            vector<Move> moves = legalMovesFrom(board, square);
            if (!moves.empty()) {
                movablePieces.push_back(moves);
            }
        }
    }

    // no legal moves (checkmate/stalemate), game should end before this
    if (movablePieces.empty()) {
        return Move{{-1, -1}, {-1, -1}, ""};
    }

    // random piece
    uniform_int_distribution<size_t> pickPiece(0, movablePieces.size() - 1);
    const vector<Move> &moves = movablePieces[pickPiece(rng)];

    // random move for that piece
    uniform_int_distribution<size_t> pickMove(0, moves.size() - 1);
    return moves[pickMove(rng)];
}
