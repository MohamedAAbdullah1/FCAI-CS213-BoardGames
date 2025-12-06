#include <iostream>
#include <iomanip>
#include <algorithm>
#include "Pyramid_Classes.h"

using namespace std;



Pyramid_Board::Pyramid_Board() : Board<char>(3, 5) {

    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;

    n_moves = 0;
}

bool Pyramid_Board::update_board(Move<char>* move) {
    int r = move->get_x();
    int c = move->get_y();
    char symbol = move->get_symbol();

    if (r < 0 || r >= rows || c < 0 || c >= columns) return false;


    if (r == 0 && c != 2) return false;
    if (r == 1 && (c < 1 || c > 3)) return false;

    // Check if empty
    if (board[r][c] != blank_symbol) return false;

    board[r][c] = symbol;
    n_moves++;
    return true;
}

bool Pyramid_Board::is_win(Player<char>* player) {
    char s = player->get_symbol();

    if (board[1][1] == s && board[1][2] == s && board[1][3] == s) return true;
    // Row 2: (2,0)..(2,2), (2,1)..(2,3), (2,2)..(2,4)
    if (board[2][0] == s && board[2][1] == s && board[2][2] == s) return true;
    if (board[2][1] == s && board[2][2] == s && board[2][3] == s) return true;
    if (board[2][2] == s && board[2][3] == s && board[2][4] == s) return true;

    if (board[0][2] == s && board[1][2] == s && board[2][2] == s) return true;


    if (board[0][2] == s && board[1][1] == s && board[2][0] == s) return true;
    if (board[0][2] == s && board[1][3] == s && board[2][4] == s) return true;

    return false;
}

bool Pyramid_Board::is_draw(Player<char>* player) {
    return (n_moves == 9 && !is_win(player));
}

bool Pyramid_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}


Pyramid_UI::Pyramid_UI() : UI<char>("Welcome to Pyramid Tic-Tac-Toe!", 3) {}

Player<char>* Pyramid_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Move<char>* Pyramid_UI::get_move(Player<char>* player) {
    int x = -1, y = -1;
    if (player->get_type() == PlayerType::HUMAN) {
        cout << player->get_name() << " (" << player->get_symbol() << ") Enter row (0-2) and col (0-4): ";
        cin >> x >> y;
    }
    else {
        // Simple Random AI
        Board<char>* b = player->get_board_ptr();
        vector<pair<int,int>> valid_moves;

        // Collect valid empty spots
        if (b->get_cell(0, 2) == '.') valid_moves.push_back({0,2});
        for (int c=1; c<=3; ++c) if(b->get_cell(1, c) == '.') valid_moves.push_back({1,c});
        for (int c=0; c<=4; ++c) if(b->get_cell(2, c) == '.') valid_moves.push_back({2,c});

        if (!valid_moves.empty()) {
            int idx = rand() % valid_moves.size();
            x = valid_moves[idx].first;
            y = valid_moves[idx].second;
            cout << "Computer chose: " << x << " " << y << endl;
        }
    }
    return new Move<char>(x, y, player->get_symbol());
}

void Pyramid_UI::display_board_matrix(const vector<vector<char>>& matrix) const {

    cout << "\n";
    // Row 0
    cout << "            | " << matrix[0][2] << " |\n";
    cout << "       -------------------\n";

    // Row 1
    cout << "      | " << matrix[1][1] << " | " << matrix[1][2] << " | " << matrix[1][3] << " |\n";
    cout << "   ---------------------------\n";

    // Row 2
    cout << " | " << matrix[2][0] << " | " << matrix[2][1] << " | " << matrix[2][2] << " | " << matrix[2][3] << " | " << matrix[2][4] << " |\n";
    cout << "\n";
}