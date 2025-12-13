#include "Diamond_Classes.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>

using namespace std;
bool is_valid_cell_static(int r, int c) {
    return (r + c >= 2 && r + c <= 6 && abs(r - c) <= 2);
}


bool check_win_static(const vector<vector<char>>& board, char symbol) {
    // Check all cells
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (board[i][j] != symbol) continue;
            int dr[] = {0, 1, 1, 1};
            int dc[] = {1, 0, 1, -1};
            for (int d = 0; d < 4; d++) {
                int r = i, c = j;
                int count = 1;
                for (int k = 1; k < 3; k++) {
                    r += dr[d];
                    c += dc[d];
                    if (r < 0 || r >= 5 || c < 0 || c >= 5 || board[r][c] != symbol) break;
                    count++;
                }
                if (count == 3) return true;
            }
        }
    }
    return false;
}

bool is_full_static(const vector<vector<char>>& board) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (is_valid_cell_static(i, j) && board[i][j] == '.') return false;
        }
    }
    return true;
}


int minimax_diamond(vector<vector<char>>& board, int depth, bool isMaximizing, char aiSym, char humSym, int alpha, int beta) {
    if (check_win_static(board, aiSym)) return 100 - depth; // AI Wins (Prefer faster wins)
    if (check_win_static(board, humSym)) return depth - 100; // Human Wins (Prefer slower losses)
    if (is_full_static(board)) return 0; // Draw

    if (isMaximizing) {
        int maxEval = -10000;
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                if (is_valid_cell_static(i, j) && board[i][j] == '.') {
                    board[i][j] = aiSym;
                    int eval = minimax_diamond(board, depth + 1, false, aiSym, humSym, alpha, beta);
                    board[i][j] = '.'; // Backtrack
                    maxEval = max(maxEval, eval);
                    alpha = max(alpha, eval);
                    if (beta <= alpha) break; // Prune
                }
            }
        }
        return maxEval;
    } else {
        int minEval = 10000;
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                if (is_valid_cell_static(i, j) && board[i][j] == '.') {
                    board[i][j] = humSym;
                    int eval = minimax_diamond(board, depth + 1, true, aiSym, humSym, alpha, beta);
                    board[i][j] = '.'; // Backtrack
                    minEval = min(minEval, eval);
                    beta = min(beta, eval);
                    if (beta <= alpha) break; // Prune
                }
            }
        }
        return minEval;
    }
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
    return (r + c >= 2 && r + c <= 6 && abs(r - c) <= 2);
}

// Implemented actual win checking logic
bool Diamond_Board::is_win(Player<char>* player) {
    if (!player) return false; // Safety check
    return check_win_static(this->board, player->get_symbol());
}

bool Diamond_Board::is_draw(Player<char>* player) {
    return (n_moves == 13 && !is_win(player)); // 13 valid cells in Diamond
}

bool Diamond_Board::game_is_over(Player<char>* player) {
    // Need to check if anyone has won, not just the current player
    // Since is_win checks for a specific player, we should ideally check generic win state
    // But usually BoardGame logic calls is_win(current_player) after their move.
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
        vector<vector<char>> boardMatrix = boardPtr->get_board_matrix();
        char opponentSym = (sym == 'X') ? 'O' : 'X';

        int bestVal = -10000;
        int bestX = -1, bestY = -1;

        // Find best move
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                if (is_valid_cell_static(i, j) && boardMatrix[i][j] == '.') {
                    boardMatrix[i][j] = sym;
                    int moveVal = minimax_diamond(boardMatrix, 0, false, sym, opponentSym, -10000, 10000);
                    boardMatrix[i][j] = '.';

                    if (moveVal > bestVal) {
                        bestX = i;
                        bestY = j;
                        bestVal = moveVal;
                    }
                }
            }
        }

        if (bestX != -1) {
            x = bestX;
            y = bestY;
        } else {
             do {
                x = rand() % 5; y = rand() % 5;
            } while (!is_valid_cell_static(x,y) || boardMatrix[x][y] != '.');
        }
        cout << "Computer chose: " << x << " " << y << "\n";
    }
    return new Move<char>(x, y, sym);
}