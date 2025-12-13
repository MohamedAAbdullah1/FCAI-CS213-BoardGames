#include <iostream>
#include <iomanip>
#include <cctype>
#include <cstdlib>
#include <limits>
#include <vector>
#include "Misere_Classes.h"

using namespace std;

bool check_win_chk(const vector<vector<char>>& board, int rows, int cols, char symbol) {
    for (int i = 0; i < rows; ++i) {
        if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) return true;
    }
    for (int i = 0; i < cols; ++i) {
        if (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol) return true;
    }
    if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) return true;
    if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol) return true;

    return false;
}

bool is_full_chk(const vector<vector<char>>& board, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (board[i][j] == '.') return false;
        }
    }
    return true;
}

int minimax(vector<vector<char>>& board, int rows, int cols, bool isMaximizing, char aiSym, char humanSym) {
    if (check_win_chk(board, rows, cols, aiSym)) {
        return -10;
    }
    if (check_win_chk(board, rows, cols, humanSym)) {
        return 10;
    }
    if (is_full_chk(board, rows, cols)) {
        return 0;
    }

    if (isMaximizing) {
        int bestScore = -1000;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (board[i][j] == '.') {
                    board[i][j] = aiSym;
                    int score = minimax(board, rows, cols, false, aiSym, humanSym);
                    board[i][j] = '.';
                    if (score > bestScore) {
                        bestScore = score;
                    }
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = 1000;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (board[i][j] == '.') {
                    board[i][j] = humanSym;
                    int score = minimax(board, rows, cols, true, aiSym, humanSym);
                    board[i][j] = '.';
                    if (score < bestScore) {
                        bestScore = score;
                    }
                }
            }
        }
        return bestScore;
    }
}

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
        int rows = boardPtr->get_rows();
        int cols = boardPtr->get_columns();

        vector<vector<char>> boardMatrix = boardPtr->get_board_matrix();

        char opponentSym = (sym == 'X') ? 'O' : 'X';

        int bestVal = -1000;
        int bestX = -1;
        int bestY = -1;

        bool moveFound = false;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (boardMatrix[i][j] == '.') {
                    boardMatrix[i][j] = sym;

                    int moveVal = minimax(boardMatrix, rows, cols, false, sym, opponentSym);

                    boardMatrix[i][j] = '.';

                    if (moveVal > bestVal) {
                        bestX = i;
                        bestY = j;
                        bestVal = moveVal;
                        moveFound = true;
                    }
                }
            }
        }

        if (moveFound) {
            x = bestX;
            y = bestY;
        } else {
             do {
                x = rand() % rows;
                y = rand() % cols;
            } while (boardMatrix[x][y] != '.');
        }

        cout << "\nComputer (" << sym << ") played at: " << x << " " << y << "\n";
    }

    return new Move<char>(x, y, sym);
}