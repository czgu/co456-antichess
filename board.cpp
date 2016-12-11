#include "board.hpp"
#include <iostream>

using namespace std;

vec2::vec2() : x(0), y(0) {}
vec2::vec2(short x, short y) : x(x), y(y) {}

void vec2::set(short x, short y) {
    this->x = x;
    this->y = y;
}

vec2 vec2::add(vec2& v) {
    vec2 ret;

    ret.x = v.x + this->x;
    ret.y = v.y + this->y;

    return ret;
}

void vec2::neg() {
    x = -x;
    y = -y;
}

bool vec2::within() {
    if (x < 8 && y < 8 && x >= 0 && y >= 0) {
        return true;
    }
    return false;
}

Move::Move(vec2 start, vec2 end) : start(start), end(end) {}

void ChessPiece::genPieceDirectedMove(std::vector<Move>& moves, ChessPiece* board[8][8], vec2 from, vec2 d, bool multi) {
    do {
        vec2 to = from.add(d);

        if (!to.within()) {
            break;
        }

        ChessPiece* cp = board[to.x][to.y];
        if (cp != 0 && cp->white == this->white) {
            break;
        }

        moves.push_back(Move(from, to));

        d = d.add(d);
    } while (multi);
}

void ChessPiece::genPieceMove(vector<Move>& moves, ChessPiece* board[8][8], vec2 p) {
    vec2 d(0, 0);

    switch(type) {
        case KING:
             for (int sign = 0; sign < 2; sign ++) {
                d.set(1, 0); if (sign) d.neg();
                genPieceDirectedMove(moves, board, p, d, false);
                d.set(0, 1); if (sign) d.neg();
                genPieceDirectedMove(moves, board, p, d, false);
                d.set(1, 1); if (sign) d.neg();
                genPieceDirectedMove(moves, board, p, d, false);
                d.set(-1, 1); if (sign) d.neg();
                genPieceDirectedMove(moves, board, p, d, false);
            }
            break;
        case QUEEN:
            for (int sign = 0; sign < 2; sign ++) {
                d.set(1, 0); if (sign) d.neg();
                genPieceDirectedMove(moves, board, p, d, true);
                d.set(0, 1); if (sign) d.neg();
                genPieceDirectedMove(moves, board, p, d, true);
                d.set(1, 1); if (sign) d.neg();
                genPieceDirectedMove(moves, board, p, d, true);
                d.set(-1, 1); if (sign) d.neg();
                genPieceDirectedMove(moves, board, p, d, true);
            }
            break;
        case CASTLE:
            for (int sign = 0; sign < 2; sign ++) {
                d.set(1, 0); if (sign) d.neg();
                genPieceDirectedMove(moves, board, p, d, true);
                d.set(0, 1); if (sign) d.neg();
                genPieceDirectedMove(moves, board, p, d, true);
            }
            break;
        case BISHOP:
            for (int sign = 0; sign < 2; sign ++) {
                d.set(1, 1); if (sign) d.neg();
                genPieceDirectedMove(moves, board, p, d, true);
                d.set(-1, 1); if (sign) d.neg();
                genPieceDirectedMove(moves, board, p, d, true);
            }
            break;
        case KNIGHT:
            for (int sign = 0; sign < 2; sign++) {
                d.set(2, 1); if (sign) d.neg();
                genPieceDirectedMove(moves, board, p, d, false);
                d.set(1, 2); if (sign) d.neg();
                genPieceDirectedMove(moves, board, p, d, false);
                d.set(-2, 1); if (sign) d.neg();
                genPieceDirectedMove(moves, board, p, d, false);
                d.set(-1, 2); if (sign) d.neg();
                genPieceDirectedMove(moves, board, p, d, false);
            }
            break;
        case PAWN:
            d.set(0, 1);

            if (!white) {
                d.neg();
            }

            genPieceDirectedMove(moves, board, p, d, false);
            break;
        default:
            break;
    }
}

ChessPiece::ChessPiece(ChessPieceType type, bool white) : type(type), white(white) {}

char ChessPiece::toString() {
    switch(type) {
        case KING:
            return white ? 'K' : 'k';
            break;
        case QUEEN:
            return white ? 'Q' : 'q';
            break;
        case CASTLE:
            return white ? 'C' : 'c';
            break;
        case BISHOP:
            return white ? 'B' : 'b';
            break;
        case KNIGHT:
            return white ? 'N' : 'n';
            break;
        case PAWN:
            return white ? 'P' : 'p';
            break;
        default:
            break;
    }
    return ' ';
}

ChessBoard::ChessBoard() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = 0;
        }
    }

    board[0][0] = new ChessPiece(CASTLE, true);
    board[1][0] = new ChessPiece(KNIGHT, true);
    board[2][0] = new ChessPiece(BISHOP, true);
    board[3][0] = new ChessPiece(QUEEN, true);
    board[4][0] = new ChessPiece(KING, true);
    board[5][0] = new ChessPiece(BISHOP, true);
    board[6][0] = new ChessPiece(KNIGHT, true);
    board[7][0] = new ChessPiece(CASTLE, true);

    for (int i = 0; i < 8; i++) {
        board[i][1] = new ChessPiece(PAWN, true);
    }

    board[0][7] = new ChessPiece(CASTLE, false);
    board[1][7] = new ChessPiece(KNIGHT, false);
    board[2][7] = new ChessPiece(BISHOP, false);
    board[3][7] = new ChessPiece(QUEEN, false);
    board[4][7] = new ChessPiece(KING, false);
    board[5][7] = new ChessPiece(BISHOP, false);
    board[6][7] = new ChessPiece(KNIGHT, false);
    board[7][7] = new ChessPiece(CASTLE, false);

    for (int i = 0; i < 8; i++) {
        board[i][6] = new ChessPiece(PAWN, false);
    }

    whiteTurn = true;
}

vector<Move> ChessBoard::genMoves() {
    vector<Move> ret;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j] != NULL && whiteTurn == board[i][j]->white) {
                board[i][j]->genPieceMove(ret, board, vec2(i, j));
            }
        }
    }

    return ret;
}

void ChessBoard::move(Move m) {
    ChessPiece* start = board[m.start.x][m.start.y];
    ChessPiece* end = board[m.end.x][m.end.y];

    board[m.start.x][m.start.y] = 0;
    if (end != 0) { // Quiet move
        delete end;
    }
    board[m.end.x][m.end.y] = start;

    whiteTurn = !whiteTurn;
}

void ChessBoard::print() {
    for (int j = 7; j >= 0; j--) {
        for (int i = 0; i < 8; i++) {
            ChessPiece* cp = board[i][j];
            if (cp == 0) {
                cout << " ";
            } else {
                cout << cp->toString();
            }
        }
        cout << endl;
    }
}
