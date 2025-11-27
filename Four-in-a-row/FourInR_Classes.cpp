#include <iostream>
#include <iomanip>
#include <cctype>
#include "FourInR_Classes.h"

Four_in_Board::Four_in_Board() : Board(6, 7)
{
 for (auto &row : board)
  for (auto &cell : row)
   cell = main_sym;
}

bool Four_in_Board::update_board(Move<char> *move)
{
 int x=move->get_x();
 int y=move->get_y();
 char mark=move->get_symbol();
 
 if(x==-1||y>=columns)
 return false;
 
 n_moves++;
 board[x][y]=mark;
 
 return true;
}

bool Four_in_Board::is_win(Player<char> *player)
{
 pair<int,int>move=player->get_l_move();
 char mark=player->get_symbol();
 int x=move.first,y=move.second;
 int cnt=0;

 for(int i=x;i<rows;i++)
 {
 if(board[i][y]==mark)
 cnt++;
 else break;
 }

 if(cnt>=4)
 return true;

 cnt=0;
 int l = y,r=y;
 
 for(;r<columns;r++)
 if(board[x][r]==mark) cnt++;
 else break;

 for(int i=l-1;i>=0;i--)
 if(board[x][i]==mark)cnt++;
 else break;
 
 if(cnt>=4)
 return true;
 
 cnt=0;
 for(int i=x,j=y;i<rows&&j<columns;i++,j++)
 if(board[i][j]==mark)cnt++;
 else break;

 if(cnt>=4)
 return true;
 
 cnt=0;
 for(int i=x,j=y;i<rows&&j>=0;i++,j--)
 if(board[i][j]==mark)cnt++;
 else break;
 
 if(cnt>=4)
 return true;

 return false;
}

bool Four_in_Board::is_draw(Player<char> *player)
{
 if(n_moves==42&&!is_win(player))
 return true;

 return false;
}

bool Four_in_Board::game_is_over(Player<char> *player)
{
 if(is_draw(player)||is_win(player))
 return true;

 return false;
}

//-----------------Four_in_UI---------------
Four_in_UI::Four_in_UI() : UI("Weclome to FCAI Four-in-a-row Game by 20240455", 3){}

Move<char> *Four_in_UI::get_move(Player<char> *player)
{
 int column, row = -1;
 
 if (player->get_type() == PlayerType::HUMAN)
 {
  cout << "Please choose column from 0 to 6:", cin >> column;

  for (int i = player->get_board_ptr()->get_rows()-1; i >=0 ; i--)
  {
   if (player->get_board_ptr()->get_cell(i, column) == '.')
   {
    row = i;
    break;
   }
  }
 }

 else if (player->get_type() == PlayerType::COMPUTER)
 {
  column = rand() % player->get_board_ptr()->get_columns();
  for (int i = player->get_board_ptr()->get_rows()-1; i >=0 ; i--)
  {
   if (player->get_board_ptr()->get_cell(i, column) == '.')
    {
     row = i;
    break;
    }
  }
 }

  if(row!=-1)
    player->set_l_move(row,column);

  return new Move<char>(row, column, player->get_symbol());
}

Player<char> *Four_in_UI::create_player(string &name, char symbol, PlayerType type)
{
 cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}
