#ifndef NUMERICAL_TICTACTOE_H
#define NUMERICAL_TICTACTOE_H

#include <vector>
#include <set>

class NumericalTicTacToe {
private:
    std::vector<std::vector<int>> board; // 3x3 grid for the game
    std::set<int> available_odd{ 1, 3, 5, 7, 9 }; // Available numbers for Player 1 (odd)
    std::set<int> available_even{ 2, 4, 6, 8 };   // Available numbers for Player 2 (even)

    void display_board();
    bool is_valid_move(int num, int row, int col, int player);
    bool check_winner();
    bool is_draw();

public:
    NumericalTicTacToe(); // Constructor
    void play(); // Function to run the game
};

#endif // NUMERICAL_TICTACTOE_H
