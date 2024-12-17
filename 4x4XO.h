#ifndef _4X4X_O_H
#define _4X4X_O_H

#include "BoardGame_Classes.h"

template <typename T>
class X_O_Board:public Board<T> {
public:
    X_O_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class X_O_Player : public Player<T> {
public:
    X_O_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class X_O_Random_Player : public RandomPlayer<T>{
public:
    X_O_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>
#include <limits>
#include <string>
#include <windows.h>
using namespace std;

// For colors in CLI
const string BLUE = "\033[34m", CYAN = "\033[1;36m", YELLOW = "\033[1;33m", RED = "\033[1;31m", RESET = "\033[0m";
bool is_computer = false; // To do not show error message for computer

// Constructor for X_O_Board
template <typename T>
X_O_Board<T>::X_O_Board() {
    this->rows = this->columns = 4;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = ' ';
        }
    }
    this->n_moves = 0;
    this->board[0][0] = this->board[0][2] = this->board[3][1] = this->board[3][3] = 'O';
    this->board[0][1] = this->board[0][3] = this->board[3][0] = this->board[3][2] = 'X';
}

// ! To update the board i have to get the old position, but header where the functions are written doesn't include this parameter, 
// ! and I can't change it. So, I tried my best to guess the old position without taking it directly, and this is what I came up with.
// ! To understand it better, try two random computer players against each other.
// ! Please note that this game is not mandatory for us, but I decided to work on it, and this is what I have come up with.
template <typename T>
bool X_O_Board<T>::update_board(int x, int y, T symbol) { 
    int old_x = -1, old_y = -1;
    for (int i = 0; i < this->rows; i++) { // To know the old position
        for (int j = 0; j < this->columns; j++) {
            if (this->board[i][j] == toupper(symbol)) {
                old_x = i;
                old_y = j;
                break;
            }
        }
        if (old_x != -1) break;
    }
    if (old_x == -1 || old_y == -1) {
        if (!is_computer) cout << RED << "Error: Your token is not on the board." << RESET << endl;
        return false;
    }
    if (x < 0 || x >= this->rows || y < 0 || y >= this->columns) {
        if (!is_computer) cout << RED << "Invalid move. Out of range" << RESET << endl;
        return false;
    }
    if (this->board[x][y] != ' ') {
        if (!is_computer) cout << RED << "Invalid move. Destination cell is occupied." << RESET << endl;
        return false;
    }
    
    // Check if move is to an adjacent square in any direction
    bool valid_move = ((old_x == x && abs(old_y - y) == 1) || (old_y == y && abs(old_x - x) == 1));

    if (!valid_move) {
        if (!is_computer) cout << RED << "Invalid move. Move isn't an adjacent square." << RESET << endl;
        return false;
    }

    this->board[old_x][old_y] = ' '; // Delete the old position
    this->board[x][y] = toupper(symbol);
    this->n_moves++;
    return true;
}

// Display the board
template <typename T>
void X_O_Board<T>::display_board() {
    cout << BLUE << "\n-=-=-=-=-=-=-=-=-" << RESET;
    for (int i = 0; i < this->rows; i++) {
        cout << BLUE << "\n| " << RESET;
        for (int j = 0; j < this->columns; j++) {
            cout << this->board[i][j] << BLUE << " | " << RESET;
        }
        cout << BLUE << "\n-=-=-=-=-=-=-=-=-" << RESET;
    }
    cout << endl;
}

// Returns true if there is any winner
template <typename T>
bool X_O_Board<T>::is_win() {
    string res = "";
    for (int i = 0; i < this->rows; i++) {
        // Check rows
        res = string(1,this->board[i][0]) + string(1,this->board[i][1]) + string(1,this->board[i][2]);
        if (res == "XXX" || res == "OOO") return true;
        res = string(1,this->board[i][1]) + string(1,this->board[i][2]) + string(1,this->board[i][3]);
        if (res == "XXX" || res == "OOO") return true;

        // Check columns
        res = string(1,this->board[0][i]) + string(1,this->board[1][i]) + string(1,this->board[2][i]);
        if (res == "XXX" || res == "OOO") return true;
        res = string(1,this->board[1][i]) + string(1,this->board[2][i]) + string(1,this->board[3][i]);
        if (res == "XXX" || res == "OOO") return true;

        // Check diagonal(\)
        if (i == 0 || i == 1){
            res = string(1,this->board[i][i]) + string(1,this->board[i+1][i+1]) + string(1,this->board[i+2][i+2]);
            if (res == "XXX" || res == "OOO") return true;
        }
    }
    res = string(1,this->board[1][0]) + string(1,this->board[2][1]) + string(1,this->board[3][2]);
    if (res == "XXX" || res == "OOO") return true;
    res = string(1,this->board[0][1]) + string(1,this->board[1][2]) + string(1,this->board[2][3]);
    if (res == "XXX" || res == "OOO") return true;

    // Check diagonal(/)
    res = string(1,this->board[0][2]) + string(1,this->board[1][1]) + string(1,this->board[2][0]);
    if (res == "XXX" || res == "OOO") return true;
    res = string(1,this->board[3][1]) + string(1,this->board[2][2]) + string(1,this->board[1][3]);
    if (res == "XXX" || res == "OOO") return true;
    res = string(1,this->board[3][0]) + string(1,this->board[2][1]) + string(1,this->board[1][2]);
    if (res == "XXX" || res == "OOO") return true;
    res = string(1,this->board[2][1]) + string(1,this->board[1][2]) + string(1,this->board[0][3]);
    if (res == "XXX" || res == "OOO") return true;

    return false;
}

// Return true if 100 moves are done and no winner
template <typename T>
bool X_O_Board<T>::is_draw() {
    return (this->n_moves == 101 && !is_win());
}

template <typename T>
bool X_O_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
X_O_Player<T>::X_O_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void X_O_Player<T>::getmove(int& x, int& y) {
    while (true) {
        // handle errors
        cout << CYAN << "\n" << this->getname() << "'s turn. Enter your move in row and column from 1 to 4: " << RESET;
        if (!(cin >> x >> y)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << RED << "Invalid input. Please enter numbers for row and column again." << RESET << endl;
            cout << x << "  " << y <<endl;
            continue;
        }
        if (x < 1 || x > 4 || y < 1 || y > 4) {
            cerr << RED << "Invalid input. Please enter numbers for row and column again."  << RESET << endl;
            cout << x << "  " << y <<endl;
            continue;
        }
        // Make the values valid for index
        --x;
        --y;
        is_computer = false;
        break;
    }
}

// Constructor for X_O_Random_Player
template <typename T>
X_O_Random_Player<T>::X_O_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    static int random_computer_num = 0;
    random_computer_num++; // To know which random player (in case of two random playing)
    this->dimension = 4;
    this->name = "Random Computer Player " + std::to_string(random_computer_num);
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void X_O_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 3
    y = rand() % this->dimension;
    is_computer = true;

}

#endif //_4X4X_O_H