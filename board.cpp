#include "board.hpp"

ChessPiece::ChessPiece(ChessPieceType type, bool white) : type(type), white(white) {}

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


    board[0][7] = new ChessPiece(CASTLE, true);
    board[1][7] = new ChessPiece(KNIGHT, true);
    board[2][7] = new ChessPiece(BISHOP, true);
    board[3][7] = new ChessPiece(QUEEN, true);
    board[4][7] = new ChessPiece(KING, true);
    board[5][7] = new ChessPiece(BISHOP, true);
    board[6][7] = new ChessPiece(KNIGHT, true);
    board[7][7] = new ChessPiece(CASTLE, true);

    for (int i = 0; i < 8; i++) {
        board[i][6] = new ChessPiece(PAWN, true);
    }
}
