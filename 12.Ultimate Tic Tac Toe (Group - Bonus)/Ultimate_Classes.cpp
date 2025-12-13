#include <iostream>
#include <iomanip>
#include <cctype>
#include "Ultimate_Classes.h"

using namespace std;

Ultimate_Board::Ultimate_Board() : Board(9, 9) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = 0;

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            big_board[i][j] = 0;

    next_valid_sub_row = -1;
    next_valid_sub_col = -1;
}

bool Ultimate_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    if (x < 0 || x >= 9 || y < 0 || y >= 9 || board[x][y] != 0) {
        return false;
    }

    int sub_r = x / 3;
    int sub_c = y / 3;

    if (next_valid_sub_row != -1) {
        if (sub_r != next_valid_sub_row || sub_c != next_valid_sub_col) {
            return false;
        }
    }

    if (big_board[sub_r][sub_c] != 0) {

    }

    board[x][y] = toupper(mark);
    n_moves++;

    if (big_board[sub_r][sub_c] == 0 && check_small_board_win(sub_r, sub_c, toupper(mark))) {
        big_board[sub_r][sub_c] = toupper(mark);
    }

    int next_r = x % 3;
    int next_c = y % 3;

    if (big_board[next_r][next_c] != 0 || is_sub_board_full(next_r, next_c)) {
        next_valid_sub_row = -1;
        next_valid_sub_col = -1;
    } else {
        next_valid_sub_row = next_r;
        next_valid_sub_col = next_c;
    }

    return true;
}

bool Ultimate_Board::is_sub_board_full(int r, int c) {
    int start_r = r * 3;
    int start_c = c * 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[start_r + i][start_c + j] == 0) return false;
        }
    }
    return true;
}

bool Ultimate_Board::check_small_board_win(int sub_r, int sub_c, char sym) {
    int r = sub_r * 3;
    int c = sub_c * 3;

    for (int i = 0; i < 3; ++i) {
        if (board[r + i][c] == sym && board[r + i][c + 1] == sym && board[r + i][c + 2] == sym) return true;
        if (board[r][c + i] == sym && board[r + 1][c + i] == sym && board[r + 2][c + i] == sym) return true;
    }

    if (board[r][c] == sym && board[r + 1][c + 1] == sym && board[r + 2][c + 2] == sym) return true;
    if (board[r][c + 2] == sym && board[r + 1][c + 1] == sym && board[r + 2][c] == sym) return true;

    return false;
}

bool Ultimate_Board::is_win(Player<char>* player) {
    char sym = toupper(player->get_symbol());

    for (int i = 0; i < 3; ++i) {
        if (big_board[i][0] == sym && big_board[i][1] == sym && big_board[i][2] == sym) return true;
        if (big_board[0][i] == sym && big_board[1][i] == sym && big_board[2][i] == sym) return true;
    }
    if (big_board[0][0] == sym && big_board[1][1] == sym && big_board[2][2] == sym) return true;
    if (big_board[0][2] == sym && big_board[1][1] == sym && big_board[2][0] == sym) return true;

    return false;
}

bool Ultimate_Board::is_draw(Player<char>* player) {
    return (n_moves == 81 && !is_win(player));
}

bool Ultimate_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

Ultimate_UI::Ultimate_UI() : UI<char>("Welcome to Ultimate Tic-Tac-Toe (9x9)!", 1) {}

Player<char>* Ultimate_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";
    return new Player<char>(name, symbol, type);
}

void Ultimate_UI::display_board_matrix(const vector<vector<char>>& matrix) const {
    cout << "\n";
    cout << "     0 1 2   3 4 5   6 7 8\n";
    cout << "   -------------------------\n";
    for (int i = 0; i < 9; ++i) {
        cout << " " << i << " |";
        for (int j = 0; j < 9; ++j) {
            char c = matrix[i][j];
            if (c == 0) cout << " .";
            else cout << " " << c;

            if ((j + 1) % 3 == 0) cout << " |";
        }
        cout << "\n";
        if ((i + 1) % 3 == 0) cout << "   -------------------------\n";
    }
    cout << endl;
}

Move<char>* Ultimate_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\n" << player->get_name() << ", enter your move (row col) 0-8: ";
        cin >> x >> y;
    }
    else {
        x = rand() % 9;
        y = rand() % 9;
    }
    return new Move<char>(x, y, player->get_symbol());
}