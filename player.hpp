#pragma once

#include "board.hpp"

class Player {
public:
    Player(bool white, ChessBoard* board);
    Move makeMove();
private:
    bool white;
    ChessBoard* board;
};
