#include "Player.hpp"
#include  <random>
#include  <vector>
#include <cfloat>
#include <iostream>

#include <iostream>
using namespace std;

double Player::evaluateBoard(ChessBoard& board) {
    double black = 0;
    double white = 0;

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

double Player::negmaxAlphaBeta(ChessBoard& board, bool white, int depth, double alpha, double beta, bool quiescent) {
    if ((depth <= 0 && !quiescent) || depth < -2) {
        if (white == this->white) {
            return evaluateBoard(board);
        } else {
            return -evaluateBoard(board);
        }
    }


    vector<Move> moves = board.genMoves();
    double best = -DBL_MAX, temp;

    for (Move& m : moves) {
        board.move(m);

        quiescent = (m.moveType & CAPTURE);
        temp = -negmaxAlphaBeta(board, !white, depth - 1, -beta, -alpha, quiescent);
        board.unmove();

        if (temp > best) {
            best = temp;
            if (temp > alpha) {
                alpha = temp;
            }
        }

        if (alpha > beta) {
            break;
        }
    }

    return best;
}

Player::Player(bool white, ChessBoard* board) : white(white), board(board) {
}

Move Player::makeMove() {
    vector<Move> moves = board->genMoves();
    vector<Move> bestMoves;

    double best = -DBL_MAX, temp;
    for (Move& m : moves) {
        board->move(m);
        bool quiescent = (m.moveType & CAPTURE);
        temp = -negmaxAlphaBeta(*board, !white, SEARCH_DEPTH, -DBL_MAX, DBL_MAX, quiescent);

        if (temp > best) {
            best = temp;
            bestMoves.clear();
        }
        if (temp == best) {
            bestMoves.push_back(m);
        }

        board->unmove();
    }

    cout << "moves.length: " << moves.size() << endl;
    Move move = bestMoves[rand() % bestMoves.size()];
    board->move(move);

    return move;
}
