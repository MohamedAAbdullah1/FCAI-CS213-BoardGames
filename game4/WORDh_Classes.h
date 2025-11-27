#ifndef WORDh_CLASSES_H
#define WORDh_CLASSES_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <algorithm>

using namespace std;

/**
 * Word_Board
 * - 3x3 board
 * - players place single letters (A-Z)
 * - after each placement, check all 3-letter lines (3 rows, 3 cols, 2 diags)
 *   if any line spells a word present in dic.txt -> the player who placed the letter wins.
 */
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

#endif // WORD_XO_CLASSES_H
