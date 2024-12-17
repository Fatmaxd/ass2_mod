#ifndef MISERE_TIC_TAC_TOE_H
#define MISERE_TIC_TAC_TOE_H

#include "BoardGames_Classes.h"
#include <vector>
#include <iostream>

enum Difficulty { EASY, NORMAL, HARD };

class MisereTicTacToe : public Board<char> {
private:
    char currentPlayer;
    Difficulty difficulty;

public:
    MisereTicTacToe(int rows, int columns, Difficulty difficulty);

    bool update_board(int x, int y, char symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;

    void switchPlayer();
    std::pair<int, int> getRandomMove();
    std::pair<int, int> getAIMove();
    char getCell(int x, int y) const;
    Difficulty getDifficulty() const;
};

void runMisereTicTacToe();

#endif // MISERE_TIC_TAC_TOE_H
