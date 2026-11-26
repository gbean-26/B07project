#include "stage1.h"
#include "Board.h"
#include "Pieces.h"
#include <random>
#include <string>
#include <vector>
using namespace std;

// addIfLegal removed; Board::legalMoves handles the same logic
// (own king safety, castling, en passant, and one move per promotion choice Q/R/B/N).
// Stage 1 only needs to filter and picks from that list.

vector<Move> legalMovesFrom(const Board &board, Position from) {
    vector<Move> moves;
    Pieces *piece = board.getPieceAt(from);
    if (!piece) {
        return moves;
    }
    // legalMoves already combine possibleMoves and captureMoves, only 1 loop needed
    for (const Move &move : board.legalMoves(piece->getColour())) {
        if (move.from == from) {
            moves.push_back(move);
        }
    }
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
