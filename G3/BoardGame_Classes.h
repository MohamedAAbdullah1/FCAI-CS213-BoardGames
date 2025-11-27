#ifndef _BOARDGAME_CLASSES_H
#define _BOARDGAME_CLASSES_H

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
// Class declarations
/////////////////////////////////////////////////////////////

enum class PlayerType {
    HUMAN,
    COMPUTER,
    AI,
    RANDOM
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
    char get_cell(int x, int y) const {
        return board[x][y];
    }
    virtual ~Board() {}

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

    int get_n_moves() const { return n_moves; }
};

template <typename T>
class Move {
    int x1;
    int y1;

    T symbol;
public:
    Move(int xf, int yf , T symbol) : x1(xf), y1(yf) , symbol(symbol) {}


    int get_x() const {return x1 ;}
    int get_y() const {return y1;}
    T get_symbol() const { return symbol; }
};

template <typename T>
class Player {
protected:
    string name;
    PlayerType type;
    T symbol;
    Board<T>* boardPtr;
public:
    Player(string n, T s, PlayerType t)
        : name(n), symbol(s), type(t), boardPtr(nullptr) {}

    virtual ~Player() {}

    string get_name() const { return name; }
    PlayerType get_type() const { return type; }
    T get_symbol() const { return symbol; }
    Board<T>* get_board_ptr() const { return boardPtr; }
    void set_board_ptr(Board<T>* b) { boardPtr = b; }
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
        cout << "Choose " << player_label << " type:\n";
        for (size_t i = 0; i < options.size(); ++i)
            cout << i + 1 << ". " << options[i] << "\n";
        int choice;
        cin >> choice;
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

    void display_board_matrix(const vector<vector<T>>& matrix) const {
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
        Player<T>* currentPlayer = players[0];

        while (true) {
            for (int i : {0, 1}) {
                currentPlayer = players[i];
                Move<T>* move = ui->get_move(currentPlayer);

                while (!boardPtr->update_board(move)) {
                    ui->display_message("Invalid move. Try again.");
                    delete move;
                    move = ui->get_move(currentPlayer);
                }
                delete move; // avoid leak

                ui->display_board_matrix(boardPtr->get_board_matrix());

                // If game is over (according to board rules), we decide winner by counting 3-in-a-row sequences
                if (boardPtr->game_is_over(currentPlayer)) {
                    // We rely on board implementation to provide a way to count sequences via dynamic_cast
                    // (since Board<T> is general template, we attempt cast to access count function)
                    int count0 = 0, count1 = 0;
                    // Try to dynamic_cast to a class that provides count_three_in_row (here we expect X_O_Board)
                    // We'll use RTTI only if available; otherwise fallback to 0.
                    // Because this is header-only and generic, we'll do a safe cast using pointers.
                    struct Countable {
                        virtual int count_three_in_row(char) = 0;
                        virtual ~Countable() {}
                    };
                    Countable* cptr = dynamic_cast<Countable*>(boardPtr);

                    auto matrix = boardPtr->get_board_matrix();
                    auto count_sequences = [&](char sym)->int {
                        int R = matrix.size();
                        int C = matrix[0].size();
                        int cnt = 0;
                        // horizontal
                        for (int r=0;r<R;++r){
                            for (int c=0;c+2<C;++c){
                                if (matrix[r][c]==sym && matrix[r][c+1]==sym && matrix[r][c+2]==sym) cnt++;
                            }
                        }
                        // vertical
                        for (int c=0;c<C;++c){
                            for (int r=0;r+2<R;++r){
                                if (matrix[r][c]==sym && matrix[r+1][c]==sym && matrix[r+2][c]==sym) cnt++;
                            }
                        }
                        // diag down-right
                        for (int r=0;r+2<R;++r){
                            for (int c=0;c+2<C;++c){
                                if (matrix[r][c]==sym && matrix[r+1][c+1]==sym && matrix[r+2][c+2]==sym) cnt++;
                            }
                        }
                        // diag down-left
                        for (int r=0;r+2<R;++r){
                            for (int c=2;c<C;++c){
                                if (matrix[r][c]==sym && matrix[r+1][c-1]==sym && matrix[r+2][c-2]==sym) cnt++;
                            }
                        }
                        return cnt;
                    };

                    count0 = count_sequences(players[0]->get_symbol());
                    count1 = count_sequences(players[1]->get_symbol());

                    cout << "\n=== Game Over ===\n";
                    cout << players[0]->get_name() << " (" << players[0]->get_symbol() << ") 3-in-a-row count: " << count0 << "\n";
                    cout << players[1]->get_name() << " (" << players[1]->get_symbol() << ") 3-in-a-row count: " << count1 << "\n";

                    if (count0 > count1) {
                        ui->display_message(players[0]->get_name() + " wins!");
                    } else if (count1 > count0) {
                        ui->display_message(players[1]->get_name() + " wins!");
                    } else {
                        ui->display_message("Draw!");
                    }
                    return;
                }
            }
        }
    }
};

template <typename T>
Player<T>** UI<T>::setup_players() {
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

#endif // _BOARDGAME_CLASSES_H
