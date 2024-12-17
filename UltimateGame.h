#ifndef ULTIMATE_TICTACTOE_H
#define ULTIMATE_TICTACTOE_H

#include "BoardGames_Classes.h"
#include <vector>

const int BIG_BOARD_SIZE = 3;
const int SMALL_BOARD_SIZE = 3;

class SmallBoard {
public:
    std::vector<std::vector<char>> grid;
    char winner;

    SmallBoard();
    bool isFull();
    bool checkWin(char player);
    void markAll(char player);
};

class BigBoard : public Board<char> {
private:
    std::vector<std::vector<SmallBoard>> grid;
    char currentPlayer;

public:
    BigBoard();
    bool update_board(int x, int y, char symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
    void switchPlayer();
    char getCurrentPlayer() const;

    // Getter for grid
    SmallBoard& getSmallBoard(int bigRow, int bigCol) {
        return grid[bigRow][bigCol];
    }

    const SmallBoard& getSmallBoard(int bigRow, int bigCol) const {
        return grid[bigRow][bigCol];
    }
};

void runUltimateTicTacToe();

#endif // ULTIMATE_TICTACTOE_H
