#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "BoardGame_Classes.h"
#include "Misere_Classes.h"
using namespace std;

int main() {

    srand(static_cast<unsigned int>(time(0)));

    UI<char>* game_ui = new Misere_UI();

    Board<char>* misere_board = new Misere_Board();

    Player<char>** players = game_ui->setup_players();

    GameManager<char> misere_game(misere_board, players, game_ui);

    misere_game.run();

    delete game_ui;

    delete misere_board;

    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    delete[] players;

    return 0;
}