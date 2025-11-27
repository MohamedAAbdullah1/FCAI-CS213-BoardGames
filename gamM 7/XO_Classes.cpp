//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
#include "XO_Classes.h"

#include <ranges>

using namespace std;

//--------------------------------------- X_O_Board Implementation

X_O_Board :: X_O_Board() : Board(4, 4) {
    // Initialize all cells with blank_symbol
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
    board[0][0] = 'O' ;
    board[0][2] = 'O' ;
    board[0][3] = 'X' ;
    board[0][1] = 'X' ;
    board[3][0] = 'X' ;
    board[3][3] = 'O' ;
    board[3][1] = 'O' ;
    board[3][2] = 'X' ;
}
bool X_O_Board::update_board(Move<char>* move) {
    int x1 = move->get_from_x();
    int y1 = move->get_from_y();
    int x2 = move->get_to_x();
    int y2 = move->get_to_y();
    char symbol = move->get_symbol();

    if (x1 < 0 || x1 >= rows || y1 < 0 || y1 >= columns) return false;
    if (x2 < 0 || x2 >= rows || y2 < 0 || y2 >= columns) return false;

    if (board[x1][y1] != symbol) return false;

    if (board[x2][y2] != blank_symbol) return false;

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    if (!((dx == 1 && dy == 0) || (dx == 0 && dy == 1))) return false;

    board[x1][y1] = blank_symbol;
    board[x2][y2] = symbol;

    return true;
}

bool X_O_Board::is_win(Player<char>* player) {
    const char sym = player->get_symbol();

    auto all_equal = [&](char a, char b, char c) {
        return a == b && b == c && a != blank_symbol;
        };

    // Check rows and columns
    for (int i = 0; i < rows; ++i) {
        if ((all_equal(board[i][0], board[i][1], board[i][2]) && board[i][0] == sym) ||
            (all_equal(board[0][i], board[1][i], board[2][i]) && board[0][i] == sym) ||
            (all_equal(board[i][1], board[i][2], board[i][3]) && board[i][1] == sym) ||
            (all_equal(board[1][i], board[2][i], board[3][i]) && board[1][i] == sym) )
            return true;
    }
    // Check diagonals
    for (int  i = 0 ; i<= 3 ; i++) {
        for (int j =0 ; j <4 ; j++) {
            if (i+2 < 4 && j+2 < 4) {
                if (all_equal(board [i][j] ,board[i+1] [j+1] ,board [i+2][j+2] ) && board [i][j] == sym )
                    return true;
            }
            if (i+2 <4 && j-2 >-1 ) {
                if (all_equal (board [i][j] ,board[i+1] [j-1] ,board [i+2][j-2]) && board [i][j] == sym )
                    return true;
            }
        }
    }
    return false;
}

bool X_O_Board::is_draw(Player<char>* player) {
    return (n_moves == 16 && !is_win(player));
}

bool X_O_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

//--------------------------------------- XO_UI Implementation

XO_UI::XO_UI() : UI<char>("Weclome to FCAI X-O Game by Dr El-Ramly", 4) {}

Player<char>* XO_UI::create_player(string& name, char symbol, PlayerType type) {
    // Create player based on type
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* XO_UI::get_move(Player<char>* player) {
    int xf, yf ,xt ,yt;
    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease enter your move x_From and y_From and x_To and y_TO  (0 to 3): ";
        cin >> xf >> yf >> xt >> yt ;
    }
    else if (player->get_type() == PlayerType::COMPUTER){
        for (int i =0  ;i<=3 ; i++) {
            for (int j=0 ; j< 4 ; j++) {
                if (player->get_board_ptr()->get_cell(i, j) == player->get_symbol()) {
                    if (i+1 < 4 && player->get_board_ptr()->get_cell(i+1, j) == '.' ) {
                        xf = i  ;
                        yf = j  ;
                        xt =i+1;
                        yt = j;
                    }
                    else if (i-1 >= 0 && player->get_board_ptr()->get_cell(i-1, j) == '.' ) {
                        xf = i  ;
                        yf = j  ;
                        xt = i-1;
                        yt = j;
                    }
                    else if (j+1< 4 && player->get_board_ptr()->get_cell(i, j+1) == '.') {
                        xf = i  ;
                        yf = j  ;
                        xt = i;
                        yt = j+1;
                    }
                    else if (j-1>=0  && player->get_board_ptr()->get_cell(i, j-1) == '.') {
                        xf = i  ;
                        yf = j  ;
                        xt = i;
                        yt = j-1;
                    }
                }
            }
        }
    }
    return new Move<char>(xf, yf,xt ,yt , player->get_symbol());
}
