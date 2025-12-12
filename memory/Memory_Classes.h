#ifndef MEMORY_CLASSES_H
#define MEMORY_CLASSES_H

#include <vector>
#include <string>
#include "BoardGame_Classes.h"

class Memory_Board : public Board<char> {
private:
    char blank_symbol = '.';
    std::vector<std::vector<char>> real_board;

public:
    Memory_Board();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    // Implementation of is_lose inside header is fine (implicitly inline)
    bool is_lose(Player<char>* player) override { return false; }
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

    std::pair<int,int> compute_best_move(char cpuMark);
};

class Memory_UI : public UI<char> {
public:
    Memory_UI();
    ~Memory_UI() override {}

    Player<char>* create_player(std::string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
};

#endif // MEMORY_CLASSES_H