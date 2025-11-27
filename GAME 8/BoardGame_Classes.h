#ifndef BOARDGAME_CLASSES_H
#define BOARDGAME_CLASSES_H

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

/////////////////////////////////////////////////////////////
// Forward declarations
/////////////////////////////////////////////////////////////
template <typename T> class Player;
template <typename T> class Move;

/////////////////////////////////////////////////////////////
// PlayerType enum
/////////////////////////////////////////////////////////////
enum class PlayerType {
    HUMAN,
    COMPUTER,
    AI,
    RANDOM
};

/////////////////////////////////////////////////////////////
// Board<T> template (base)
/////////////////////////////////////////////////////////////
template <typename T>
class Board {
protected:
    int rows;
    int columns;
    vector<vector<T>> board;
    int n_moves = 0;

public:
    Board(int rows_, int columns_)
        : rows(rows_), columns(columns_), board(rows_, vector<T>(columns_)) {}

    virtual ~Board() {}

    // Return cell value
    T get_cell(int x, int y) const {
        return board[x][y];
    }

    // Virtual game-specific operations
    virtual bool update_board(Move<T>* move) = 0;
    virtual bool is_win(Player<T>* p) = 0;
    virtual bool is_lose(Player<T>* p) = 0;
    virtual bool is_draw(Player<T>* p) = 0;
    virtual bool game_is_over(Player<T>* p) = 0;

    vector<vector<T>> get_board_matrix() const { return board; }

    int get_rows() const { return rows; }
    int get_columns() const { return columns; }

    void increment_moves() { ++n_moves; }
    int get_n_moves() const { return n_moves; }
};

/////////////////////////////////////////////////////////////
// Move<T> template
/////////////////////////////////////////////////////////////
template <typename T>
class Move {
    int x1, y1;
    T symbol;

public:
    // Using from and to coordinates for flexibility
    Move(int xf, int yf, T s)
        : x1(xf), y1(yf), symbol(s) {}

    int get_to_x() const { return x1; }
    int get_to_y() const { return y1; }
    T get_symbol() const { return symbol; }
};

/////////////////////////////////////////////////////////////
// Player<T> template
/////////////////////////////////////////////////////////////
template <typename T>
class Player {
protected:
    string name;
    PlayerType type;
    T symbol;
    Board<T>* boardPtr;

public:
    Player(string n, T s, PlayerType t)
        : name(n), type(t), symbol(s), boardPtr(nullptr) {}

    virtual ~Player() {}

    string get_name() const { return name; }
    PlayerType get_type() const { return type; }
    T get_symbol() const { return symbol; }
    Board<T>* get_board_ptr() const { return boardPtr; }
    void set_board_ptr(Board<T>* b) { boardPtr = b; }
};

/////////////////////////////////////////////////////////////
// UI<T> template (base)
/////////////////////////////////////////////////////////////
template <typename T>
class UI {
protected:
    int cell_width;

    string get_player_name(const string& player_label) {
        string name;
        cout << "Enter " << player_label << " name: ";
        getline(cin >> ws, name);
        return name;
    }

    PlayerType get_player_type_choice(const string& player_label, const vector<string>& options) {
        cout << "Choose " << player_label << " type:\n";
        for (size_t i = 0; i < options.size(); ++i)
            cout << i + 1 << ". " << options[i] << "\n";
        int choice = 1;
        cin >> choice;
        if (choice < 1) choice = 1;
        if (choice > 2) choice = 2;
        return (choice == 2) ? PlayerType::COMPUTER : PlayerType::HUMAN;
    }

public:
    UI(const string& message = "", int cell_display_width = 3)
        : cell_width(cell_display_width) {
        if (!message.empty()) cout << message << endl;
    }

    virtual ~UI() {}

    void display_message(const string& message) { cout << message << "\n"; }

    virtual Move<T>* get_move(Player<T>*) = 0;

    // default players setup - uses create_player virtual
    virtual Player<T>** setup_players() {
        Player<T>** players = new Player<T>*[2];
        vector<string> type_options = { "Human", "Computer" };

        string nameX = get_player_name("Player X");
        PlayerType typeX = get_player_type_choice("Player X", type_options);
        players[0] = create_player(nameX, static_cast<T>('X'), typeX);

        string nameO = get_player_name("Player O");
        PlayerType typeO = get_player_type_choice("Player O", type_options);
        players[1] = create_player(nameO, static_cast<T>('O'), typeO);

        return players;
    }

    virtual Player<T>* create_player(string& name, T symbol, PlayerType type) = 0;

    // Display matrix; specialized games can use their own layout (override if needed)
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
            for (int j = 0; j < cols; ++j)
                cout << setw(cell_width) << matrix[i][j] << " |";
            cout << "\n   " << string((cell_width + 2) * cols, '-') << "\n";
        }
        cout << endl;
    }
};

/////////////////////////////////////////////////////////////
// GameManager<T> template
/////////////////////////////////////////////////////////////
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
        while (true) {
            for (int i = 0; i < 2; ++i) {
                Player<T>* current = players[i];
                Move<T>* move = ui->get_move(current);

                // Keep asking until valid move applied
                while (!boardPtr->update_board(move)) {
                    ui->display_message("Invalid move. Try again.");
                    delete move;
                    move = ui->get_move(current);
                }

                ui->display_board_matrix(boardPtr->get_board_matrix());

                if (boardPtr->is_win(current)) {
                    ui->display_message(current->get_name() + " wins!");
                    return;
                }
                if (boardPtr->is_lose(current)) {
                    ui->display_message(players[1 - i]->get_name() + " wins!");

                    return;
                }
                if (boardPtr->is_draw(current)) {
                    ui->display_message("Draw!");delete move;
                    return;
                }


            }
        }
    }
};

#endif // BOARDGAME_CLASSES_H
