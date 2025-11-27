#include "XO_Classes.h"
#include <iostream>
using namespace std;


X_O_Board::X_O_Board() : Board<char>(3,5) {
    for (auto &r : board)
        for (auto &c : r)
            c = ' ';

    valid_cells = {
        {2,0},{2,1},{2,2},{2,3},{2,4},
        {1,1},{1,2},{1,3},
        {0,2}
    };
    for (auto &p : valid_cells)
        board[p.first][p.second] = blank_symbol;
    winning_triples = {
        {0,1,2}, {1,2,3}, {2,3,4},
        {5,6,7},
        {2,6,8},
        {0,5,8}, {4,7,8}
    };
}

bool X_O_Board::update_board(Move<char>* move) {
    int tx = move->get_to_x();
    int ty = move->get_to_y();
    char sym = move->get_symbol();

    auto it = find(valid_cells.begin(), valid_cells.end(), make_pair(tx,ty));
    if (it == valid_cells.end()) return false;
    if (board[tx][ty] != blank_symbol) return false;

    board[tx][ty] = sym;
    increment_moves();
    return true;
}

bool X_O_Board::is_win(Player<char>* player) {
    char sym = player->get_symbol();

    for (auto &t : winning_triples) {
        auto a = valid_cells[t[0]];
        auto b = valid_cells[t[1]];
        auto c = valid_cells[t[2]];

        if (board[a.first][a.second] == sym &&
            board[b.first][b.second] == sym &&
            board[c.first][c.second] == sym)
            return true;
    }
    return false;
}

bool X_O_Board::is_draw(Player<char>* player) {
    return (get_n_moves() >= 9 && !is_win(player));
}

bool X_O_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

bool X_O_Board::input1to9_to_coord(int input, int &x, int &y) {
    if (input < 1 || input > 9) return false;
    static vector<pair<int,int>> map = {
        {2,0},{2,1},{2,2},{2,3},{2,4},
        {1,1},{1,2},{1,3},
        {0,2}
    };
    x = map[input-1].first;
    y = map[input-1].second;
    return true;
}

// ========== UI ==========

XO_UI::XO_UI() : UI<char>("Welcome to FCAI Pyramid X-O", 3) {}

Player<char>* XO_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}
Move<char>* XO_UI::get_move(Player<char>* player) {
    int tx=-1, ty=-1;
    if (player->get_type() == PlayerType::HUMAN) {
        int cell;
        cout << "Enter cell (1..9): ";
        cin >> cell;
        if (!X_O_Board::input1to9_to_coord(cell, tx, ty))
            return new Move<char>(-1,-1, player->get_symbol());
    }
    else {
        Board<char>* b = player->get_board_ptr();
        vector<pair<int,int>> map = {
            {2,0},{2,1},{2,2},{2,3},{2,4},
            {1,1},{1,2},{1,3},
            {0,2}
        };

        for (auto &p : map)
            if (b->get_cell(p.first,p.second)=='.') {
                tx=p.first; ty=p.second;
                break;
            }
    }

    return new Move<char>(tx,ty,player->get_symbol());
}

void XO_UI::display_board_matrix(const vector<vector<char>>& M) const {
    cout << "\n      [" << M[0][2] << "]    (9)\n";
    cout << "   [" << M[1][1] << "][" << M[1][2] << "][" << M[1][3] << "]   (6 7 8)\n";
    cout << "[" << M[2][0] << "][" << M[2][1] << "][" << M[2][2] << "][" << M[2][3] << "][" << M[2][4] << "]  (1 2 3 4 5)\n\n";
}