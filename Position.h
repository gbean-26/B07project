#ifndef POSITION_H
#define POSITION_H

// stores struct
struct Position {
    int row;
    int col;

    bool operator==(const Position& other) const {
        return row == other.row && col == other.col;
    }
    
    Position operator+(const Position& other) const {
        return {row + other.row, col + other.col};
    }
    
    Position &operator+=(const Position& other) {
        row += other.row;
        col += other.col;
        return *this;
    }
};

// true if p is on the 8x8 board
inline bool inBounds(Position p) {
    return p.row >= 0 && p.row < 8 && p.col >= 0 && p.col < 8;
}

#endif