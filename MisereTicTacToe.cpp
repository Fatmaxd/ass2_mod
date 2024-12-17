#include "MisereTicTacToe.h"
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

MisereTicTacToe::MisereTicTacToe(int rows, int columns, Difficulty difficulty) : Board() {
    this->rows = rows;
    this->columns = columns;
    this->difficulty = difficulty;
    this->n_moves = 0;

    board = new char* [rows];
    for (int i = 0; i < rows; i++) {
        board[i] = new char[columns];
        for (int j = 0; j < columns; j++) {
            board[i][j] = '.';
        }
    }

    currentPlayer = 'X';
}

bool MisereTicTacToe::update_board(int x, int y, char symbol) {
    if (x < 0 || x >= rows || y < 0 || y >= columns || board[x][y] != '.') {
        return false;
    }
    board[x][y] = symbol;
    n_moves++;
    return true;
}

void MisereTicTacToe::display_board() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cout << setw(2) << board[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

bool MisereTicTacToe::is_win() {
    for (int i = 0; i < rows; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            if (board[i][0] == 'X') {
                return true;
            }
            else if (board[i][0] == 'O') {
                return true;
            }
        }
    }

    for (int i = 0; i < columns; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            if (board[0][i] == 'X') {
                return true;
            }
            else if (board[0][i] == 'O') {
                return true;
            }
        }
    }

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == 'X') {
            return true;
        }
        else if (board[0][0] == 'O') {
            return true;
        }
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == 'X') {
            return true;
        }
        else if (board[0][2] == 'O') {
            return true;
        }
    }

    return false;
}

bool MisereTicTacToe::is_draw() {
    return n_moves == rows * columns && !is_win();
}

bool MisereTicTacToe::game_is_over() {
    return is_win() || is_draw();
}

void MisereTicTacToe::switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

std::pair<int, int> MisereTicTacToe::getRandomMove() {
    vector<pair<int, int>> availableMoves;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (board[i][j] == '.') {
                availableMoves.push_back({ i, j });
            }
        }
    }
    return availableMoves[rand() % availableMoves.size()];
}

std::pair<int, int> MisereTicTacToe::getAIMove() {
    return getRandomMove();
}

char MisereTicTacToe::getCell(int x, int y) const {
    if (x < 0 || x >= rows || y < 0 || y >= columns) {
        throw out_of_range("Invalid cell coordinates");
    }
    return board[x][y];
}

Difficulty MisereTicTacToe::getDifficulty() const {
    return difficulty;
}
