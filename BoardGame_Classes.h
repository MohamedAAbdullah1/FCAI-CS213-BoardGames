#ifndef _BOARDGAME_CLASSES_H
#define _BOARDGAME_CLASSES_H

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <utility>
#include <limits>

using namespace std;

// Available Player Types
enum class PlayerType {
    HUMAN,
    COMPUTER,
    AI,
    RANDOM
};


template <typename T> class Board;


template <typename T>
class Move {
protected:
    int x;
    int y;
    T symbol;

public:
    Move() : x(-1), y(-1), symbol(T()) {}

    Move(int x, int y, T symbol) : x(x), y(y), symbol(symbol) {}

    virtual ~Move() {}

    // Getters
    int get_x() const { return x; }
    int get_y() const { return y; }
    T get_symbol() const { return symbol; }

    bool is_valid() const { return x != -1 && y != -1; }
};


template <typename T>
class Player {
protected:
    string name;
    PlayerType type;
    T symbol;
    Board<T>* boardPtr;

    pair<int, int> last_move = {-1, -1};

public:
    Player(string n, T s, PlayerType t)
        : name(n), symbol(s), type(t), boardPtr(nullptr) {}

    virtual ~Player() {}

    string get_name() const { return name; }
    PlayerType get_type() const { return type; }
    T get_symbol() const { return symbol; }
    Board<T>* get_board_ptr() const { return boardPtr; }
    void set_board_ptr(Board<T>* b) { boardPtr = b; }

    pair<int, int> get_last_move() const { return last_move; }
    void set_last_move(int x, int y) { last_move = {x, y}; }
};

template <typename T>
class Board {
protected:
    int rows;
    int columns;
    vector<vector<T>> board;
    int n_moves = 0;

public:
    Board(int rows, int columns)
        : rows(rows), columns(columns), board(rows, vector<T>(columns)) {}

    virtual ~Board() {}

    // Virtual functions to be implemented by games
    virtual bool update_board(Move<T>* move) = 0;
    virtual bool is_win(Player<T>*) = 0;
    virtual bool is_lose(Player<T>*) = 0;
    virtual bool is_draw(Player<T>*) = 0;
    virtual bool game_is_over(Player<T>*) = 0;

    vector<vector<T>> get_board_matrix() const {
        return board;
    }

    int get_rows() const { return rows; }
    int get_columns() const { return columns; }

    T get_cell(int r, int c) const {
        if (r >= 0 && r < rows && c >= 0 && c < columns) return board[r][c];
        return T();
    }
};

template <typename T>
class UI {
protected:
    int cell_width;

    string get_player_name(string player_label) {
        string name;
        cout << "Enter " << player_label << " name: ";
        getline(cin >> ws, name);
        return name;
    }

    PlayerType get_player_type_choice(string player_label, const vector<string>& options) {
        int choice;
        cout << "Choose " << player_label << " type:\n";
        for (size_t i = 0; i < options.size(); ++i)
            cout << i + 1 << ". " << options[i] << "\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
             cout << "Invalid input! Defaulting to Human.\n";
             cin.clear();
             cin.ignore(numeric_limits<streamsize>::max(), '\n');
             return PlayerType::HUMAN;
        }

        if (choice < 1 || choice > options.size()) {
             cout << "Invalid choice! Defaulting to Human.\n";
             return PlayerType::HUMAN;
        }

        return (choice == 2) ? PlayerType::COMPUTER : PlayerType::HUMAN;
    }

