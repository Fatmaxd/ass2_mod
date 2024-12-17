#include "FourInARowBoard.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

FourInARowBoard::FourInARowBoard(int rows, int columns) : defaultRows(rows), defaultColumns(columns) {
    this->rows = rows;
    this->columns = columns;
    board = new char* [rows];
    for (int i = 0; i < rows; ++i) {
        board[i] = new char[columns];
        fill(board[i], board[i] + columns, '.');
    }
}

FourInARowBoard::~FourInARowBoard() {
    for (int i = 0; i < rows; ++i) {
        delete[] board[i];
    }
    delete[] board;
}

bool FourInARowBoard::update_board(int col, int, char symbol) {
    if (col < 0 || col >= defaultColumns || board[0][col] != '.') return false;

    for (int r = rows - 1; r >= 0; --r) {
        if (board[r][col] == '.') {
            board[r][col] = symbol;
            ++n_moves;
            return true;
        }
    }
    return false;
}

void FourInARowBoard::display_board() {
    cout << "\nBoard:\n";
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < defaultColumns; ++c) {
            cout << board[r][c] << " ";
        }
        cout << "\n";
    }
    for (int c = 0; c < defaultColumns; ++c) {
        cout << c << " ";
    }
    cout << "\n";
}

bool FourInARowBoard::is_win() {
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < defaultColumns; ++c) {
            char mark = board[r][c];
            if (mark == '.') continue;

            if (check_direction(r, c, 1, 0, mark) || // Horizontal
                check_direction(r, c, 0, 1, mark) || // Vertical
                check_direction(r, c, 1, 1, mark) || // Diagonal 
                check_direction(r, c, 1, -1, mark))  // Diagonal /
            {
                return true;
            }
        }
    }
    return false;
}

bool FourInARowBoard::is_draw() {
    return n_moves == rows * defaultColumns;
}

bool FourInARowBoard::game_is_over() {
    return is_win() || is_draw();
}

bool FourInARowBoard::check_direction(int r, int c, int dr, int dc, char mark) {
    int count = 0;
    for (int i = 0; i < 4; ++i) {
        int nr = r + i * dr;
        int nc = c + i * dc;
        if (nr >= 0 && nr < rows && nc >= 0 && nc < defaultColumns && board[nr][nc] == mark) {
            ++count;
        }
        else {
            break;
        }
    }
    return count == 4;
}

HumanPlayer::HumanPlayer(string n, char symbol) : Player<char>(n, symbol) {}

void HumanPlayer::getmove(int& col, int&) {
    cout << getname() << " (" << getsymbol() << "), enter column (0-" << 6 << "): ";
    cin >> col;
}

AIPlayer::AIPlayer(char symbol) : RandomPlayer<char>(symbol) {}

void AIPlayer::getmove(int& col, int&) {
    // Pick a random valid column
    col = rand() % 7;  // Random column selection
    cout << "AI Player chose column: " << col << endl;  // Debug output
}

// This function encapsulates the entire game logic
void runFourInARowGame() {
    srand(time(0));

    FourInARowBoard board;
    char choice;
    cout << "Do you want to play against AI? (y/n): ";
    cin >> choice;

    Player<char>* player1 = new HumanPlayer("Player 1", 'X');
    Player<char>* player2 = (choice == 'y' || choice == 'Y') ?
        (Player<char>*)new AIPlayer('O') :
        (Player<char>*)new HumanPlayer("Player 2", 'O');

    player1->setBoard(&board);
    player2->setBoard(&board);
    Player<char>* players[] = { player1, player2 };

    GameManager<char> gameManager(&board, players);
    gameManager.run();

    delete player1;
    delete player2;
}
