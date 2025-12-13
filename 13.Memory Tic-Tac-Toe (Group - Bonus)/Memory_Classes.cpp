#include "Memory_Classes.h"
#include <iostream>
#include <cctype>
#include <ctime>

using namespace std;


Memory_Board::Memory_Board() : Board<char>(3, 3) {
    real_board.assign(rows, vector<char>(columns, blank_symbol));
    for (auto &r : board)
        for (auto &c : r)
            c = blank_symbol;
    n_moves = 0;
    srand(static_cast<unsigned int>(time(nullptr)));
}

bool Memory_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    if (x < 0 || x >= rows || y < 0 || y >= columns) return false;

    // must be empty in real_board to place
    if (real_board[x][y] != blank_symbol) return false;

    real_board[x][y] = toupper(mark);


    board[x][y] = '?';

    n_moves++;
    return true;
}

bool Memory_Board::is_win(Player<char>* player) {
    char sym = toupper(player->get_symbol());

    for (int i = 0; i < rows; ++i)
        if (real_board[i][0] == sym && real_board[i][1] == sym && real_board[i][2] == sym)
            return true;

    for (int j = 0; j < columns; ++j)
        if (real_board[0][j] == sym && real_board[1][j] == sym && real_board[2][j] == sym)
            return true;

    if (real_board[0][0] == sym && real_board[1][1] == sym && real_board[2][2] == sym) return true;
    if (real_board[0][2] == sym && real_board[1][1] == sym && real_board[2][0] == sym) return true;

    return false;
}

bool Memory_Board::is_draw(Player<char>* player) {
    return (n_moves == rows * columns && !is_win(player));
}

bool Memory_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

static bool would_win_at(vector<vector<char>>& real_board, int r, int c, char mark) {
    real_board[r][c] = mark;
    bool win = false;
    // rows
    for (int i = 0; i < 3; ++i)
        if (real_board[i][0] == mark && real_board[i][1] == mark && real_board[i][2] == mark)
            win = true;
    // cols
    for (int j = 0; j < 3; ++j)
        if (real_board[0][j] == mark && real_board[1][j] == mark && real_board[2][j] == mark)
            win = true;
    // diags
    if (real_board[0][0] == mark && real_board[1][1] == mark && real_board[2][2] == mark) win = true;
    if (real_board[0][2] == mark && real_board[1][1] == mark && real_board[2][0] == mark) win = true;

    real_board[r][c] = '.';
    return win;
}

pair<int,int> Memory_Board::compute_best_move(char cpuMark) {
    cpuMark = toupper(cpuMark);
    char opp = (cpuMark == 'X') ? 'O' : 'X';

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < columns; ++c) {
            if (real_board[r][c] == blank_symbol) {
                if (would_win_at(real_board, r, c, cpuMark)) {
                    return {r, c};
                }
            }
        }
    }

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < columns; ++c) {
            if (real_board[r][c] == blank_symbol) {
                if (would_win_at(real_board, r, c, opp)) {
                    return {r, c};
                }
            }
        }
    }

    int center = rows / 2;
    if (real_board[center][center] == blank_symbol) return {center, center};

    vector<pair<int,int>> corners = {{0,0},{0,2},{2,0},{2,2}};
    for (auto &p : corners)
        if (real_board[p.first][p.second] == blank_symbol) return p;

    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < columns; ++c)
            if (real_board[r][c] == blank_symbol) return {r, c};

    return {-1, -1};
}

// ---------------- Memory_UI ----------------

Memory_UI::Memory_UI() : UI<char>("Welcome to Memory Tic-Tac-Toe (hidden marks)", 3) {}

Player<char>* Memory_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
         << " player: " << name << " (" << symbol << ")\n";
    return new Player<char>(name, symbol, type);
}

Move<char>* Memory_UI::get_move(Player<char>* player) {
    int x, y;
    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease enter your move x and y (0 to " << (player->get_board_ptr()->get_rows() - 1) << "): ";
        cin >> x >> y;
        return new Move<char>(x, y, player->get_symbol());
    }

    Memory_Board* mb = dynamic_cast<Memory_Board*>(player->get_board_ptr());
    if (mb != nullptr) {
        pair<int,int> mv = mb->compute_best_move(player->get_symbol());
        if (mv.first >= 0) {
            cout << "Computer (" << player->get_name() << ") plays: " << mv.first << ' ' << mv.second << "\n";
            return new Move<char>(mv.first, mv.second, player->get_symbol());
        }
    }

    for (int r = 0; r < player->get_board_ptr()->get_rows(); ++r)
        for (int c = 0; c < player->get_board_ptr()->get_columns(); ++c) {
            return new Move<char>(r, c, player->get_symbol());
        }

    return new Move<char>(0, 0, player->get_symbol());
}