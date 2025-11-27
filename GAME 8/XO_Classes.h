#ifndef XO_CLASSES_H
#define XO_CLASSES_H

#include "BoardGame_Classes.h"
#include <vector>
#include <array>
#include <algorithm>

using namespace std;

class X_O_Board : public Board<char> {
private:
    char blank_symbol = '.';
    vector<pair<int,int>> valid_cells;
    vector<array<int,3>> winning_triples;

public:
    X_O_Board();

    bool update_board(Move<char>* move) ;
    bool is_win(Player<char>* player) ;
    bool is_lose(Player<char>*)  { return false; }
    bool is_draw(Player<char>* player) ;
    bool game_is_over(Player<char>* player) ;

    static bool input1to9_to_coord(int input, int &outx, int &outy);
};

class XO_UI : public UI<char> {
public:
    XO_UI();
    Player<char>* create_player(string& name, char symbol, PlayerType type) ;
    Move<char>* get_move(Player<char>* player) ;
    void display_board_matrix(const vector<vector<char>>& matrix) const ;
};

#endif // XO_CLASSES_H
