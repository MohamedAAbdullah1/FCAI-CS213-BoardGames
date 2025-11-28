#ifndef PYRAMID_CLASSES_H
#define PYRAMID_CLASSES_H

#include "BoardGame_Classes.h"

#include <vector>
#include <array>
#include <algorithm>
#include <utility>

using namespace std;

class Pyramid_Board : public Board<char> {
private:
    char blank_symbol = '.';
    vector<pair<int,int>> valid_cells;

public:
    Pyramid_Board();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>*) override { return false; }
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
};

class Pyramid_UI : public UI<char> {
public:
    Pyramid_UI();
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
    void display_board_matrix(const vector<vector<char>>& matrix) const override;
};

#endif