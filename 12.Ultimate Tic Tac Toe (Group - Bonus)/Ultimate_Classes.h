#ifndef ULTIMATE_CLASSES_H
#define ULTIMATE_CLASSES_H

#include "../BoardGame_Classes.h"

class Ultimate_Board : public Board<char> {
    char big_board[3][3];
    int next_valid_sub_row;
    int next_valid_sub_col;

public:
    Ultimate_Board();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>*) override { return false; }
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

    bool is_sub_board_full(int r, int c);
    bool check_small_board_win(int sub_r, int sub_c, char symbol);
};

class Ultimate_UI : public UI<char> {
public:
    Ultimate_UI();
    ~Ultimate_UI() {}

    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    void display_board_matrix(const vector<vector<char>>& matrix) const override;
    Move<char>* get_move(Player<char>* player) override;
};

#endif