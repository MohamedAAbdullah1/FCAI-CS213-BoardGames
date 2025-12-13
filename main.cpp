#include <iostream>
#include <string>
#include <limits>
#include "BoardGame_Classes.h"
#include "Game_Runners.h"

using namespace std;

void display_menu() {
    cout << "\n============================================\n";
    cout << "           FCAI Board Games Menu            \n";
    cout << "============================================\n";
    cout << "Choose a game to play (1-10):\n";
    cout << "1. X-O\n";
    cout << "2. SUS\n";
    cout << "3. Four-in-a-row\n";
    cout << "4. 5x5 Tic-Tac-Toe\n";
    cout << "5. Word Tic-Tac-Toe\n";
    cout << "6. Misere Tic-Tac-Toe\n";
    cout << "7. Diamond Tic-Tac-Toe\n";
    cout << "8. 4x4 Tic-Tac-Toe\n";
    cout << "9. Pyramid Tic-Tac-Toe\n";
    cout << "10. Numerical Tic-Tac-Toe\n";
    cout << "11. Obstacles Tic-Tac-Toe\n";
    cout << "12. Infinity Tic-Tac-Toe\n";
    cout << "13. Ultimate Tic-Tac-Toe\n";
    cout << "14. Memory Tic-Tac-Toe\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    int choice;

    srand(static_cast<unsigned int>(time(0)));

    do {
        display_menu();
        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1: run_1_xo(); break;
            case 2: run_2_sus(); break;
            case 3: run_3_four_in_a_row(); break;
            case 4: run_4_5x5_tictactoe(); break;
            case 5: run_5_word_tic_tac_toe(); break;
            case 6: run_6_misere_tic_tac_toe(); break;
            case 7: run_7_diamond_tic_tac_toe(); break;
            case 8: run_8_4x4_tic_tac_toe(); break;
            case 9: run_9_pyramid_tic_tac_toe(); break;
            case 10: run_10_numerical_tic_tac_toe(); break;
            case 11: run_11_obstacles_tic_tac_toe(); break;
            case 12: run_12_infinity_Tic_tac_toe(); break;
            case 13: run_13_Ultimate_tic_tac_toe(); break;
            case 14: run_14_memory_tic_tac_toe(); break;
            case 0: cout << "Exiting program. Goodbye!\n"; break;
            default: cout << "Invalid choice. Please enter a number between 0 and 10.\n"; break;
        }
    } while (choice != 0);

    return 0;
}