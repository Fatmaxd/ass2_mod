#ifndef _pyramic_H
#define _pyramic_H

#include "BoardGame_Classes.h"

template <typename T>
class pyramic_Board:public Board<T> {
public:
    pyramic_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class pyramic_Player : public Player<T> {
public:
    pyramic_Player (string name, T symbol);
    void getmove(int& x, int& y) ;
};

template <typename T>
class pyramic_Random_Player : public RandomPlayer<T>{
public:
    pyramic_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};

//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <limits> 
#include <cstdlib>
#include <ctime>
#include <random>
#include <vector>
#include <windows.h>
#include <algorithm>
using namespace std;

// For colors in CLI
const string BLUE = "\033[34m", CYAN = "\033[1;36m", YELLOW = "\033[1;33m", RED = "\033[1;31m", RESET = "\033[0m";

// Vector of all possibal moves 
vector<pair<int, int>> moves = {
                    {0, 0},
            {1, 0}, {1, 1}, {1, 2},
    {2, 0}, {2, 1}, {2, 2}, {2, 3}, {2, 4}
};


// Constructor for pyramic_Board
template <typename T>
pyramic_Board<T>::pyramic_Board() {
    this->rows = 3;
    this->columns = 5;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = ' ';
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool pyramic_Board<T>::update_board(int x, int y, T mark) {
    // handle range error
    if (x < 0 || x >= this->rows || y < 0 || y >= this->columns) {
        cout << RED << "Invalid move. Out of range" << RESET << endl;
        return false;
    }
    // handle used cell error
    if (this->board[x][y] != ' ') {
        cout << RED << "Invalid move. Cell already used" << RESET << endl;
        return false;
    }

    this->n_moves++;
    this->board[x][y] = toupper(mark);
    return true;
}

// Display the board
template <typename T>
void pyramic_Board<T>::display_board() {
cout << BLUE << "\n        -=-=-" << RESET;
for (int i = 0; i < this->rows; i++) {
    cout << "\n" << string((this->rows - i - 1) * 4, ' ');
    cout << BLUE << "| " << RESET;
    for (int j = 0; j <= i * 2; j++) {
        cout << this->board[i][j] << BLUE << " | " << RESET;
    }
    if (i == 0){
        cout << BLUE << "\n    -=-=-=-=-=-=-" << RESET;
    }else{
    cout << BLUE << "\n-=-=-=-=-=-=-=-=-=-=-" << RESET;
    }
}
cout << endl;
}

// Returns true if there is any winner
template <typename T>
bool pyramic_Board<T>::is_win() {
    string res = "";
        res = string(1,this->board[0][0]) + string(1,this->board[1][1]) + string(1,this->board[2][2]);
        if (res == "XXX" || res == "OOO") return true; // Check column

        res = string(1,this->board[0][0]) + string(1,this->board[1][0]) + string(1,this->board[2][0]);
        if (res == "XXX" || res == "OOO") return true; // Check diagonal

        res = string(1,this->board[0][0]) + string(1,this->board[1][2]) + string(1,this->board[2][4]);
        if (res == "XXX" || res == "OOO") return true; // Check diagonal
//----------------------------------------------------------------------------------------------------
        res = string(1,this->board[1][0]) + string(1,this->board[1][1]) + string(1,this->board[1][2]);
        if (res == "XXX" || res == "OOO") return true; // Check second row

        res = string(1,this->board[2][0]) + string(1,this->board[2][1]) + string(1,this->board[2][2]);
        if (res == "XXX" || res == "OOO") return true; // Check Third row

        res = string(1,this->board[2][1]) + string(1,this->board[2][2]) + string(1,this->board[2][3]);
        if (res == "XXX" || res == "OOO") return true; // Check Third row

        res = string(1,this->board[2][2]) + string(1,this->board[2][3]) + string(1,this->board[2][4]);
        if (res == "XXX" || res == "OOO") return true; // Check Third row

        res = string(1,this->board[2][0]) + string(1,this->board[2][1]) + string(1,this->board[2][2]);
        if (res == "XXX" || res == "OOO") return true; // Check Third row

    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool pyramic_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool pyramic_Board<T>::game_is_over() {
    return is_win() || is_draw();
}
//--------------------------------------

// Constructor for pyramic_Player
template <typename T>
pyramic_Player<T>::pyramic_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void pyramic_Player<T>::getmove(int& x, int& y) {
    while (true) {
        // handle errors
        cout << CYAN << "\n" << this->getname() << "'s turn. Enter your move in row from 1 to 3, column from 1 to 5: " << RESET;
        if (!(cin >> x >> y)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << RED << "Invalid input. Please enter numbers for row and column again." << RESET << endl;
            cout << x << "  " << y <<endl;
            continue;
        }
        if (x < 1 || x > 3 || y < 1 || y > 5) {
            cerr << RED << "Invalid input. Please enter numbers for row and column again."  << RESET << endl;
            cout << x << "  " << y <<endl;
            continue;
        }
        if ((x == 1) && (y != 1)) {
            cerr << RED << "Invalid input. Please enter numbers for row and column again."  << RESET << endl;
            cout << x << "  " << y <<endl;
            continue;
        }
        if ((x == 2) && (y != 1 && y != 2 && y != 3)) {
            cerr << RED << "Invalid input. Please enter numbers for row and column again."  << RESET << endl;
            cout << x << "  " << y <<endl;
            continue;
        }
        // Make the values valid for index
        --x;
        --y;
        // Remove the move from the moves vector
        pair<int, int> targetPair = {x, y};
        auto it = std::find(moves.begin(), moves.end(), targetPair);
        int i = std::distance(moves.begin(), it);
        moves[i] = moves.back();
        moves.pop_back();
        break;
    }
}

// Constructor for pyramic_Random_Player
template <typename T>
pyramic_Random_Player<T>::pyramic_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    static int random_computer_num = 0;
    random_computer_num++; // To know which random player (in case of two random playing)
    this->dimension = 5;
    this->name = "Random Comaputer Player " + std::to_string(random_computer_num);
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
    }

template <typename T>
void pyramic_Random_Player<T>::getmove(int& x, int& y) {
    int index = rand() % moves.size(); // Get a random move
    x = moves[index].first;
    y = moves[index].second;
    cout << CYAN << "Random computer move: " << (x + 1) << ", " << (y + 1) << endl;
    moves[index] = moves.back();
    moves.pop_back(); // Remove the move from the moves vector
    Sleep(500); // To see the move
}

#endif //_pyramic_H