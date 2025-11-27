#include "WORDh_Classes.h"

Word_Board::Word_Board(const string& dict_filename) : Board<char>(3, 3) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
    n_moves = 0;
    ifstream fin(dict_filename);
    if (!fin.is_open()) {
        cerr << "Warning: could not open dictionary file '" << dict_filename << "'. No words loaded.\n";
        return;
    }
    string line;
    while (getline(fin, line)) {
        string w;
        for (char ch : line) {
            if (!isspace((unsigned char)ch)) w.push_back(char(toupper((unsigned char)ch)));
        }
        if (w.size() == 3) dict.insert(w);
    }
    fin.close();
}

bool Word_Board::update_board(Move<char>* move) {
    int xt = move->get_to_x();
    int yt = move->get_to_y();
    char symbol = move->get_symbol();

    if (xt < 0 || xt >= rows || yt < 0 || yt >= columns) return false;
    if (board[xt][yt] != blank_symbol) return false;

    char up = char(toupper((unsigned char)symbol));
    if (up < 'A' || up > 'Z') return false;

    board[xt][yt] = up;
    ++n_moves;
    return true;
}

bool Word_Board::any_three_letter_word_present() const {
    // Rows
    for (int r = 0; r < 3; ++r) {
        string s;
        for (int c = 0; c < 3; ++c) s.push_back(board[r][c]);
        if (s.find('.') == string::npos) {
            if (dict.find(s) != dict.end()) return true;
        }
    }
    for (int c = 0; c < 3; ++c) {
        string s;
        for (int r = 0; r < 3; ++r) s.push_back(board[r][c]);
        if (s.find('.') == string::npos) {
            if (dict.find(s) != dict.end()) return true;
        }
    }
    {
        string s;
        s.push_back(board[0][0]);
        s.push_back(board[1][1]);
        s.push_back(board[2][2]);
        if (s.find('.') == string::npos) {
            if (dict.find(s) != dict.end()) return true;
        }
    }
    {
        string s;
        s.push_back(board[0][2]);
        s.push_back(board[1][1]);
        s.push_back(board[2][0]);
        if (s.find('.') == string::npos) {
            if (dict.find(s) != dict.end()) return true;
        }
    }
    return false;
}

bool Word_Board::is_win(Player<char>* player) {
    return any_three_letter_word_present();
}

bool Word_Board::is_draw(Player<char>* player) {
    if (n_moves < 9) return false;
    return !any_three_letter_word_present();
}

bool Word_Board::game_is_over(Player<char>* player) {
    return any_three_letter_word_present() || (n_moves >= 9);
}


WordXO_UI::WordXO_UI() : UI<char>("Welcome to Word Tic-Tac-Toe (3x3). Place letters to form a 3-letter word!", 3) {}

Player<char>* WordXO_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << "\n";
    return new Player<char>(name, static_cast<char>('?'), type);
}

Move<char>* WordXO_UI::get_move(Player<char>* player) {
    int xt = -1, yt = -1;
    int xf = -1, yf = -1;
    char letter = 'A';

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nEnter row (0-2) and column (0-2) and letter (A-Z), separated by spaces: ";
        cin >> xt >> yt >> letter;
    } else {
        Board<char>* b = player->get_board_ptr();
        bool chosen = false;
        for (int i = 0; i < b->get_rows() && !chosen; ++i) {
            for (int j = 0; j < b->get_columns() && !chosen; ++j) {
                if (b->get_cell(i,j) == '.') {
                    xt = i; yt = j;
                    chosen = true;
                }
            }
        }
        letter = char('A' + (rand() % 26));
    }
    return new Move<char>(xf, yf, xt, yt, letter);
}
