#ifndef GAME3_CLASSES_H
#define GAME3_CLASSES_H

#include "../BoardGame_Classes.h"

class GAME3_Board : public Board<char> {
    int x_wins = 0;
    int o_wins = 0;
public:
    GAME3_Board();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
    void count_score();
};

class GAME3_UI : public UI<char> {
public:
    GAME3_UI();
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
};

#endif
