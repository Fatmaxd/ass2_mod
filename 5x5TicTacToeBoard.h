#ifndef FIVE_BY_FIVE_TICTACTOE_BOARD_H
#define FIVE_BY_FIVE_TICTACTOE_BOARD_H

#include "BoardGames_Classes.h"
#include <string>

class FiveByFiveTicTacToeBoard : public Board<char> {
private:
    std::vector<std::vector<char>> boardData;
    int playerXScore, playerOScore;
    char currentPlayer;
    bool gameOver;
    int totalMoves;
    std::string gameMode; // "Human", "AI", or "SmartAI"

public:
    FiveByFiveTicTacToeBoard();
    bool update_board(int x, int y, char symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
    bool makeMove(int x, int y);
    char getCell(int x, int y) const;
    char getCurrentPlayer() const;
    int getPlayerXScore() const;
    int getPlayerOScore() const;
    void setGameMode(const std::string& mode);
    void aiMove(); // Simple AI move
    void smartAiMove(); // Smart AI move
    int countThreeInARow(char symbol);
};

void run5x5TicTacToe();

#endif // FIVE_BY_FIVE_TICTACTOE_BOARD_H
