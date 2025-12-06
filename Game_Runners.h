#ifndef GAME_RUNNERS_H
#define GAME_RUNNERS_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>


#include "XO/XO_Classes.h"
#include "1. SUS/SUS_Classes.h"
#include "2. Four-in-a-row/FourInR_Classes.h"
#include "3. 5 x 5 Tic Tac Toe/game3h_Classes.h"
#include "4. Word Tic-tac-toe/WORDh_Classes.h"
#include "5. Misère Tic Tac Toe/Misere_Classes.h"
#include "6. Diamond Tic-Tac-Toe/Diamond_Classes.h"
#include "7. 4 x 4 Tic-Tac-Toe/4x4_Classes.h"
#include "8. Pyramid Tic-Tac-Toe/Pyramid_Classes.h"
#include "9. Numerical Tic-Tac-Toe (Group)/Numerical_Classes.h"

using namespace std;

void run_1_xo();
void run_2_sus();
void run_3_four_in_a_row();
void run_4_5x5_tictactoe();
void run_5_word_tic_tac_toe();
void run_6_misere_tic_tac_toe();
void run_7_diamond_tic_tac_toe();
void run_8_4x4_tic_tac_toe();
void run_9_pyramid_tic_tac_toe();
void run_10_numerical_tic_tac_toe();

#endif