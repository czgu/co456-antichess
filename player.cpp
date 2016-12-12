#include "Player.hpp"
#include  <random>
#include  <vector>

#include <iostream>
using namespace std;

double evaluateBoard(ChessBoard& board) {
    double white = 0;
    double black = 0;

    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            ChessPiece* piece = board.getPiece(vec2(x, y));
            if (piece == nullptr) {
                cerr << "evaluateBoard: nullptr" << endl;
                continue;
            }
            if (piece->type == EMPTY) {
                continue;
            }
            double* score = (piece->white)? &white : &black;
            switch(piece->type) {
                case KING:
                    *score += 200;
                    break;
                case QUEEN:
                    *score += 9;
                    break;
                case CASTLE:
                    *score += 5;
                    break;
                case BISHOP:
                    *score += 3;
                    break;
                case KNIGHT:
                    *score += 3;
                    break;
                case PAWN:
                    *score += 1;
                    break;
                default:
                    break;
            }
        }
    }
    
    if (board.isWhite()) {
        return white - black;
    }
    return black - white;
}

Player::Player(bool white, ChessBoard* board) : white(white), board(board) {
}

Move Player::makeMove() {
    vector<Move> moves = board->genMoves();

    // TODO: come up with smarter AI
    Move m = moves[rand() % moves.size()];
    board->move(m);

    return m;
}
