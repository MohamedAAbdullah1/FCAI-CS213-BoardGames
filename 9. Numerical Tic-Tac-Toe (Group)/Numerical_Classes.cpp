#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <set>
#include <cstdlib>
#include <limits>
#include "Numerical_Classes.h"

using namespace std;


Numerical_Player::Numerical_Player(string n, int symbol_code, PlayerType t)
    : Player<int>(n, symbol_code, t) {
    if (symbol_code == 1) {
        available_numbers = {1, 3, 5, 7, 9};
    } else {
        available_numbers = {2, 4, 6, 8};
    }
}

bool Numerical_Player::is_odd() const {
    return this->symbol == 1;
}

bool Numerical_Player::is_number_available(int num) const {
    return available_numbers.count(num);
}

bool Numerical_Player::consume_number(int num) {
    if (available_numbers.count(num)) {
        available_numbers.erase(num);
        return true;
    }
    return false;
}

void Numerical_Player::display_available_numbers() const {
    cout << this->name << " (Available numbers: ";
    for (int num : available_numbers) {
        cout << num << " ";
    }
    cout << ")\n";
}

const set<int>& Numerical_Player::get_available_numbers() const {
    return available_numbers;
}


Numerical_Board::Numerical_Board() : Board<int>(3, 3) {
    this->board = vector<vector<int>>(3, vector<int>(3, 0));
    this->n_moves = 0;
}

bool Numerical_Board::update_board(Move<int>* move) {
    int x = move->get_x();
    int y = move->get_y();
    int number = move->get_symbol();

    if (x < 0 || x >= rows || y < 0 || y >= columns) {
        return false;
    }
    if (this->board[x][y] != 0) {
        return false;
    }

    this->board[x][y] = number;
    this->n_moves++;
    return true;
}

bool Numerical_Board::is_win(Player<int>* player) {

    for (int i = 0; i < 3; i++) {
        if (this->board[i][0] != 0 && this->board[i][1] != 0 && this->board[i][2] != 0) {
            if ((this->board[i][0] + this->board[i][1] + this->board[i][2]) == 15) return true;
        }
        if (this->board[0][i] != 0 && this->board[1][i] != 0 && this->board[2][i] != 0) {
            if ((this->board[0][i] + this->board[1][i] + this->board[2][i]) == 15) return true;
        }
    }

    if (this->board[0][0] != 0 && this->board[1][1] != 0 && this->board[2][2] != 0) {
        if ((this->board[0][0] + this->board[1][1] + this->board[2][2]) == 15) return true;
    }
    if (this->board[0][2] != 0 && this->board[1][1] != 0 && this->board[2][0] != 0) {
        if ((this->board[0][2] + this->board[1][1] + this->board[2][0]) == 15) return true;
    }
    return false;
}

bool Numerical_Board::is_draw(Player<int>* player) {
    return (this->n_moves == 9 && !is_win(player));
}

bool Numerical_Board::game_is_over(Player<int>* player) {
    return is_win(player) || is_draw(player);
}


Numerical_UI::Numerical_UI() : UI<int>("Welcome to Numerical Tic-Tac-Toe! (Win with a sum of 15)", 4) {}

Player<int>** Numerical_UI::setup_players() {
    Player<int>** players = new Player<int>*[2];
    vector<string> type_options = { "Human", "Computer" };

    string name1 = get_player_name("Player 1 (Odd: 1,3,5,7,9)");
    PlayerType type1 = get_player_type_choice("Player 1", type_options);
    players[0] = create_player(name1, 1, type1);

    string name2 = get_player_name("Player 2 (Even: 2,4,6,8)");
    PlayerType type2 = get_player_type_choice("Player 2", type_options);
    players[1] = create_player(name2, 2, type2);

    return players;
}

Move<int>* Numerical_UI::get_move(Player<int>* player) {
    int x = -1, y = -1, number = 0;

    Numerical_Player* num_player = static_cast<Numerical_Player*>(player);

    if (player->get_type() == PlayerType::HUMAN) {
        bool valid_input = false;
        while (!valid_input) {
            num_player->display_available_numbers();
            cout << player->get_name() << "'s turn.\n";
            if (num_player->is_odd()) cout << "Player 1 (Odd) - Choose Row, Column, and Number: ";
            else cout << "Player 2 (Even) - Choose Row, Column, and Number: ";

            if (!(cin >> x >> y >> number)) {
                cout << "Invalid input format! Please enter three numbers.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            if (x < 0 || x > 2 || y < 0 || y > 2) {
                cout << "Error: Row and Column must be between 0 and 2.\n";
                continue;
            }

            if (num_player->is_odd() && number % 2 == 0) {
                cout << "Error: Player 1 must choose ODD numbers only!\n";
                continue;
            }
            if (!num_player->is_odd() && number % 2 != 0) {
                cout << "Error: Player 2 must choose EVEN numbers only!\n";
                continue;
            }

            if (number < 1 || number > 9) {
                cout << "Error: Number must be between 1 and 9.\n";
                continue;
            }

            if (!num_player->is_number_available(number)) {
                cout << "Error: This number has already been used by you or is invalid for you!\n";
                continue;
            }

            valid_input = true;
        }


        if (valid_input) {
             num_player->consume_number(number);

        } else {
             return new Move<int>(-1, -1, 0);
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

        vector<pair<int, int>> empty_cells;
        for(int i = 0; i < boardPtr->get_rows(); ++i) {
             for(int j = 0; j < boardPtr->get_columns(); ++j) {
                 if(boardPtr->get_cell(i, j) == 0) {
                     empty_cells.push_back({i, j});
                 }
             }
        }

        if (!empty_cells.empty()) {
             int rand_idx = rand() % empty_cells.size();
             x = empty_cells[rand_idx].first;
             y = empty_cells[rand_idx].second;
        } else {
             cout << "Computer found no available cells.\n";
             return new Move<int>(-1, -1, 0);
        }


        num_player->consume_number(number);

        cout << "\nComputer (" << player->get_name() << ") played " << number << " at: " << x << " " << y << "\n";
    }

    return new Move<int>(x, y, number);
}

Player<int>* Numerical_UI::create_player(string& name, int symbol, PlayerType type) {
    // symbol هنا هو 1 (Odd) أو 2 (Even)
    return new Numerical_Player(name, symbol, type);
}