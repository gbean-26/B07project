#include <iostream>
#include <cctype>
#include <memory>
#include <cstdlib>
#include "Board.h"
#include "Directions.h"
#include "Pieces.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"

Board::Board() = default;
Board::~Board() = default;

std::unique_ptr<Pieces> Board::createPiece(const std::string &symbol){
    unsigned char charSymbol = static_cast<unsigned char>(symbol[0]);
    std::string colour = std::isupper(charSymbol) ? "white" : "black";

    switch(std::toupper(charSymbol)){
        case 'K':
            return std::make_unique<King>(colour);
        case 'Q':
            return std::make_unique<Queen>(colour);
        case 'R':
            return std::make_unique<Rook>(colour);
        case 'B':
            return std::make_unique<Bishop>(colour);
        case 'N':
            return std::make_unique<Knight>(colour);
        case 'P':
            return std::make_unique<Pawn>(colour);
        default:
            return nullptr;
    }
}

void Board::initialize(const BoardSetup &setup){
    // Go through all 64 squares.
    // Explicitly set empty squares to nullptr, which automatically deletes old pieces from previous games
    for (int row = 0; row < 8; ++row){
        for (int col = 0; col < 8; ++col){
            if (!setup.layout[row][col].empty()){
                grid[row][col] = createPiece(setup.layout[row][col]);
            } else {
                grid[row][col] = nullptr;
            }
        }
    }

    // Reset game
    currentTurn = setup.startingColour;
    enPassant = {-1,-1};
}

Pieces* Board::getPieceAt(Position square) const {
    if (!inBounds(square)){ return nullptr; }
    return grid[square.row][square.col].get();
}

std::string Board::whoseTurn() const {
    return currentTurn;
}

// gets a move, and checks if legal
bool Board::isLegal(const Move &move) const {
    // 1. from and to are in bound
    if (!inBounds(move.from) || !inBounds(move.to)) { return false; }

    Pieces* movingPiece = getPieceAt(move.from);
    // 2. There is a piece on from, and it belongs to currentTurn
    if (!movingPiece || movingPiece->getColour() != currentTurn) { return false; }

    // 3. to is in possibleMoves or captureMoves
    bool foundMove = false;
    std::vector<Position> possibleMoves = movingPiece->possibleMoves(*this, move.from);
    std::vector<Position> captureMoves = movingPiece->captureMoves(*this, move.from);
    for (Position m : possibleMoves){
        if (m == move.to){
            foundMove = true;
            break;
        }
    }
    for (Position m : captureMoves){
        if (m == move.to){
            foundMove = true;
            break;
        }
    }
    if (!foundMove) return false;

    // 4. Promotion
    bool isPawn = movingPiece->getType() == 'P';
    int lastRow = (currentTurn == "white") ? 0 : 7;
    bool isPromotion = isPawn && move.to.row == lastRow;
    if (isPromotion) {
        const std::string &choice = move.promotionChoice;
        if (choice != "Q" && choice != "R" && choice != "B" && choice != "N") {
            return false;
        }
    } else if (!move.promotionChoice.empty()) {
        return false;   // no piece letter allowed if move is not a promotion
    }

    // 5. Castling: king moving 2 columns
    if (movingPiece->getType() == 'K' && std::abs(move.to.col - move.from.col) == 2) {
        std::string enemy = (currentTurn == "white") ? "black" : "white";

        if (isInCheck(currentTurn)) return false;

        Position passed{move.from.row, (move.from.col + move.to.col) / 2};
        if (isAttacked(passed, enemy)) return false;
    }

    // 6. move doesn't make king in check/leave one's king in check
    // Check if King is in check after the move
    std::unique_ptr<Pieces> captured = std::move(grid[move.to.row][move.to.col]);
    grid[move.to.row][move.to.col] = std::move(grid[move.from.row][move.from.col]);

    std::unique_ptr<Pieces> enPassantCaptured;
    if (movingPiece->getType() == 'P' && !captured && move.from.col != move.to.col){ // if move is en passant
        enPassantCaptured = std::move(grid[move.from.row][move.to.col]);
    }

    bool safe = !(isInCheck(currentTurn));

    grid[move.from.row][move.from.col] = std::move(grid[move.to.row][move.to.col]);
    grid[move.to.row][move.to.col] = std::move(captured);

    if (enPassantCaptured) {
        grid[move.from.row][move.to.col] = std::move(enPassantCaptured);
    }
    return safe;
}

