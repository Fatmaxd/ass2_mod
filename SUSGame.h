#ifndef SUS_GAME_H
#define SUS_GAME_H

#include "BoardGames_Classes.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

class SUSGame : public Board<char> {
public:
    enum Difficulty { EASY, NORMAL, HARD };

    char player1Symbol, player2Symbol;
    int player1Score, player2Score;
    char currentPlayerSymbol;
    Difficulty difficulty;

public:
    // Constructor
    SUSGame(Difficulty diff = EASY);

    // Destructor
    ~SUSGame();

    // Overridden methods from Board class
    bool update_board(int row, int col, char symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;

    // Original methods
    int countSUSSequences();
    void switchPlayer();
    pair<int, int> getRandomMove();
    pair<int, int> getAIMove();
    void playGame(bool againstAI, bool againstRandom);

    // GUI support methods
    char getCurrentPlayerSymbol() const;
    int getPlayer1Score() const;
    int getPlayer2Score() const;

    // New method to access board value
    char getBoardValue(int row, int col) const;
};
void runSUSGameGUI();  // Added GUI run function

#endif // SUS_GAME_H