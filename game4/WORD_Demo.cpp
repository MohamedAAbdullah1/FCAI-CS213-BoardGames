#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <ctime>

#include "BoardGame_Classes.h"
#include "WORDh_Classes.h"

using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(0)));

    UI<char>* game_ui = new WordXO_UI();
    Board<char>* word_board = new Word_Board("dic.txt");
    Player<char>** players = game_ui->setup_players();
    GameManager<char> word_game(word_board, players, game_ui);
    word_game.run();

    delete word_board;
    for (int i = 0; i < 2; ++i) delete players[i];
    delete[] players;
    delete game_ui;

    return 0;
}
