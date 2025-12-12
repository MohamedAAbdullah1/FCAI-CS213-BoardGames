#include <iostream>
#include "INFINITY_CLASSES.h"
// IMPORTANT: Do NOT include "Memory_Classes.cpp" here.

using namespace std;

int main() {
    Memory_Board* board = new Memory_Board();

    Memory_UI* ui = new Memory_UI();


    Player<char>** players = ui->setup_players();

    GameManager<char> game(board, players, ui);
    game.run();

    delete board;
    delete ui;
    delete players[0];
    delete players[1];
    delete[] players;

    return 0;
}