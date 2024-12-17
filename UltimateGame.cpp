#include "UltimateGame.h"
#include <iostream>
#include <string>

SmallBoard::SmallBoard() : grid(SMALL_BOARD_SIZE, std::vector<char>(SMALL_BOARD_SIZE, '.')), winner('.') {}

bool SmallBoard::isFull() {
    for (const auto& row : grid)
        for (char cell : row)
            if (cell == '.')
                return false;
    return true;
}

bool SmallBoard::checkWin(char player) {
    for (int i = 0; i < SMALL_BOARD_SIZE; ++i) {
        if ((grid[i][0] == player && grid[i][1] == player && grid[i][2] == player) ||
            (grid[0][i] == player && grid[1][i] == player && grid[2][i] == player))
            return true;
    }

    if ((grid[0][0] == player && grid[1][1] == player && grid[2][2] == player) ||
        (grid[0][2] == player && grid[1][1] == player && grid[2][0] == player))
        return true;

    return false;
}

void SmallBoard::markAll(char player) {
    for (auto& row : grid)
        for (auto& cell : row)
            cell = player;
    winner = player;
}

BigBoard::BigBoard() : grid(BIG_BOARD_SIZE, std::vector<SmallBoard>(BIG_BOARD_SIZE)), currentPlayer('X') {
    rows = BIG_BOARD_SIZE;
    columns = BIG_BOARD_SIZE;
    board = nullptr;  // Not used directly since we have SmallBoards
}

bool BigBoard::update_board(int x, int y, char symbol) {
    int bigRow = x / SMALL_BOARD_SIZE;
    int bigCol = y / SMALL_BOARD_SIZE;
    int smallRow = x % SMALL_BOARD_SIZE;
    int smallCol = y % SMALL_BOARD_SIZE;

    // Use the getter method to access the SmallBoard
    if (bigRow < 0 || bigRow >= BIG_BOARD_SIZE || bigCol < 0 || bigCol >= BIG_BOARD_SIZE ||
        smallRow < 0 || smallRow >= SMALL_BOARD_SIZE || smallCol < 0 || smallCol >= SMALL_BOARD_SIZE ||
        getSmallBoard(bigRow, bigCol).grid[smallRow][smallCol] != '.') {
        return false;
    }

    // Make the move
    getSmallBoard(bigRow, bigCol).grid[smallRow][smallCol] = symbol;

    // Check if the small board has a winner
    if (getSmallBoard(bigRow, bigCol).checkWin(symbol)) {
        getSmallBoard(bigRow, bigCol).markAll(symbol);
    }

    ++n_moves;
    return true;
}

void BigBoard::display_board() {
    for (int bigRow = 0; bigRow < BIG_BOARD_SIZE; ++bigRow) {
        for (int smallRow = 0; smallRow < SMALL_BOARD_SIZE; ++smallRow) {
            for (int bigCol = 0; bigCol < BIG_BOARD_SIZE; ++bigCol) {
                for (int smallCol = 0; smallCol < SMALL_BOARD_SIZE; ++smallCol) {
                    std::cout << grid[bigRow][bigCol].grid[smallRow][smallCol] << " ";
                }
                if (bigCol < BIG_BOARD_SIZE - 1) std::cout << "| ";
            }
            std::cout << std::endl;
        }
        if (bigRow < BIG_BOARD_SIZE - 1) {
            std::cout << std::string(11, '-') << "+" << std::string(11, '-') << "+" << std::string(11, '-') << std::endl;
        }
    }
}

bool BigBoard::is_win() {
    for (int i = 0; i < BIG_BOARD_SIZE; ++i) {
        // Check rows and columns for 'X' and 'O'
        if ((grid[i][0].winner == 'X' && grid[i][1].winner == 'X' && grid[i][2].winner == 'X') ||
            (grid[0][i].winner == 'X' && grid[1][i].winner == 'X' && grid[2][i].winner == 'X'))
            return true;
        if ((grid[i][0].winner == 'O' && grid[i][1].winner == 'O' && grid[i][2].winner == 'O') ||
            (grid[0][i].winner == 'O' && grid[1][i].winner == 'O' && grid[2][i].winner == 'O'))
            return true;
    }

    // Check diagonals for 'X' and 'O'
    if ((grid[0][0].winner == 'X' && grid[1][1].winner == 'X' && grid[2][2].winner == 'X') ||
        (grid[0][2].winner == 'X' && grid[1][1].winner == 'X' && grid[2][0].winner == 'X'))
        return true;

    if ((grid[0][0].winner == 'O' && grid[1][1].winner == 'O' && grid[2][2].winner == 'O') ||
        (grid[0][2].winner == 'O' && grid[1][1].winner == 'O' && grid[2][0].winner == 'O'))
        return true;

    return false;
}

bool BigBoard::is_draw() {
    // Check if all small boards are filled
    for (int i = 0; i < BIG_BOARD_SIZE; i++) {
        for (int j = 0; j < BIG_BOARD_SIZE; j++) {
            // Check if any cell in the small board is empty
            for (int smallRow = 0; smallRow < SMALL_BOARD_SIZE; ++smallRow) {
                for (int smallCol = 0; smallCol < SMALL_BOARD_SIZE; ++smallCol) {
                    if (getSmallBoard(i, j).grid[smallRow][smallCol] == '.') {
                        return false;  // Found an empty cell, not a draw yet
                    }
                }
            }
        }
    }
    // All small boards are filled, now check for a winner
    return !is_win();  // If there's no winner, then it's a draw
}


bool BigBoard::game_is_over() {
    return is_win() || is_draw();
}

void BigBoard::switchPlayer() {
    // Switch the current player between 'X' and 'O'
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

char BigBoard::getCurrentPlayer() const {
    return currentPlayer;
}
