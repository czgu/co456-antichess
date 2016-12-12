#pragma once

#include "board.hpp"
#define SEARCH_DEPTH 2

class Player {
public:
    Player(bool white, ChessBoard* board);
    Move makeMove();
    double evaluateBoard(ChessBoard& board);
    double negmaxAlphaBeta(ChessBoard& board, bool white, int depth, double alpha, double beta, bool quiescent);
private:
    bool white;
    ChessBoard* board;
};
