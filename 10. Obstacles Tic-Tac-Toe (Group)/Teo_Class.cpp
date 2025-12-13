#include "Teo_Class.h"

Toe_Board::Toe_Board():Board(6,6)
{
 for(auto& row:board) 
 {
  for(auto& cell:row)
  {
    cell=board_sym;
  }
 }
}

bool Toe_Board::update_board(Move<char> *move)
{
 int x=move->get_x(),y=move->get_y();
 char sym=move->get_symbol();
  if (!(x < 0 || x >= rows || y < 0 || y >= columns) )
  if(get_cell(x,y)=='.')
  {
  board[x][y]=sym;
   while(board[x][y]!=board_sym)
   {
   x = rand() % rows;
   y = rand() % columns;
   }
   board[x][y]='#';
   n_moves+=2;
   return true;
  }
 return false;
}

bool Toe_Board::is_win(Player<char> *player)
{
 int x,y;
 char mark=player->get_symbol();
 for(int a=0;a<rows;a++)
 {
  for(int b=0;b<columns;b++)
  {
   x=a,y=b; 
   if(board[x][y]==mark)
   {
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

   }
  }
 }
 return false;
}

bool Toe_Board::is_lose(Player<char> *player)
{
 return false;
}

bool Toe_Board::is_draw(Player<char> *player)
{
if(n_moves==36&&!is_win(player))
 return true;

 return false;

}

bool Toe_Board::game_is_over(Player<char> *player)
{
  if(is_draw(player)||is_win(player))
 return true;

 return false;

}

//--------------Teo_UI--------------

Toe_UI::Toe_UI():UI("Weclome to FCAI Four-in-a-row Game by 20240455", 3)
{
}

Move<char> *Toe_UI::get_move(Player<char> *player)
{
 int x, y;
    
    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease enter your move x and y (0 to 5): ";
        cin >> x >> y;
        
    } 
    else if (player->get_type() == PlayerType::COMPUTER) {
        x = rand() % player->get_board_ptr()->get_rows();
        y = rand() % player->get_board_ptr()->get_columns();
        
    }
    return new Move<char>(x, y, player->get_symbol());

}

Player<char> *Toe_UI::create_player(string &name, char symbol, PlayerType type)
{
 cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";
 return new Player<char>(name,symbol,type);

}
