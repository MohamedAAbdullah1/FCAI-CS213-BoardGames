#include <iostream>
#include <iomanip>
#include <cctype>
#include <cstdlib>
#include "Misere_Classes.h"

using namespace std;

bool Misere_Board::check_three_in_a_row(char a, char b, char c) {
    return a == b && b == c && a != blank_symbol;
}

Misere_Board::Misere_Board() : Board<char>(3, 3) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

bool Misere_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    if (!(x < 0 || x >= rows || y < 0 || y >= columns) &&
        (board[x][y] == blank_symbol)) {

        n_moves++;
        board[x][y] = toupper(mark);
        return true;
    }
    return false;
}

bool Misere_Board::is_win(Player<char>* player) {
    return false;
}

bool Misere_Board::is_lose(Player<char>* player) {
    const char sym = player->get_symbol();

    for (int i = 0; i < rows; ++i) {
        if ( (check_three_in_a_row(board[i][0], board[i][1], board[i][2]) && board[i][0] == sym) ||
             (check_three_in_a_row(board[0][i], board[1][i], board[2][i]) && board[0][i] == sym) )
            return true;
    }

    if ( (check_three_in_a_row(board[0][0], board[1][1], board[2][2]) && board[1][1] == sym) ||
         (check_three_in_a_row(board[0][2], board[1][1], board[2][0]) && board[1][1] == sym) )
        return true;

    return false;
}

bool Misere_Board::is_draw(Player<char>* player) {
    return (n_moves == 9 && !is_lose(player));
}

bool Misere_Board::game_is_over(Player<char>* player) {
    return is_lose(player) || is_draw(player);
}

Misere_UI::Misere_UI() : UI<char>("Misere Tic-Tac-Toe: The objective is to force the opponent to win", 3) {}

Player<char>* Misere_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Move<char>* Misere_UI::get_move(Player<char>* player) {
    int x, y;
    char sym = player->get_symbol();

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\n" << player->get_name() << " (" << sym << ") - Enter row and column (0-2) for your move: ";
        cin >> x >> y;
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        Board<char>* boardPtr = player->get_board_ptr();

        do {
            x = rand() % boardPtr->get_rows();
            y = rand() % boardPtr->get_columns();
        } while (boardPtr->get_board_matrix()[x][y] != '.');

        cout << "\nComputer (" << sym << ") played at: " << x << " " << y << "\n";
    }

    return new Move<char>(x, y, sym);
}