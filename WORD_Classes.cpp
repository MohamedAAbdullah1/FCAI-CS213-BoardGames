#include "WORDh_Classes.h"

Word_Board::Word_Board(const string& dict_filename) : Board<char>(3, 3) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
    n_moves = 0;
    ifstream fin(dict_filename);
    if (!fin.is_open()) {
        dict.insert("CAT"); dict.insert("DOG"); dict.insert("BAT");
        dict.insert("ANT"); dict.insert("ZOO"); dict.insert("WIN");
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
    WordMove* wMove = dynamic_cast<WordMove*>(move);
    if (!wMove) return false;

    int xt = wMove->get_to_x();
    int yt = wMove->get_to_y();
    char symbol = wMove->get_symbol();

    if (xt < 0 || xt >= rows || yt < 0 || yt >= columns) return false;
    if (board[xt][yt] != blank_symbol) return false;

    char up = char(toupper((unsigned char)symbol));
    if (up < 'A' || up > 'Z') return false;

    board[xt][yt] = up;
    ++n_moves;
    return true;
}

bool Word_Board::any_three_letter_word_present() const {
    auto check = [&](string s) {
        return (s.find('.') == string::npos && dict.count(s));
    };
    // Rows
    for (int r = 0; r < 3; ++r) {
        string s = ""; s += board[r][0]; s += board[r][1]; s += board[r][2];
        if (check(s)) return true;
    }
    // Cols
    for (int c = 0; c < 3; ++c) {
        string s = ""; s += board[0][c]; s += board[1][c]; s += board[2][c];
        if (check(s)) return true;
    }
    // Diagonals
    string d1 = ""; d1 += board[0][0]; d1 += board[1][1]; d1 += board[2][2];
    if (check(d1)) return true;

    string d2 = ""; d2 += board[0][2]; d2 += board[1][1]; d2 += board[2][0];
    if (check(d2)) return true;

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
    return new Player<char>(name, static_cast<char>('?'), type);
}

Move<char>* WordXO_UI::get_move(Player<char>* player) {
    int xt = -1, yt = -1;
    char letter = 'A';

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nEnter row (0-2) and column (0-2) and letter (A-Z): ";
        cin >> xt >> yt >> letter;
    } else {
        Board<char>* b = player->get_board_ptr();
        vector<pair<int,int>> empty;
        for(int i=0; i<3; ++i)
            for(int j=0; j<3; ++j)
                if(b->get_cell(i,j) == '.') empty.push_back({i,j});

        if(!empty.empty()) {
            int idx = rand() % empty.size();
            xt = empty[idx].first;
            yt = empty[idx].second;
            letter = char('A' + (rand() % 26));
            cout << "Computer played " << letter << " at " << xt << " " << yt << endl;
        }
    }
    return new WordMove(-1, -1, xt, yt, letter);
}