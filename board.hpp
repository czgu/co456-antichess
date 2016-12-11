#pragma once
#include <vector>

struct vec2 {
    short x;
    short y;

    vec2();
    vec2(short x, short y);
    void set(short x, short y);
    vec2 add(vec2& v);
    void neg();

    bool within();
};

enum ChessPieceType {
    KING,
    QUEEN,
    CASTLE,
    BISHOP,
    KNIGHT,
    PAWN,
    EMPTY
};

struct Move {
    vec2 start;
    vec2 end;

    Move(vec2 start, vec2 end);
};

struct ChessPiece {
    ChessPieceType type;
    bool white;

    ChessPiece(ChessPieceType type, bool white);

    void genPieceMove(std::vector<Move>& moves, ChessPiece* board[8][8], vec2 p);
    void genPieceDirectedMove(std::vector<Move>& moves, ChessPiece* board[8][8], vec2 p, vec2 d, bool multi);
    char toString();
};

class ChessBoard {
public:
    ChessBoard();
    std::vector<Move> genMoves();
    void move(Move m);
    void print();
private:
    bool whiteTurn;
    ChessPiece* board[8][8];
};
