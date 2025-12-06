#include "game3h_Classes.h"

GAME3_Board::GAME3_Board() : Board<char>(5, 5) { n_moves = 0; }

bool GAME3_Board::update_board(Move<char>* move) {
    if (move->get_x() < 0 || move->get_x() >= 5 || move->get_y() < 0 || move->get_y() >= 5) return false;
    if (board[move->get_x()][move->get_y()] != 0) return false;
    board[move->get_x()][move->get_y()] = move->get_symbol();
    n_moves++;
    return true;
}

bool GAME3_Board::is_win(Player<char>* player) {
    if (n_moves == 25) {
        return true;
    }
    return false;
}
bool GAME3_Board::is_lose(Player<char>* player) { return false; }
bool GAME3_Board::is_draw(Player<char>* player) { return n_moves == 25; }
bool GAME3_Board::game_is_over(Player<char>* player) { return n_moves == 25; }

GAME3_UI::GAME3_UI() : UI<char>("Welcome to 5x5 Tic-Tac-Toe", 3) {}
Player<char>* GAME3_UI::create_player(string& name, char symbol, PlayerType type) { return new Player<char>(name, symbol, type); }
Move<char>* GAME3_UI::get_move(Player<char>* player) {
    int x, y;
    if (player->get_type() == PlayerType::HUMAN) {
        cout << "Enter row col: "; cin >> x >> y;
    } else { x = rand()%5; y = rand()%5; }
    return new Move<char>(x, y, player->get_symbol());
}