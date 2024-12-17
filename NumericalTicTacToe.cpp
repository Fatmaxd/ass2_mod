#include "NumericalTicTacToe.h"
#include <iostream>

using namespace std;

NumericalTicTacToe::NumericalTicTacToe() {
    board = vector<vector<int>>(3, vector<int>(3, 0)); // Initialize the board with 0 (empty)
}

void NumericalTicTacToe::display_board() {
    cout << "\nBoard:\n  1 2 3\n"; // Column headers
    for (int r = 0; r < 3; ++r) {
        cout << r + 1 << " "; // Row headers
        for (int c = 0; c < 3; ++c) {
            if (board[r][c] == 0)
                cout << ". "; // Empty cells
            else
                cout << board[r][c] << " "; // Filled cells
        }
        cout << "\n";
    }
    for (int c = 0; c < 3; ++c) {
        cout << c << " ";
    }
    cout << "\n";
}

bool NumericalTicTacToe::is_valid_move(int num, int row, int col, int player) {
    row--; col--; // Convert to 0-based indexing (from 1-based input)

    // Check if the position is within bounds (1 to 3) and if the cell is empty
    if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != 0)
        return false;

    // Check if the number is valid for the current player
    if (player == 1 && available_odd.count(num)) return true;
    if (player == 2 && available_even.count(num)) return true;

    return false;
}

bool NumericalTicTacToe::check_winner() {
    // Check rows, columns, and diagonals for a sum of 15
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] + board[i][1] + board[i][2] == 15) return true; // Rows
        if (board[0][i] + board[1][i] + board[2][i] == 15) return true; // Columns
    }
    if (board[0][0] + board[1][1] + board[2][2] == 15) return true; // Main diagonal
    if (board[0][2] + board[1][1] + board[2][0] == 15) return true; // Anti-diagonal

    return false;
}

bool NumericalTicTacToe::is_draw() {
    // Check if all cells are filled
    for (int r = 0; r < 3; ++r)
        for (int c = 0; c < 3; ++c)
            if (board[r][c] == 0)
                return false;
    return true;
}

void NumericalTicTacToe::play() {
    int player = 1; // Player 1 starts

    while (true) {
        display_board();
        cout << "Player " << player << "'s turn.\n";
        cout << "Available numbers: ";
        if (player == 1) {
            for (int num : available_odd) cout << num << " ";
        }
        else {
            for (int num : available_even) cout << num << " ";
        }
        cout << "\n";

        int num, row, col;
        cout << "Enter row, column, and value (separated by spaces): ";
        cin >> row >> col >> num;

        // Validate the move
        if (!is_valid_move(num, row, col, player)) {
            cout << "Invalid move. Try again.\n";
            continue;
        }

        // Place the number on the board
        row--; col--; // Adjust to 0-based indexing
        board[row][col] = num;

        // Remove the number from the available set
        if (player == 1)
            available_odd.erase(num);
        else
            available_even.erase(num);

        // Confirm the move
        cout << "Player " << player << " placed " << num << " at position (" << row + 1 << ", " << col + 1 << ").\n";

        // Check for a winner
        if (check_winner()) {
            display_board();
            cout << "Player " << player << " wins!\n";
            break;
        }

        // Check for a draw
        if (is_draw()) {
            display_board();
            cout << "It's a draw!\n";
            break;
        }

        // Switch player
        player = (player == 1) ? 2 : 1;
    }
}
