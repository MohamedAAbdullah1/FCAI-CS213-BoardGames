#ifndef NUMERICAL_TICTACTOE_H
#define NUMERICAL_TICTACTOE_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

class Numerical_Player : public Player<int> {
private:
    set<int> available_numbers;

public:
    Numerical_Player(string n, int symbol_code, PlayerType t)
        : Player<int>(n, symbol_code, t) {
        if (symbol_code == 1) {
            available_numbers = {1, 3, 5, 7, 9};
        } else {
            available_numbers = {2, 4, 6, 8};
        }
    }

    bool is_odd() const {
        return this->symbol == 1;
    }

    bool is_number_available(int num) const {
        return available_numbers.count(num);
    }

    bool consume_number(int num) {
        if (available_numbers.count(num)) {
            available_numbers.erase(num);
            return true;
        }
        return false;
    }

    void display_available_numbers() const {
        cout << this->name << " (Available: ";
        for (int num : available_numbers) {
            cout << num << " ";
        }
        cout << ")\n";
    }

    const set<int>& get_available_numbers() const {
        return available_numbers;
    }
};

class Numerical_Board : public Board<int> {
public:
    Numerical_Board() : Board<int>(3, 3) {
        this->board = vector<vector<int>>(3, vector<int>(3, 0));
        this->n_moves = 0;
    }

    bool update_board(Move<int>* move) override {
        int x = move->get_x();
        int y = move->get_y();
        int symbol = move->get_symbol();

        if (x < 0 || x >= rows || y < 0 || y >= columns) {
            return false;
        }
        if (this->board[x][y] != 0) {
            return false;
        }

        this->board[x][y] = symbol;
        this->n_moves++;
        return true;
    }

    bool is_win(Player<int>* player) override {
        for (int i = 0; i < 3; i++) {
            if (this->board[i][0] != 0 && this->board[i][1] != 0 && this->board[i][2] != 0) {
                if ((this->board[i][0] + this->board[i][1] + this->board[i][2]) == 15) return true;
            }
        }
        for (int i = 0; i < 3; i++) {
            if (this->board[0][i] != 0 && this->board[1][i] != 0 && this->board[2][i] != 0) {
                if ((this->board[0][i] + this->board[1][i] + this->board[2][i]) == 15) return true;
            }
        }
        if (this->board[0][0] != 0 && this->board[1][1] != 0 && this->board[2][2] != 0) {
            if ((this->board[0][0] + this->board[1][1] + this->board[2][2]) == 15) return true;
        }
        if (this->board[0][2] != 0 && this->board[1][1] != 0 && this->board[2][0] != 0) {
            if ((this->board[0][2] + this->board[1][1] + this->board[2][0]) == 15) return true;
        }
        return false;
    }

    bool is_lose(Player<int>* player) override {
        return false;
    }

    bool is_draw(Player<int>* player) override {
        return (this->n_moves == 9 && !is_win(player));
    }

    bool game_is_over(Player<int>* player) override {
        return is_win(player) || is_draw(player);
    }
};

#endif