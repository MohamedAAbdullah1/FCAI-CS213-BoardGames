#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "BoardGame_Classes.h"
#include "Diamond_Classes.h"
using namespace std;

int main() {

    srand(static_cast<unsigned int>(time(0)));

    UI<char>* game_ui = new Diamond_UI();

    Board<char>* diamond_board = new Diamond_Board();

    Player<char>** players = game_ui->setup_players();

    GameManager<char> diamond_game(diamond_board, players, game_ui);

    diamond_game.run();

    delete game_ui;

    delete diamond_board;

    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    delete[] players;

    return 0;
}