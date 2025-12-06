#include "SUS_Classes.h"
#include <iostream>
#include <iomanip>
#include <cctype>
#include <cstdlib>

using namespace std;


SUS_Board::SUS_Board():Board(3,3)
{
 for(auto &row:board)
 for(auto &colum:row)
 colum=black_sympol;
}

bool SUS_Board::update_board(Move<char>*move)
{
int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    if (!(x < 0 || x >= rows || y < 0 || y >= columns) && (board[x][y] == black_sympol || mark == 0)) {

        if (mark == 0) {
            n_moves--;
            board[x][y] = black_sympol;

        }
        else {
            n_moves++;
            board[x][y] = toupper(mark);

        }
        return true;
       }
 return false;
}

bool SUS_Board::is_win(Player<char> *player)
{
 char sym = player->get_symbol();
 pair<int,int>x_y=player->get_last_move();
 int x=x_y.first , y=x_y.second;
 auto all_SUS = [&](char a,char b,char c){ return (((a=='S') && (c=='S')) && (b=='U'));};

for (int i = 0; i < rows; ++i) {

    if (
   ( (all_SUS(board[i][0], board[i][1], board[i][2]))))
   {
        for(int j=0;j<columns;j++)
        if(x==i&&y==j)
        return true;
   }

    if( (all_SUS(board[0][i], board[1][i], board[2][i])))
   {
     for(int j=0;j<rows;j++)
     if(x==j&&y==i)
     return true;
   }
}

if (((all_SUS(board[0][0], board[1][1], board[2][2]))))
 {
        for(int i=0;i<rows;i++)
        if(x==i&&y==i)
        return true;
 }
else if((all_SUS(board[0][2], board[1][1], board[2][0])))
{
        for(int i=0,j=columns-1;i<rows&&j>=0;i++,j--)
        if(x==i&&y==j)
        return true;
}
        return false;
}

bool SUS_Board::is_draw(Player<char>* player)
{
  return (n_moves == 9 && !is_win(player));
}

bool SUS_Board::game_is_over(Player<char>* player)
{
 return  is_draw(player) || is_win(player);
}


SUS_UI::SUS_UI():UI("Weclome to FCAI SUS Game by 20240455",3){}

Player<char> *SUS_UI::create_player(string &name, char symbol, PlayerType type)
{

 cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";
 return new Player<char>(name,symbol,type);
}

Move<char> *SUS_UI::get_move(Player<char> *player)
{
 int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease enter your move x and y (0 to 2): ";
        cin >> x >> y;
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        Board<char>* boardPtr = player->get_board_ptr();
        do {
            x = rand() % boardPtr->get_rows();
            y = rand() % boardPtr->get_columns();
        } while (boardPtr->get_cell(x, y) != '.');
    }
    return new Move<char>(x, y, player->get_symbol());
}