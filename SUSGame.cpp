#include "SUSGame.h"

// Constructor
SUSGame::SUSGame(Difficulty diff) {
    rows = 3;
    columns = 3;
    board = new char* [rows];
    for (int i = 0; i < rows; i++) {
        board[i] = new char[columns];
        for (int j = 0; j < columns; j++) {
            board[i][j] = '.';
        }
    }
    player1Symbol = 'S';
    player2Symbol = 'U';
    player1Score = 0;
    player2Score = 0;
    currentPlayerSymbol = player1Symbol;
    difficulty = diff;
    n_moves = 0;
}

// Destructor
SUSGame::~SUSGame() {
    for (int i = 0; i < rows; i++) {
        delete[] board[i];
    }
    delete[] board;
}

char SUSGame::getBoardValue(int row, int col) const {
    if (row < 0 || row >= rows || col < 0 || col >= columns) {
        return '.';  // Return empty cell for out-of-bounds
    }
    return board[row][col];
}

// Update board
bool SUSGame::update_board(int row, int col, char symbol) {
    if (row < 0 || row >= rows || col < 0 || col >= columns || board[row][col] != '.') {
        return false;
    }
    board[row][col] = symbol;
    n_moves++;
    int beforeMove = (symbol == player1Symbol) ? player1Score : player2Score;
    int afterMove = countSUSSequences();
    int newSequences = afterMove - (player1Score + player2Score);
    if (symbol == player1Symbol) {
        player1Score += newSequences;
    }
    else {
        player2Score += newSequences;
    }
    return true;
}

// Display board
void SUSGame::display_board() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cout << setw(2) << board[i][j];
        }
        cout << endl;
    }
    cout << "Player 1 (S): " << player1Score << " | Player 2 (U): " << player2Score << endl;
    cout << endl;
}

// Check win
bool SUSGame::is_win() {
    return n_moves == rows * columns;
}

// Check draw
bool SUSGame::is_draw() {
    return (n_moves == rows * columns) && (player1Score == player2Score);
}

// Game is over
bool SUSGame::game_is_over() {
    return n_moves == rows * columns;
}

// Count SUS sequences
int SUSGame::countSUSSequences() {
    int count = 0;
    for (int i = 0; i < rows; i++) {
        if (board[i][0] == 'S' && board[i][1] == 'U' && board[i][2] == 'S') count++;
    }
    for (int j = 0; j < columns; j++) {
        if (board[0][j] == 'S' && board[1][j] == 'U' && board[2][j] == 'S') count++;
    }
    if (board[0][0] == 'S' && board[1][1] == 'U' && board[2][2] == 'S') count++;
    if (board[0][2] == 'S' && board[1][1] == 'U' && board[2][0] == 'S') count++;
    return count;
}

// Switch player
void SUSGame::switchPlayer() {
    currentPlayerSymbol = (currentPlayerSymbol == player1Symbol) ? player2Symbol : player1Symbol;
}

// Get random move
pair<int, int> SUSGame::getRandomMove() {
    vector<pair<int, int>> availableMoves;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (board[i][j] == '.') availableMoves.push_back({ i, j });
        }
    }
    return availableMoves[rand() % availableMoves.size()];
}

// Get AI move
pair<int, int> SUSGame::getAIMove() {
    pair<int, int> bestMove = { -1, -1 };
    int maxSequences = -1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (board[i][j] == '.') {
                board[i][j] = currentPlayerSymbol;
                int sequencesGained = countSUSSequences();
                board[i][j] = '.';
                if (sequencesGained > maxSequences) {
                    maxSequences = sequencesGained;
                    bestMove = { i, j };
                }
            }
        }
    }
    return bestMove.first == -1 ? getRandomMove() : bestMove;
}

// Play game
void SUSGame::playGame(bool againstAI, bool againstRandom) {
    while (!game_is_over()) {
        display_board();
        int row, col;
        if (againstAI && currentPlayerSymbol == player2Symbol) {
            pair<int, int> move = getAIMove();
            row = move.first;
            col = move.second;
            cout << "AI chooses: " << row << ", " << col << endl;
        }
        else if (againstRandom && currentPlayerSymbol == player2Symbol) {
            pair<int, int> move = getRandomMove();
            row = move.first;
            col = move.second;
            cout << "Random player chooses: " << row << ", " << col << endl;
        }
        else {
            cout << "Player " << (currentPlayerSymbol == player1Symbol ? "1" : "2")
                << "'s turn (" << currentPlayerSymbol << "). Enter row and column (0-2): ";
            cin >> row >> col;
        }
        if (!update_board(row, col, currentPlayerSymbol)) {
            cout << "Invalid move. Try again.\n";
            continue;
        }
        switchPlayer();
    }
    display_board();
    cout << "Game over!\n";
    if (player1Score > player2Score) {
        cout << "Player 1 wins with " << player1Score << " sequences!\n";
    }
    else if (player2Score > player1Score) {
        cout << "Player 2 wins with " << player2Score << " sequences!\n";
    }
    else {
        cout << "It's a draw with both players scoring " << player1Score << " sequences!\n";
    }
}

// Added GUI support methods
char SUSGame::getCurrentPlayerSymbol() const {
    return currentPlayerSymbol;
}

int SUSGame::getPlayer1Score() const {
    return player1Score;
}

int SUSGame::getPlayer2Score() const {
    return player2Score;
}