#pragma once

enum ChessPieceType {
    KING,
    QUEEN,
    CASTLE,
    BISHOP,
    KNIGHT,
    PAWN
};

struct ChessPiece {
    ChessPieceType type;
    bool white;

    ChessPiece(ChessPieceType type, bool white);
};

class ChessBoard {
public:
    ChessBoard();
private:
    ChessPiece* board[8][8];
};
