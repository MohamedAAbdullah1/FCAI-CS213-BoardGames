#ifndef SUS_CLASSES_H
#define SUS_CLASSES_H

#include"BoardGame_Classes.h"

class SUS_Board:public Board<char>
{
 char black_sympol = '.';
 
 public:
 SUS_Board();

 bool update_board(Move<char>*move);

 bool is_win(Player<char>* player);

 bool is_lose(Player<char>*) { return false; }

 bool is_draw();

 bool game_is_over();
};

class SUS_UI:public UI<char>
{
 public:
 SUS_UI();

 ~SUS_UI(){}

 Player<char>* create_player(string& name, char symbol, PlayerType type);

 virtual Move<char>* get_move(Player<char>* player);
};
#endif