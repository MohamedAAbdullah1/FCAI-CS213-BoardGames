#ifndef X4X4_CLASSES_H
#define X4X4_CLASSES_H


#include "BoardGame_Classes.h"

#include <vector>
#include <array>
#include <algorithm>
#include <cmath>

using namespace std;

class X4x4_Move : public Move<char> {
    int x_from;
    int y_from;
    int x_to;
    int y_to;

public:
    X4x4_Move(int xf, int yf, int xt, int yt, char symbol)
        : Move<char>(xt, yt, symbol), x_from(xf), y_from(yf), x_to(xt), y_to(yt) {}

    int get_from_x() const { return x_from; }
    int get_from_y() const { return y_from; }
    int get_to_x() const { return x_to; }
    int get_to_y() const { return y_to; }
};

class X4x4_Board : public Board<char> {
private:
    char blank_symbol = '.';

public:
    X4x4_Board();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>*) override { return false; };
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
};

class X4x4_UI : public UI<char> {
public:
    X4x4_UI();
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
};

#endif