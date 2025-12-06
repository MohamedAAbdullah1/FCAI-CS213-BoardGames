#ifndef WORD_CLASSES_H
#define WORD_CLASSES_H

#include "../BoardGame_Classes.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <algorithm>

using namespace std;

class WordMove : public Move<char> {
    int to_x, to_y;
public:
    WordMove(int xf, int yf, int xt, int yt, char s)
        : Move<char>(xf, yf, s), to_x(xt), to_y(yt) {}

    int get_to_x() const { return to_x; }
    int get_to_y() const { return to_y; }
};

class Word_Board : public Board<char> {
private:
    char blank_symbol = '.';
    unordered_set<string> dict;
public:
    Word_Board(const string& dict_filename = "dic.txt");
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override { return false; }
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

    bool any_three_letter_word_present() const;
};

class WordXO_UI : public UI<char> {
public:
    WordXO_UI();
    ~WordXO_UI() {};
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
};

#endif
