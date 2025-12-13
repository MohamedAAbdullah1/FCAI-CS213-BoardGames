#include "Diamond_Classes.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>
#include <cstdlib>
#include <ctime>

using namespace std;

bool is_valid_cell_static(int r, int c) {
    return (r + c >= 2 && r + c <= 6 && abs(r - c) <= 2);
}

bool check_win_static(const vector<vector<char>>& board, char symbol) {
    int dr[] = {0, 1, 1, 1};
    int dc[] = {1, 0, 1, -1};

    bool has_len3[4] = {false, false, false, false};
    bool has_len4[4] = {false, false, false, false};

    for (int d = 0; d < 4; ++d) {
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                if (board[i][j] != symbol) continue;

                int prev_r = i - dr[d];
                int prev_c = j - dc[d];
                bool is_start = true;
                if (prev_r >= 0 && prev_r < 5 && prev_c >= 0 && prev_c < 5 && board[prev_r][prev_c] == symbol) {
                    is_start = false;
                }

                if (is_start) {
                    int count = 0;
                    int r = i, c = j;
                    while (r >= 0 && r < 5 && c >= 0 && c < 5 && board[r][c] == symbol) {
                        count++;
                        r += dr[d];
                        c += dc[d];
                    }

                    if (count == 3) has_len3[d] = true;
                    if (count >= 4) {
                        has_len4[d] = true;
                        has_len3[d] = true;
                    }
                }
            }
        }
    }

    for (int d4 = 0; d4 < 4; ++d4) {
        if (has_len4[d4]) {
            for (int d3 = 0; d3 < 4; ++d3) {
                if (d4 != d3 && has_len3[d3]) {
                    return true;
                }
            }
        }
    }

    return false;
}

Diamond_Board::Diamond_Board() : Board<char>(5, 5) {
    blank_symbol = '.';
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

bool Diamond_Board::update_board(Move<char>* move) {
    int x = move->get_x(), y = move->get_y();
    if (x < 0 || x >= 5 || y < 0 || y >= 5) return false;
    if (!is_valid_diamond_cell(x, y)) return false;
    if (board[x][y] != '.') return false;
    board[x][y] = move->get_symbol();
    n_moves++;
    return true;
}

bool Diamond_Board::is_valid_diamond_cell(int r, int c) const {
    return is_valid_cell_static(r, c);
}

bool Diamond_Board::is_win(Player<char>* player) {
    if (!player) return false;
    return check_win_static(this->board, player->get_symbol());
}

bool Diamond_Board::is_draw(Player<char>* player) {
    return (n_moves == 13 && !is_win(player));
}

bool Diamond_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

void Diamond_Board::display_board_matrix() const {
    cout << "\n";
    cout << "    " << (is_valid_diamond_cell(0,2) ? board[0][2] : ' ') << "\n";
    cout << "   " << board[1][1] << " " << board[1][2] << " " << board[1][3] << "\n";
    cout << "  " << board[2][0] << " " << board[2][1] << " " << board[2][2] << " " << board[2][3] << " " << board[2][4] << "\n";
    cout << " " << board[3][0] << " " << board[3][1] << " " << board[3][2] << " " << board[3][3] << " " << board[3][4] << "\n";
    cout << board[4][0] << " " << board[4][1] << " " << board[4][2] << " " << board[4][3] << " " << board[4][4] << "\n\n";
}

Diamond_UI::Diamond_UI() : UI<char>("Welcome to Diamond Tic-Tac-Toe", 3) {}

Player<char>* Diamond_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Move<char>* Diamond_UI::get_move(Player<char>* player) {
    int x, y;
    char sym = player->get_symbol();

    if (player->get_type() == PlayerType::HUMAN) {
        cout << player->get_name() << " (" << sym << ") - Enter row and column (0-4): ";
        cin >> x >> y;
    } else {
        cout << "\nComputer (" << sym << ") is thinking...\n";

        Board<char>* boardPtr = player->get_board_ptr();
        do {
            x = rand() % 5;
            y = rand() % 5;
        } while (!is_valid_cell_static(x, y) || boardPtr->get_board_matrix()[x][y] != '.');

        cout << "Computer chose: " << x << " " << y << "\n";
    }
    return new Move<char>(x, y, sym);
}