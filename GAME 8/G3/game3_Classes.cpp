/**
 * XO_Classes.h
 * Implementation for 5x5 Tic-Tac-Toe where players place marks,
 * game ends when 24 moves are played (one empty cell remains),
 * winner = player with more 3-in-a-row sequences (horizontal/vertical/diagonal).
 */

#ifndef game3h_CLASSES_H
#define game3h_CLASSES_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cctype>
#include <vector>
using namespace std;

class X_O_Board : public Board<char> {
private:
    char blank_symbol = '.';
public:
    X_O_Board();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override { return false; } // not used for immediate win
    bool is_lose(Player<char>* player) override { return false; }
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

    int count_three_in_row(char sym);
};

class XO_UI : public UI<char> {
public:
    XO_UI();
    ~XO_UI() {};
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
};

#endif


X_O_Board :: X_O_Board() : Board<char>(5, 5) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
    n_moves = 0;
}

bool X_O_Board::update_board(Move<char>* move) {
    int xt = move->get_x();
    int yt = move->get_y();
    char symbol = move->get_symbol();

    if (xt < 0 || xt >= rows || yt < 0 || yt >= columns) return false;
    if (board[xt][yt] != blank_symbol) return false;

    board[xt][yt] = symbol;
    ++n_moves;
    return true;
}

bool X_O_Board::is_draw(Player<char>* player) {
    return (n_moves >= 24);
}

bool X_O_Board::game_is_over(Player<char>* player) {
    return (n_moves >= 24);
}

int X_O_Board::count_three_in_row(char sym) {
    int R = rows;
    int C = columns;
    int cnt = 0;
    for (int r=0;r<R;++r){
        for (int c=0;c+2<C;++c){
            if (board[r][c]==sym && board[r][c+1]==sym && board[r][c+2]==sym) cnt++;
        }
    }
    for (int c=0;c<C;++c){
        for (int r=0;r+2<R;++r){
            if (board[r][c]==sym && board[r+1][c]==sym && board[r+2][c]==sym) cnt++;
        }
    }
    for (int r=0;r+2<R;++r){
        for (int c=0;c+2<C;++c){
            if (board[r][c]==sym && board[r+1][c+1]==sym && board[r+2][c+2]==sym) cnt++;
        }
    }
    for (int r=0;r+2<R;++r){
        for (int c=2;c<C;++c){
            if (board[r][c]==sym && board[r+1][c-1]==sym && board[r+2][c-2]==sym) cnt++;
        }
    }
    return cnt;
}


XO_UI::XO_UI() : UI<char>("Welcome to 5x5 FCAI X-O (place marks, 3-in-a-row counts)", 3) {}

Player<char>* XO_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* XO_UI::get_move(Player<char>* player) {
    int xt = -1, yt = -1;
    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease enter your move row and column (0 to 4): ";
        cin >> xt >> yt;
    }
    else if (player->get_type() == PlayerType::COMPUTER){
        Board<char>* b = player->get_board_ptr();
        for (int i = 0; i < b->get_rows(); ++i) {
            for (int j = 0; j < b->get_columns(); ++j) {
                if (b->get_cell(i,j) == '.') {
                    xt = i; yt = j;
                    goto chosen;
                }
            }
        }
        chosen:;
    }
    return new Move<char>(xt, yt ,player->get_symbol());
}