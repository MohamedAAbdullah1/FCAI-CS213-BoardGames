#ifndef NUMERICAL_CLASSES_H
#define NUMERICAL_CLASSES_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cstdlib>

using namespace std;

class Numerical_Player : public Player<int> {
private:
    set<int> available_numbers;

public:
    Numerical_Player(string n, int symbol_code, PlayerType t);

    bool is_odd() const;

    bool is_number_available(int num) const;

    bool consume_number(int num);

    void display_available_numbers() const;

    const set<int>& get_available_numbers() const;
};

class Numerical_Board : public Board<int> {
public:
    Numerical_Board();

    bool update_board(Move<int>* move) override;

    bool is_win(Player<int>* player) override;

    bool is_lose(Player<int>* player) override { return false; }

    bool is_draw(Player<int>* player) override;

    bool game_is_over(Player<int>* player) override;
};


class Numerical_UI : public UI<int> {
public:
    Numerical_UI();

    Player<int>** setup_players() override;

    Move<int>* get_move(Player<int>* player) override;

    Player<int>* create_player(string& name, int symbol, PlayerType type) override;
};

#endif