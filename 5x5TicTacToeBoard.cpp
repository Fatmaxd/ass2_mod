#include <iostream>
#include "5x5TicTacToeBoard.h"
#include <functional>


FiveByFiveTicTacToeBoard::FiveByFiveTicTacToeBoard()
    : playerXScore(0), playerOScore(0), currentPlayer('X'), gameOver(false), totalMoves(0), gameMode("Human"){
    boardData.resize(5, std::vector<char>(5, '.'));
    std::srand(std::time(nullptr)); // Seed for random number generator
}


void FiveByFiveTicTacToeBoard::setGameMode(const std::string& mode) {
    gameMode = mode;
}

void FiveByFiveTicTacToeBoard::aiMove() {
    if (gameOver || currentPlayer != 'O' || totalMoves >= 25) return; // AI acts only on its turn

    std::vector<std::pair<int, int>> availableMoves;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (boardData[i][j] == '.') {
                availableMoves.emplace_back(i, j);
            }
        }
    }

    if (!availableMoves.empty()) {
        int randomIndex = std::rand() % availableMoves.size();
        int x = availableMoves[randomIndex].first;
        int y = availableMoves[randomIndex].second;
        boardData[x][y] = currentPlayer;
        totalMoves++;
        if (is_win()) {
            gameOver = true; // Check if this move ends the game
        }
        currentPlayer = 'X'; // Switch turn to the player
    }
}


void FiveByFiveTicTacToeBoard::smartAiMove() {
    if (gameOver || currentPlayer != 'O' || totalMoves >= 25) return; // AI acts only on its turn

    int bestScore = -1000;
    int bestMoveX = -1;
    int bestMoveY = -1;

    // Evaluation heuristic
    auto evaluateBoard = [&]() -> int {
        int score = 0;
        score += countThreeInARow('O') * 10; // Favor AI's opportunities
        score -= countThreeInARow('X') * 10; // Penalize opponent's opportunities
        return score;
        };

    // Minimax with Alpha-Beta Pruning
    std::function<int(int, bool, int, int)> minimax = [&](int depth, bool isMaximizing, int alpha, int beta) {
        if (is_win()) {
            return isMaximizing ? -1000 + depth : 1000 - depth; // Winning sooner is better
        }
        if (is_draw() || depth == 4) { // Limit depth to 4 for faster decisions
            return evaluateBoard();
        }

        int bestValue = isMaximizing ? -1000 : 1000;
        char symbol = isMaximizing ? 'O' : 'X';

        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                if (boardData[i][j] == '.') {
                    boardData[i][j] = symbol; // Make the move
                    totalMoves++;

                    int moveValue = minimax(depth + 1, !isMaximizing, alpha, beta);

                    boardData[i][j] = '.'; // Undo move
                    totalMoves--;

                    if (isMaximizing) {
                        bestValue = std::max(bestValue, moveValue);
                        alpha = std::max(alpha, bestValue);
                    }
                    else {
                        bestValue = std::min(bestValue, moveValue);
                        beta = std::min(beta, bestValue);
                    }

                    if (beta <= alpha) break; // Prune branches
                }
            }
            if (beta <= alpha) break; // Prune branches
        }

        return bestValue;
        };

    // Evaluate all possible moves
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (boardData[i][j] == '.') {
                boardData[i][j] = 'O'; // AI makes a move
                totalMoves++;

                int moveScore = minimax(0, false, -1000, 1000); // Alpha-Beta Pruning

                boardData[i][j] = '.'; // Undo move
                totalMoves--;

                if (moveScore > bestScore) {
                    bestScore = moveScore;
                    bestMoveX = i;
                    bestMoveY = j;
                }
            }
        }
    }

    // Make the best move
    if (bestMoveX != -1 && bestMoveY != -1) {
        boardData[bestMoveX][bestMoveY] = 'O';
        totalMoves++;
        if (is_win()) {
            gameOver = true; // End the game if AI wins
        }
        currentPlayer = 'X'; // Switch to the player
    }
}


bool FiveByFiveTicTacToeBoard::update_board(int x, int y, char symbol) {
    if (x >= 0 && x < 5 && y >= 0 && y < 5 && boardData[x][y] == '.') {
        boardData[x][y] = symbol;
        totalMoves++;
        return true;
    }
    return false;
}

void FiveByFiveTicTacToeBoard::display_board() {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            std::cout << boardData[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int FiveByFiveTicTacToeBoard::countThreeInARow(char symbol) {
    int count = 0;

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (boardData[i][j] == symbol && boardData[i][j + 1] == symbol && boardData[i][j + 2] == symbol)
                count++;
        }
    }

    for (int j = 0; j < 5; ++j) {
        for (int i = 0; i < 3; ++i) {
            if (boardData[i][j] == symbol && boardData[i + 1][j] == symbol && boardData[i + 2][j] == symbol)
                count++;
        }
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (boardData[i][j] == symbol && boardData[i + 1][j + 1] == symbol && boardData[i + 2][j + 2] == symbol)
                count++;
        }
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 2; j < 5; ++j) {
            if (boardData[i][j] == symbol && boardData[i + 1][j - 1] == symbol && boardData[i + 2][j - 2] == symbol)
                count++;
        }
    }

    return count;
}

bool FiveByFiveTicTacToeBoard::is_win() {
    int countX = countThreeInARow('X');
    int countO = countThreeInARow('O');

    playerXScore = countX;
    playerOScore = countO;

    return false;
}

bool FiveByFiveTicTacToeBoard::is_draw() {
    return totalMoves == 24 && !is_win();
}

bool FiveByFiveTicTacToeBoard::makeMove(int x, int y) {
    if (gameOver) return false; // Don't allow moves if the game is over

    if (x >= 0 && x < 5 && y >= 0 && y < 5 && boardData[x][y] == '.') {
        boardData[x][y] = currentPlayer;
        totalMoves++;

        if (is_win()) {
            gameOver = true; // Set the game as over if there's a winner
            return true;
        }

        if (is_draw()) {
            gameOver = true; // End the game if it's a draw
            return true;
        }

        // Switch player
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        return true;
    }

    return false;
}

bool FiveByFiveTicTacToeBoard::game_is_over() {
    return totalMoves == 24;
}

char FiveByFiveTicTacToeBoard::getCell(int x, int y) const {
    if (x >= 0 && x < 5 && y >= 0 && y < 5) {
        return boardData[x][y];
    }
    return '.';
}

char FiveByFiveTicTacToeBoard::getCurrentPlayer() const {
    return currentPlayer;
}

int FiveByFiveTicTacToeBoard::getPlayerXScore() const {
    return playerXScore;
}

int FiveByFiveTicTacToeBoard::getPlayerOScore() const {
    return playerOScore;
}
