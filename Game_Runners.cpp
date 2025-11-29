#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#include "Game_Runners.h"

#include "XO_Classes.h"
#include "SUS_Classes.h"
#include "FourInR_Classes.h"
#include "game3h_Classes.h"
#include "WORDh_Classes.h"
#include "Misere_Classes.h"
#include "Diamond_Classes.h"
#include "4x4_Classes.h"
#include "Pyramid_Classes.h"
#include "Numerical_Classes.h"

using namespace std;

void run_1_xo() {
    cout << "Starting X-O Game...\n";
    UI<char>* game_ui = new XO_UI();
    Board<char>* xo_board = new X_O_Board();
    Player<char>** players = game_ui->setup_players();
    GameManager<char> x_o_game(xo_board, players, game_ui);
    x_o_game.run();
    delete xo_board; for (int i=0; i<2; ++i) delete players[i]; delete[] players; delete game_ui;
}

void run_2_sus() {
    cout << "Starting SUS Game...\n";
    UI<char>* game_ui = new SUS_UI();
    Board<char>* sus_board = new SUS_Board();
    Player<char>** players = game_ui->setup_players();
    GameManager<char> sus_game(sus_board, players, game_ui);
    sus_game.run();
    delete sus_board; for (int i=0; i<2; ++i) delete players[i]; delete[] players; delete game_ui;
}

void run_3_four_in_a_row() {
    cout << "Starting Four-in-a-row Game...\n";
    UI<char>* game_ui = new Four_in_UI();
    Board<char>* board_ptr = new Four_in_Board();
    Player<char>** players = game_ui->setup_players();
    GameManager<char> game(board_ptr, players, game_ui);
    game.run();
    delete board_ptr; for (int i=0; i<2; ++i) delete players[i]; delete[] players; delete game_ui;
}

void run_4_5x5_tictactoe() {
    cout << "Starting 5x5 Tic-Tac-Toe Game...\n";
    UI<char>* game_ui = new GAME3_UI();
    Board<char>* board_ptr = new GAME3_Board();
    Player<char>** players = game_ui->setup_players();
    GameManager<char> game(board_ptr, players, game_ui);
    game.run();
    delete board_ptr; for (int i=0; i<2; ++i) delete players[i]; delete[] players; delete game_ui;
}

void run_5_word_tic_tac_toe() {
    cout << "Starting Word Tic-Tac-Toe Game...\n";
    UI<char>* game_ui = new WordXO_UI();
    Board<char>* board_ptr = new Word_Board("dic.txt");
    Player<char>** players = game_ui->setup_players();
    GameManager<char> game(board_ptr, players, game_ui);
    game.run();
    delete board_ptr; for (int i=0; i<2; ++i) delete players[i]; delete[] players; delete game_ui;
}

void run_6_misere_tic_tac_toe() {
    cout << "Starting Misere Tic-Tac-Toe Game...\n";
    UI<char>* game_ui = new Misere_UI();
    Board<char>* misere_board = new Misere_Board();
    Player<char>** players = game_ui->setup_players();
    GameManager<char> misere_game(misere_board, players, game_ui);
    misere_game.run();
    delete misere_board; for (int i=0; i<2; ++i) delete players[i]; delete[] players; delete game_ui;
}

void run_7_diamond_tic_tac_toe() {
    cout << "Starting Diamond Tic-Tac-Toe Game...\n";
    UI<char>* game_ui = new Diamond_UI();
    Board<char>* diamond_board = new Diamond_Board();
    Player<char>** players = game_ui->setup_players();
    GameManager<char> diamond_game(diamond_board, players, game_ui);
    diamond_game.run();
    delete diamond_board; for (int i=0; i<2; ++i) delete players[i]; delete[] players; delete game_ui;
}

void run_8_4x4_tic_tac_toe() {
    cout << "Starting 4x4 Tic-Tac-Toe Game...\n";
    UI<char>* game_ui = new X4x4_UI();
    Board<char>* board_ptr = new X4x4_Board();
    Player<char>** players = game_ui->setup_players();
    GameManager<char> game(board_ptr, players, game_ui);
    game.run();
    delete board_ptr; for (int i=0; i<2; ++i) delete players[i]; delete[] players; delete game_ui;
}

void run_9_pyramid_tic_tac_toe() {
    cout << "Starting Pyramid Tic-Tac-Toe Game...\n";
    UI<char>* game_ui = new Pyramid_UI();
    Board<char>* board_ptr = new Pyramid_Board();
    Player<char>** players = game_ui->setup_players();
    GameManager<char> game(board_ptr, players, game_ui);
    game.run();
    delete board_ptr; for (int i=0; i<2; ++i) delete players[i]; delete[] players; delete game_ui;
}

void run_10_numerical_tic_tac_toe() {
    cout << "Starting Numerical Tic-Tac-Toe Game...\n";
    UI<int>* game_ui = new Numerical_UI();
    Board<int>* numerical_board = new Numerical_Board();
    Player<int>** players = game_ui->setup_players();
    GameManager<int> numerical_game(numerical_board, players, game_ui);
    numerical_game.run();
    delete numerical_board; for (int i=0; i<2; ++i) delete players[i]; delete[] players; delete game_ui;
}