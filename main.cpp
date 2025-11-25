#include <iostream>
#include <ctime>
#include "BoardGame_Classes.h"
#include "Numerical_TicTacToe.h"
#include "Numerical_UI.h"
#include "Misere_Classes.h"

using namespace std;

void run_misere_tictactoe() {
    Board<char>* board = new Misere_Board();
    UI<char>* ui = new Misere_UI();

    Player<char>** players = ui->setup_players();

    GameManager<char> gameManager(board, players, ui);

    gameManager.run();

    delete board;
    delete ui;
    delete players[0];
    delete players[1];
    delete[] players;
}

void run_numerical_tictactoe() {
    Board<int>* board = new Numerical_Board();
    UI<int>* ui = new Numerical_UI();

    Player<int>** players = ui->setup_players();

    GameManager<int> gameManager(board, players, ui);

    gameManager.run();

    delete board;
    delete ui;
    delete players[0];
    delete players[1];
    delete[] players;
}


int main() {
    srand(static_cast<unsigned int>(time(0)));

    int choice;
    cout << "Welcome to FCAI Board Game System\n";
    cout << "1. Numerical Tic-Tac-Toe (Group Game)\n";
    cout << "2. Misère Tic Tac Toe (Individual Game)\n";
    cout << "3. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
        {
            run_numerical_tictactoe();
            break;
        }
        case 2:
        {
            run_misere_tictactoe();
            break;
        }
        case 3:
            cout << "Goodbye!\n";
            break;
        default:
            cout << "Invalid choice.\n";
    }
    return 0;
}