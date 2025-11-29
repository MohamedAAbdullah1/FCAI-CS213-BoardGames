#include "Diamond_Classes.h"
#include <iostream>

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
    return (r + c >= 2 && r + c <= 6 && abs(r - c) <= 2);
}

bool Diamond_Board::is_win(Player<char>*) { return false; }
bool Diamond_Board::is_draw(Player<char>*) { return n_moves == 13; }
bool Diamond_Board::game_is_over(Player<char>*) { return is_win(nullptr) || is_draw(nullptr); }
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
    if (player->get_type() == PlayerType::HUMAN) {
        cout << "Enter row and column (0-4): ";
        cin >> x >> y;
    } else {
        x = rand() % 5; y = rand() % 5;
    }
    return new Move<char>(x, y, player->get_symbol());
}