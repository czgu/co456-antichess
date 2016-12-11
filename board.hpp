#pragma once
#include <vector>
#include <string>

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

#define QUIET 0x1
#define CAPTURE 0x2
#define CASTLING 0x4
#define ENPASSANT 0x8
#define PROMOTION 0x10

struct Move {
    vec2 start;
    vec2 end;

    // BitMap
    // 0 : Unknown
    // 1 : Quiet
    // 2 : Capture
    // 3 : Castling
    // 4 : EnPassant
    // 5 : Promotion
    short moveType;

    ChessPieceType promotion;

    Move(vec2 start, vec2 end);
    Move(vec2 start, vec2 end, short moveType);

    std::string toString();
};

struct UnMove {
    vec2 start;
    vec2 end;
    // 1: Capture
    // 2: 
    short moveType;

    UnMove(vec2 start, vec2 end);
};

struct ChessPiece {
    ChessPieceType type;
    bool white;

    ChessPiece(ChessPieceType type, bool white);

    char toString();
};

class ChessBoard {
public:
    ChessBoard();
    std::vector<Move> genMoves();
    void move(Move m);
    void print();

    void identifyMoveType(Move& m);
private:
    void genPieceMove(std::vector<Move>& moves, vec2 p);
    void genPieceDirectedMove(std::vector<Move>& moves, vec2 from, vec2 d, bool multi);

    bool castling[2][2];
    bool checkMate[2];
    short enPassant[2];

    bool white;
    ChessPiece* board[8][8];
};
