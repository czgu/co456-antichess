#include <iostream>
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
    return Move(v_start, v_end);
}

string parseMove(Move m) {
    char ret[4];

    ret[0] = m.start.x + 'a';
    ret[1] = m.start.y + '1';
    ret[2] = m.end.x + 'a';
    ret[3] = m.end.y + '1';

    return string(ret);
}

int main() {
    string s;
    cin >> s;

    bool white = s == "white";
    ChessBoard board;
    Player ai(white, &board);

    if (white) {
        ai.makeMove();
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
            cout << parseMove(aiMove) << std::endl;
        }
    }
}