public:
    UI(string message, int cell_display_width)
        : cell_width(cell_display_width) {
        cout << message << endl;
    }

    virtual ~UI() {}

    void display_message(string message) { cout << message << "\n"; }

    virtual Move<T>* get_move(Player<T>*) = 0;
    virtual Player<T>** setup_players();
    virtual Player<T>* create_player(string& name, T symbol, PlayerType type) = 0;

    // [Fixed]: Added 'virtual' keyword so Pyramid_UI can override this.
    virtual void display_board_matrix(const vector<vector<T>>& matrix) const {
        if (matrix.empty() || matrix[0].empty()) return;

        int rows = matrix.size();
        int cols = matrix[0].size();

        cout << "\n    ";
        for (int j = 0; j < cols; ++j)
            cout << setw(cell_width + 1) << j;
        cout << "\n   " << string((cell_width + 2) * cols, '-') << "\n";

        for (int i = 0; i < rows; ++i) {
            cout << setw(2) << i << " |";
            for (int j = 0; j < cols; ++j) {
                if (matrix[i][j] == T() && sizeof(T) == 4) { // sizeof(int) == 4 check for Numerical
                     cout << setw(cell_width) << "." << " |";
                } else {
                     cout << setw(cell_width) << matrix[i][j] << " |";
                }
            }
            cout << "\n   " << string((cell_width + 2) * cols, '-') << "\n";
        }
        cout << endl;
    }
};


template <typename T>
class GameManager {
    Board<T>* boardPtr;
    Player<T>* players[2];
    UI<T>* ui;

public:
    GameManager(Board<T>* b, Player<T>* p[2], UI<T>* u)
        : boardPtr(b), ui(u) {
        players[0] = p[0];
        players[1] = p[1];
        players[0]->set_board_ptr(b);
        players[1]->set_board_ptr(b);
    }

    void run() {
        ui->display_board_matrix(boardPtr->get_board_matrix());
        Player<T>* currentPlayer;

        while (true) {
            for (int i : {0, 1}) {
                currentPlayer = players[i];
                Move<T>* move = nullptr;
                bool move_success = false;

                while (!move_success) {
                    if (move) delete move;

                    move = ui->get_move(currentPlayer);

                    if (!move || !move->is_valid()) {
                        if (currentPlayer->get_type() == PlayerType::HUMAN) {
                            ui->display_message("Invalid input or coordinates. Try again.");
                        }
                        else {
                            ui->display_message("Computer failed to find a move. Game ends in a draw!");
                            delete move;
                            return;
                        }
                        continue;
                    }

                    if (boardPtr->update_board(move)) {
                        move_success = true;
                    } else {
                        if (currentPlayer->get_type() == PlayerType::HUMAN) {
                            ui->display_message("Invalid move. Cell is occupied or out of bounds. Try again.");
                        }
                    }
                }

                currentPlayer->set_last_move(move->get_x(), move->get_y());
                ui->display_board_matrix(boardPtr->get_board_matrix());

                if (boardPtr->is_win(currentPlayer)) {
                    ui->display_message(currentPlayer->get_name() + " wins!");
                    delete move;
                    return;
                }
                if (boardPtr->is_lose(currentPlayer)) {
                    ui->display_message(players[1 - i]->get_name() + " wins! (" + currentPlayer->get_name() + " loses)");
                    delete move;
                    return;
                }
                if (boardPtr->is_draw(currentPlayer)) {
                    ui->display_message("Draw!");
                    delete move;
                    return;
                }
                delete move;
            }
        }
    }
};

template <typename T>
Player<T>** UI<T>::setup_players() {
    Player<T>** players = new Player<T>*[2];
    vector<string> type_options = { "Human", "Computer" };

    string name1 = get_player_name("Player 1");
    PlayerType type1 = get_player_type_choice("Player 1", type_options);
    T symbol1 = (sizeof(T) == sizeof(char)) ? static_cast<T>('X') : T(1);
    players[0] = create_player(name1, symbol1, type1);

    string name2 = get_player_name("Player 2");
    PlayerType type2 = get_player_type_choice("Player 2", type_options);
    T symbol2 = (sizeof(T) == sizeof(char)) ? static_cast<T>('O') : T(2);
    players[1] = create_player(name2, symbol2, type2);

    return players;
}

#endif