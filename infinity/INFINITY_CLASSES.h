#ifndef INFINITY_CLASSES_H
    #define INFINITY_CLASSES_H

#include <vector>
#include <string>
#include <deque>
#include <tuple>
#include "BoardGame_Classes.h"


class Memory_Board : public Board<char> {
private:
    char blank_symbol = '.';
    std::vector<std::vector<char>> real_board;

    std::deque<std::tuple<int,int,char>> moves_queue;

    int removals_done = 0;
    void sync_board_matrix();

public:
    Memory_Board();

    bool update_board(Move<char>* move) ;

    bool is_win(Player<char>* player);
    bool is_lose(Player<char>* player)  { return false; }
    bool is_draw(Player<char>* player) ;
    bool game_is_over(Player<char>* player) ;

    std::pair<int,int> compute_best_move(char cpuMark);


    void process_pending_removals();
};

class Memory_UI : public UI<char> {
public:
    Memory_UI();
    ~Memory_UI() override {}

    Player<char>* create_player(std::string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
};

#endif