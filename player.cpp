#include "Player.hpp"
#include  <random>
#include  <vector>

using namespace std;

double evaluateMove(ChessBoard& board, Move& m) {
    double white = 0;
    double black = 0;

    board.move(m);
        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++) {
                ChessPiece* piece = board.getPiece(vec2(x, y));
                //ChessPieceType type = board[x][y]->type;
                //double* score = (
            }
        }
    board.unmove();
    
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
