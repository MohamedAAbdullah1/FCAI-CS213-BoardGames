#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "BoardGame_Classes.h"
#include "Numerical_Classes.h"
using namespace std;

int main() {

    srand(static_cast<unsigned int>(time(0)));

    UI<int>* game_ui = new Numerical_UI();

    Board<int>* numerical_board = new Numerical_Board();

    Player<int>** players = game_ui->setup_players();

    GameManager<int> numerical_game(numerical_board, players, game_ui);

    numerical_game.run();

    delete game_ui;

    delete numerical_board;

    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    delete[] players;

    return 0;
}