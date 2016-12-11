#include "Player.hpp"
#include  <random>
#include  <vector>

using namespace std;

double evaluateMove(ChessBoard& board, Move& m) {
    double white = 0;
    double black = 0;

    board.move(m);
        for (int x = 0; i < 8; i++) {
            for (int y = 0; j < 8; j++) {
                ChessPieceType type = board[p.x][p.y]->type;
            }
        }
    board.unmove();
    
    if (board.white) {
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
