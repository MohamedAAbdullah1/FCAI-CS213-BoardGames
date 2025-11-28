#ifndef FOURINR_CLASSES_H
#define FOURINR_CLASSES_H

#include"BoardGame_Classes.h"

class Four_in_Board:public Board<char>
{
 char main_sym='.';

 public:
 Four_in_Board();

 bool update_board(Move<char>* move);

 bool is_win(Player<char>*);

 bool is_lose(Player<char>*){return false;}

 bool is_draw(Player<char>*);

 bool game_is_over(Player<char>*);
};

class Four_in_UI:public UI<char>
{

 public:
 Four_in_UI();

 Move<char>* get_move(Player<char>*);

 Player<char>* create_player(string& name, char symbol, PlayerType type);

};

#endif