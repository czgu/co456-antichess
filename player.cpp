#include "Player.hpp"
#include  <random>
#include  <vector>

using namespace std;

Player::Player(bool white, ChessBoard* board) : white(white), board(board) {
}

Move Player::makeMove() {
    vector<Move> moves = board->genMoves();

    Move m = moves[rand() % moves.size()];
    board->move(m);

    return m;
}
