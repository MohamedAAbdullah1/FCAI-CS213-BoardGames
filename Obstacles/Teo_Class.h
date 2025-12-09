#ifndef TEO_CLASS_H
#define TEO_CLASS_H

#include"BoardGame_Classes.h"
#include"bits/stdc++.h"

using  namespace  std;

class Toe_Board:public Board<char>
{
 char board_sym='.';

 public:
 Toe_Board();

  bool update_board(Move<char>* move) ;

  bool is_win(Player<char>*);

  bool is_lose(Player<char>*);

  bool is_draw(Player<char>*);

  bool game_is_over(Player<char>*);

};

class Toe_UI:public UI<char>
{
 public:
 Toe_UI();

 Move<char>* get_move(Player<char>*);

 Player<char>* create_player(string& name, char symbol, PlayerType type);

};
#endif