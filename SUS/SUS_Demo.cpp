#include"SUS_Classes.h"


int main()
{
 UI<char>*Game_ui=new SUS_UI();
 Board<char>*Game_Board= new SUS_Board();
 Player<char>**players = Game_ui->setup_players();
 GameManager<char>SUS(Game_Board,players,Game_ui);
 SUS.run();
}