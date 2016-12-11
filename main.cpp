#include <iostream>
#include <cstdio>
#include <string>
#include "board.hpp"
#include "player.hpp"

using namespace std;

Move parseString(string in) {
    string s_start = in.substr(0, 2);
    string s_end = in.substr(2, 2);

    int s_start_x = s_start[0] >= 'A' && s_start[0] <= 'Z' ? s_start[0] - 'A' : s_start[0] - 'a';
    int s_end_x = s_end[0] >= 'A' && s_end[0] <= 'Z' ? s_end[0] - 'A' : s_end[0] - 'a';

    vec2 v_start(s_start_x, s_start[1] - '1');
    vec2 v_end(s_end_x, s_end[1] - '1');

    Move m(v_start, v_end);
    if (in.length() > 4) {
        ChessPieceType type = EMPTY;

        char c = in[4];
        c = c >= 'A' ? c - 'A' + 'a' : c;

        switch (c) {
            case 'q':
                type = QUEEN;
                break;
            case 'r':
                type = CASTLE;
                break;
            case 'b':
                type = BISHOP;
                break;
            case 'n':
                type = KNIGHT;
                break;
            default:
                break;
        }

        m.promotion = EMPTY;
    }

    return m;
}

int main() {
    string s;
    cin >> s;

    bool white = s == "white";
    ChessBoard board;
    Player ai(white, &board);
    Player ai2(!white, &board);
    while (true) {
        cin >> s;
        if (s == "b") {
            cout << "UnMove" << endl;
            board.unmove();
            // board.print();
        } else if (s == "n") {
            if (white) {
                Move aiMove = ai.makeMove();
                cout << aiMove.toString() << std::endl;
            } else {
                Move aiMove = ai2.makeMove();
                cout << aiMove.toString() << std::endl;
            }
            board.print();
            white = !white;
        }
    }


    while (true) {
        cin >> s;
        if (s[0] == '$') {
            char command = s[1];
            if (command == 'p') {
                board.print();
            }
        } else {
            Move playerMove = parseString(s);
            board.move(playerMove);

            Move aiMove = ai.makeMove();
            cout << aiMove.toString() << std::endl;
        }
    }
}
