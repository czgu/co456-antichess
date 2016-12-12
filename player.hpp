#pragma once

#include "board.hpp"
#define SEARCH_DEPTH 6

class Player {
public:
    Player(bool white, ChessBoard* board);
    Move makeMove();
    double evaluateBoard(ChessBoard& board);
    double negmaxAlphaBeta(ChessBoard& board, int depth, double alpha, double beta, bool quiescent);
private:
    bool white;
    ChessBoard* board;
    int num_moves;
};
