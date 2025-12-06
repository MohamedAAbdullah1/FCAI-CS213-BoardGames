#ifndef MISERE_CLASSES_H
#define MISERE_CLASSES_H

#include "../BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

class Misere_Board : public Board<char> {
private:
    char blank_symbol = '.';

    bool check_three_in_a_row(char a, char b, char c);

public:
    Misere_Board();

    bool update_board(Move<char>* move) override;

    bool is_win(Player<char>* player) override;

    bool is_lose(Player<char>* player) override;

    bool is_draw(Player<char>* player) override;

    bool game_is_over(Player<char>* player) override;
};

class Misere_UI : public UI<char> {
public:
    Misere_UI();

    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    Move<char>* get_move(Player<char>* player) override;
};

#endif