bool Board::updateBoard(const Move &move) {
    if (!isLegal(move)) return false;

    Pieces *piece = getPieceAt(move.from);

    // Determine move type: en passant/castling/two-square pawn move/promotion/etc
    const bool isEnPassant = (piece->getType() == 'P' && !getPieceAt(move.to) && move.from.col != move.to.col);
    const bool isCastling = (piece->getType() == 'K' && std::abs(move.from.col - move.to.col) == 2);
    const bool isTwoSquarePawnMove = (piece->getType() == 'P' && std::abs(move.from.row - move.to.row) == 2);
    const bool isPromotion = (piece->getType() == 'P' && (move.to.row == 0 || move.to.row == 7));

    // En passant: captured piece needs to be deleted manually
    if (isEnPassant){ grid[move.from.row][move.to.col] = nullptr; }

    // Move piece. Captured piece automatically deleted
    grid[move.to.row][move.to.col] = std::move(grid[move.from.row][move.from.col]);

    // Castling: move rook
    if (isCastling){
        int castleRow = (currentTurn == "white" ? 7 : 0);
        if (move.to.col - move.from.col > 0){ // Kingside
            grid[castleRow][5] = std::move(grid[castleRow][7]);
            getPieceAt({castleRow,5})->setMoved();
        } else { // Queenside
            grid[castleRow][3] = std::move(grid[castleRow][0]);
            getPieceAt({castleRow,3})->setMoved();
        }
    }

    // Promotion: replace piece
    if (isPromotion){
        char promoteType = move.promotionChoice[0];
        if (currentTurn == "black"){ promoteType = std::tolower(static_cast<unsigned char>(promoteType)); }
        grid[move.to.row][move.to.col] = createPiece(std::string(1, promoteType));
        piece = getPieceAt(move.to);
    }

    // Setmoved (for castled rooks, it was done inside isCastling)
    piece->setMoved();

    // Update enPassant
    enPassant = isTwoSquarePawnMove ? move.to : Position{-1, -1};

    // Switch currentTurn
    currentTurn = (currentTurn == "white" ? "black" : "white");

    return true;
}

// Checks if a position is attacked (not piece: castling paths need to be checked)
bool Board::isAttacked(Position square, const std::string &byColour) const {
    // knights
    for (Position direction: knightDirections){
        Pieces *piece = getPieceAt(square + direction);
        if (piece && piece->getColour() == byColour && piece->getType() == 'N') return true;
    }

    // bishops, rooks, queens, king
    for (Position direction : allDirections) {
        bool diagonal = direction.row != 0 && direction.col != 0;
        Position to = square + direction;
        bool firstStep = true;
        while (inBounds(to)) {
            Pieces *piece = getPieceAt(to);
            if (piece) {
                if (piece->getColour() == byColour) {
                    char type = piece->getType();
                    if (type == 'Q') return true;
                    if (type == 'B' && diagonal) return true;
                    if (type == 'R' && !diagonal) return true;
                    if (type == 'K' && firstStep) return true;
                }
                break;
            }
            to += direction;
            firstStep = false;
        }
    }

    // pawn diagonals
    for (Position direction: diagonalDirections){
        if ((byColour == "white" && direction.row == -1) || (byColour == "black" && direction.row == 1)) continue;
        Pieces *piece = getPieceAt(square + direction);
        if (piece && piece->getColour() == byColour && piece->getType() == 'P') return true;
    }

    return false;
}

bool Board::isInCheck(const std::string &colour) const {
    std::string enemy = (colour == "white" ? "black" : "white");
    for (int row = 0; row < 8; ++row){
        for (int col = 0; col < 8; ++col){
            Pieces *piece = grid[row][col].get();
            if (piece && piece->getType() == 'K' && piece->getColour() == colour){
                return isAttacked(Position{row,col}, enemy);
            }
        }
    }
    return false;
}

bool Board::isCheckmate(const std::string &colour) const {
    return (isInCheck(colour) && legalMoves(colour).empty());
}

bool Board::isStalemate(const std::string &colour) const {
    return (!isInCheck(colour) && legalMoves(colour).empty());
}

std::vector<Move> Board::legalMoves(const std::string &colour) const {
    std::vector<Move> legalMoves;
    for (int row = 0; row < 8; ++row){
        for (int col = 0; col < 8; ++col){
            Pieces *piece = getPieceAt(Position{row,col});
            if (!piece || piece->getColour() != colour) continue;
            Position from = Position{row,col};

            std::vector<Position> allMoves = piece->possibleMoves(*this, from);
            std::vector<Position> captureMoves = piece->captureMoves(*this, from);
            allMoves.insert(allMoves.end(), captureMoves.begin(), captureMoves.end());
            
            for (Position to: allMoves){
                Move move = Move{from, to, ""};
                bool isPromotion = piece->getType() == 'P' && (to.row == 0 || to.row == 7);
                // test if promotion is legal
                if (isPromotion) move.promotionChoice = "Q";
                if (!isLegal(move)) continue;
                // add promotion moves if is legal
                if (isPromotion){ 
                    for (const char *choice : {"Q", "R", "B", "N"}) {
                        move.promotionChoice = choice;
                        legalMoves.push_back(move);
                    }
                } else {
                    legalMoves.push_back(move);
                }
            }
        }
    }
    return legalMoves;
}

Position Board::enPassantTarget() const {
    return enPassant;
}

void Board::print() const {
    for (int row = 0; row < 8; ++row){
        std::cout << 8 - row << ' ';
        for (int col = 0; col < 8; ++col){
            Position curr = {row, col};
            if (getPieceAt(curr)){
                std::cout << getPieceAt(curr)->getSymbol();
            } else {
                if ((row + col)%2){ std::cout << '_'; } 
                else { std::cout << ' '; }
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl << "  abcdefgh" << std::endl;
}