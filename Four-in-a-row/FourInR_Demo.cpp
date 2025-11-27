
#include "FourInR_Classes.h"

int main()
{
  srand(static_cast<unsigned int>(time(0)));

  UI<char>* game_ui = new Four_in_UI();

  Board<char>* game_board = new Four_in_Board();

  Player<char>** Players= game_ui->setup_players();

  GameManager<char>Four_in_row(game_board,Players,game_ui);

  Four_in_row.run();
}