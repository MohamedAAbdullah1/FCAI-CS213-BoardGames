#ifndef NUMERICAL_UI_H
#define NUMERICAL_UI_H

#include "BoardGame_Classes.h"
#include "Numerical_TicTacToe.h"
#include <vector>
#include <cstdlib>

using namespace std;

class Numerical_UI : public UI<int> {
public:
    Numerical_UI() : UI<int>("Welcome to Numerical Tic-Tac-Toe!", 4) {}

    // *** FIX 1: Add setup_players() override to allow user to choose PlayerType ***
    Player<int>** setup_players() override {
        Player<int>** players = new Player<int>*[2];
        vector<string> type_options = { "Human", "Computer" };

        string name1 = get_player_name("Player 1 (Odd)");
        PlayerType type1 = get_player_type_choice("Player 1", type_options);
        players[0] = create_player(name1, 1, type1); // 1 for Odd

        string name2 = get_player_name("Player 2 (Even)");
        PlayerType type2 = get_player_type_choice("Player 2", type_options);
        players[1] = create_player(name2, 2, type2); // 2 for Even

        return players;
    }


    Move<int>* get_move(Player<int>* player) override {
        int x, y, number;

        Numerical_Player* num_player = static_cast<Numerical_Player*>(player);

        if (player->get_type() == PlayerType::HUMAN) {
            num_player->display_available_numbers();

            bool valid_input = false;
            while (!valid_input) {
                cout << player->get_name() << "'s turn.\n";
                if (num_player->is_odd()) cout << "Choose an ODD number (1,3,5,7,9).\n";
                else cout << "Choose an EVEN number (2,4,6,8).\n";

                cout << "Enter Row (0-2), Column (0-2), and Number: ";

                if (!(cin >> x >> y >> number)) {
                    cout << "Invalid input format! Please enter three numbers.\n";
                    cin.clear();
                    cin.ignore(10000, '\n');
                    continue;
                }

                if (num_player->is_odd() && number % 2 == 0) {
                    cout << "Error: Player 1 must choose ODD numbers!\n";
                    continue;
                }
                if (!num_player->is_odd() && number % 2 != 0) {
                    cout << "Error: Player 2 must choose EVEN numbers!\n";
                    continue;
                }

                if (number < 1 || number > 9) {
                    cout << "Error: Number must be between 1 and 9.\n";
                    continue;
                }

                if (!num_player->is_number_available(number)) {
                    cout << "Error: This number has already been used or is invalid for you!\n";
                    continue;
                }

                if (!num_player->consume_number(number)) {
                     continue;
                }

                valid_input = true;
            }
        } else if (player->get_type() == PlayerType::COMPUTER) {
            Board<int>* boardPtr = player->get_board_ptr();
            const set<int>& available_nums = num_player->get_available_numbers();

            if (available_nums.empty()) {
                cout << "Computer has no numbers left! Error.\n";
                return new Move<int>(-1, -1, 0);
            }

            vector<int> num_vector(available_nums.begin(), available_nums.end());
            int random_index = rand() % num_vector.size();
            number = num_vector[random_index];

            do {
                x = rand() % boardPtr->get_rows();
                y = rand() % boardPtr->get_columns();
            } while (boardPtr->get_board_matrix()[x][y] != 0);

            num_player->consume_number(number);

            cout << "\nComputer (" << player->get_name() << ") played " << number << " at: " << x << " " << y << "\n";
        }

        return new Move<int>(x, y, number);
    }

    Player<int>* create_player(string& name, int symbol, PlayerType type) override {
        return new Numerical_Player(name, symbol, type);
    }
};

#endif