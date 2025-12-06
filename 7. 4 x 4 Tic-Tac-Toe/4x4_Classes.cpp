#include <iostream>
#include <iomanip>
#include <cctype>
#include "4x4_Classes.h"
#include <cmath> // لـ abs
#include <ranges> // تم إزالة الاستخدام غير الضروري

using namespace std;

X4x4_Board :: X4x4_Board() : Board(4, 4) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
    board[0][0] = 'O' ;
    board[0][2] = 'O' ;
    board[0][3] = 'X' ;
    board[0][1] = 'X' ;
    board[3][0] = 'X' ;
    board[3][3] = 'O' ;
    board[3][1] = 'O' ;
    board[3][2] = 'X' ;
}
bool X4x4_Board::update_board(Move<char>* move) {
    X4x4_Move* x4x4_move = static_cast<X4x4_Move*>(move);

    int x1 = x4x4_move->get_from_x();
    int y1 = x4x4_move->get_from_y();
    int x2 = x4x4_move->get_to_x();
    int y2 = x4x4_move->get_to_y();
    char symbol = x4x4_move->get_symbol();

    if (x1 < 0 || x1 >= rows || y1 < 0 || y1 >= columns) return false;
    if (x2 < 0 || x2 >= rows || y2 < 0 || y2 >= columns) return false;

    if (board[x1][y1] != symbol) return false;
    if (board[x2][y2] != blank_symbol) return false;

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    if (!((dx == 1 && dy == 0) || (dx == 0 && dy == 1))) return false;

    board[x1][y1] = blank_symbol;
    board[x2][y2] = symbol;

    return true;
}

bool X4x4_Board::is_win(Player<char>* player) {
    const char sym = player->get_symbol();

    auto all_equal = [&](char a, char b, char c) {
        return a == b && b == c && a != blank_symbol;
        };

    for (int i = 0; i < rows; ++i) {
        if ((all_equal(board[i][0], board[i][1], board[i][2]) && board[i][0] == sym) ||
            (all_equal(board[0][i], board[1][i], board[2][i]) && board[0][i] == sym) ||
            (all_equal(board[i][1], board[i][2], board[i][3]) && board[i][1] == sym) ||
            (all_equal(board[1][i], board[2][i], board[3][i]) && board[1][i] == sym) )
            return true;
    }

    for (int  i = 0 ; i<= 3 ; i++) {
        for (int j =0 ; j <4 ; j++) {
            if (i+2 < 4 && j+2 < 4) {
                if (all_equal(board [i][j] ,board[i+1] [j+1] ,board [i+2][j+2] ) && board [i][j] == sym )
                    return true;
            }
            if (i+2 <4 && j-2 >-1 ) {
                if (all_equal (board [i][j] ,board[i+1] [j-1] ,board [i+2][j-2]) && board [i][j] == sym )
                    return true;
            }
        }
    }
    return false;
}

bool X4x4_Board::is_draw(Player<char>* player) {
    return (n_moves == 16 && !is_win(player));
}

bool X4x4_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

X4x4_UI::X4x4_UI() : UI<char>("Welcome to 4x4 FCAI X-O Game (Move your marks)", 4) {}

Player<char>* X4x4_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* X4x4_UI::get_move(Player<char>* player) {
    int xf, yf ,xt ,yt;
    char symbol = player->get_symbol();

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease enter your move x_From and y_From and x_To and y_TO (0 to 3): ";
        cin >> xf >> yf >> xt >> yt ;

    }
    else if (player->get_type() == PlayerType::COMPUTER){
        Board<char>* boardPtr = player->get_board_ptr();
        xf = -1;
        for (int i =0  ;i<=3 ; i++) {
            for (int j=0 ; j< 4 ; j++) {
                if (boardPtr->get_cell(i, j) == symbol) {
                    if (i+1 < 4 && boardPtr->get_cell(i+1, j) == '.') {
                        xf = i; yf = j; xt = i+1; yt = j;
                        goto chosen;
                    }
                    else if (i-1 >= 0 && boardPtr->get_cell(i-1, j) == '.') {
                        xf = i; yf = j; xt = i-1; yt = j;
                        goto chosen;
                    }
                    else if (j+1< 4 && boardPtr->get_cell(i, j+1) == '.') {
                        xf = i; yf = j; xt = i; yt = j+1;
                        goto chosen;
                    }
                    else if (j-1>=0  && boardPtr->get_cell(i, j-1) == '.') {
                        xf = i; yf = j; xt = i; yt = j-1;
                        goto chosen;
                    }
                }
            }
        }
        chosen:;

        if (xf == -1) {
             cout << "\nComputer failed to find a move (Draw likely).\n";
             return new X4x4_Move(-1, -1, -1, -1, symbol);
        }
    }
    return new X4x4_Move(xf, yf,xt ,yt , symbol);
}