#ifndef FOURINAROWBOARD_H
#define FOURINAROWBOARD_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "BoardGames_Classes.h"

class FourInARowBoard : public Board<char> {
public:
    FourInARowBoard(int rows = 6, int columns = 7);
    ~FourInARowBoard();

    bool update_board(int col, int, char symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;

private:
    int defaultRows;
    int defaultColumns;
    char** board;
    int n_moves = 0;

    bool check_direction(int r, int c, int dr, int dc, char mark);
};

class HumanPlayer : public Player<char> {
public:
    HumanPlayer(std::string n, char symbol);
    void getmove(int& col, int& row) override;
};

class AIPlayer : public RandomPlayer<char> {
public:
    AIPlayer(char symbol);
    void getmove(int& col, int& row) override;
};

void runFourInARowGame();
#endif // FOURINAROWBOARD_H
