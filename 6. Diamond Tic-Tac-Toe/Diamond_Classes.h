#ifndef DIAMOND_CLASSES_H
#define DIAMOND_CLASSES_H

#include "../BoardGame_Classes.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

class Diamond_Board : public Board<char> {
private:
    char blank_symbol = '.';

    bool check_line(int start_r, int start_c, int dr, int dc, int length, char symbol) const;

    bool is_valid_diamond_cell(int r, int c) const;

public:
    Diamond_Board();

    bool update_board(Move<char>* move) override;

    bool is_win(Player<char>* player) override;

    bool is_lose(Player<char>* player) override { return false; }

    bool is_draw(Player<char>* player) override;

    bool game_is_over(Player<char>* player) override;

    void display_board_matrix() const;
};

class Diamond_UI : public UI<char> {
public:
    Diamond_UI();

    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    Move<char>* get_move(Player<char>* player) override;
};

#endif