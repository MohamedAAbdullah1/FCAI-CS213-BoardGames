#ifndef XO_CLASSES_H
#define XO_CLASSES_H

#include"BoardGame_Classes.h"

class X_O_Board:public Board<char>
{
    char blank_symbol = '.';

public:
    X_O_Board();

    bool update_board(Move<char>* move) override;

    bool is_win(Player<char>* player) override;

    bool is_lose(Player<char>*) override { return false; }

    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
};

class XO_UI:public UI<char>
{
public:
    XO_UI();

    ~XO_UI(){}

    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    virtual Move<char>* get_move(Player<char>* player) override;
};
#endif