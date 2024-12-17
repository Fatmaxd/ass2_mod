#ifndef _wordTTT_H
#define _wordTTT_H

#include "BoardGame_Classes.h"

template <typename T>
class wordTTT_Board:public Board<T> {
public:
    wordTTT_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class wordTTT_Player : public Player<T> {
public:
    wordTTT_Player (string name, T symbol);
    void getmove(int& x, int& y) ;
};

template <typename T>
class wordTTT_Random_Player : public RandomPlayer<T>{
public:
    wordTTT_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};

//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
#include <unordered_set>
#include <fstream>
#include <limits> 
#include <windows.h>
using namespace std;

// For colors in CLI
const string BLUE = "\033[34m", CYAN = "\033[1;36m", YELLOW = "\033[1;33m", RED = "\033[1;31m", RESET = "\033[0m";

bool is_file_open = true;

// Function to read words from the file and returns an unordered set
unordered_set<string> loud_file_in_set() {
    ifstream file("dic.txt");
    unordered_set<string> words;
    if (!file.is_open()) {
        cerr << RED << "Error: Unable to open the file. Please try again.\n\n" << RESET;
        is_file_open = false;
        return words;
    }
    string word;
    while (file >> word) {
        words.insert(word);
    }

    file.close();
    return words;
}

// Constructor for wordTTT_Board
template <typename T>
wordTTT_Board<T>::wordTTT_Board() {
    this->rows = this->columns = 3;
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
bool wordTTT_Board<T>::update_board(int x, int y, T mark) {
    this->n_moves++;
    this->board[x][y] = toupper(mark);
    return true;
}

// Display the board
template <typename T>
void wordTTT_Board<T>::display_board() {
    cout << BLUE << "\n-=-=-=-=-=-=-" << RESET;
    for (int i = 0; i < this->rows; i++) {
        cout << BLUE << "\n| " << RESET;
        for (int j = 0; j < this->columns; j++) {
            cout << this->board[i][j] << BLUE << " | " << RESET;
        }
        cout << BLUE << "\n-=-=-=-=-=-=-" << RESET;
    }
    cout << endl;
}

// Returns true if there is any winner
template <typename T>
bool wordTTT_Board<T>::is_win() {
    unordered_set<string> dictionary = loud_file_in_set();
    string res = "";
    for (int i = 0; i < this->rows; i++) {
    // Check rows
        res = string(1,this->board[i][0]) + string(1,this->board[i][1]) + string(1,this->board[i][2]);
            if (dictionary.find(res) != dictionary.end()) {
                cout << CYAN << "Word(" << RED << res << CYAN << ") FOUND! (row), after " << this->n_moves << " moves" << RESET << endl;
                return true;
            }
        res = string(1,this->board[i][2]) + string(1,this->board[i][1]) + string(1,this->board[i][0]);
            if (dictionary.find(res) != dictionary.end()) {
                cout << CYAN << "Word(" << RED << res << CYAN << ") FOUND! (row), after " << this->n_moves << " moves" << RESET << endl;
                return true;
            }
    // Check columns
        res = string(1,this->board[0][i]) + string(1,this->board[1][i]) + string(1,this->board[2][i]);
            if (dictionary.find(res) != dictionary.end()) {
                cout << CYAN << "Word(" << RED << res << CYAN << ") FOUND! (column), after " << this->n_moves << " moves" << RESET << endl;
                return true;
            }
        res = string(1,this->board[2][i]) + string(1,this->board[1][i]) + string(1,this->board[0][i]);
            if (dictionary.find(res) != dictionary.end()) {
                cout << CYAN << "Word(" << RED << res << CYAN << ") FOUND! (column), after " << this->n_moves << " moves" << RESET << endl;
                return true;
            }
    // Check diagonal(\)
        res = string(1,this->board[0][0]) + string(1,this->board[1][1]) + string(1,this->board[2][2]); 
            if (dictionary.find(res) != dictionary.end()) {
                cout << CYAN << "Word(" << RED << res << CYAN << ") FOUND! (diagonal), after " << this->n_moves << " moves" << RESET << endl;
                return true;
            }
        res = string(1,this->board[2][2]) + string(1,this->board[1][1]) + string(1,this->board[0][0]);
            if (dictionary.find(res) != dictionary.end()) {
                cout << CYAN << "Word(" << RED << res << CYAN << ") FOUND! (diagonal), after " << this->n_moves << " moves" << RESET << endl;
                return true;
            }
    // Check diagonal(/)
        res = string(1,this->board[0][2]) + string(1,this->board[1][1]) + string(1,this->board[2][0]);
            if (dictionary.find(res) != dictionary.end()) {
                cout << CYAN << "Word(" << RED << res << CYAN << ") FOUND! (diagonal), after " << this->n_moves << " moves" << RESET << endl;
                return true;
            }
        res = string(1,this->board[2][0]) + string(1,this->board[1][1]) + string(1,this->board[0][2]);
            if (dictionary.find(res) != dictionary.end()) {
                cout << CYAN << "Word(" << RED << res << CYAN << ") FOUND! (diagonal), after " << this->n_moves << " moves" << RESET << endl;
                return true;
            }
    }
    if (!is_file_open){ // To handle the error if the file is not opened
        return true;
    }
    return false;
}

template <typename T>
bool wordTTT_Board<T>::is_draw() { // Draw if the moves are more thann 50
    return (this->n_moves == 51 && !is_win());
}

template <typename T>
bool wordTTT_Board<T>::game_is_over() {
    return is_win() || is_draw();
}
//--------------------------------------

// Constructor for wordTTT_Player
template <typename T>
wordTTT_Player<T>::wordTTT_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void wordTTT_Player<T>::getmove(int& x, int& y) {
    while (true) {
        // handle errors
        cout << CYAN << "\n" << this->getname() << "'s turn. Enter your move in row, column from 1 to 3, and character: " << RESET;
        if (!(cin >> x >> y >> this->symbol)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << RED << "Invalid input. Please enter numbers for row and column, and a character again." << RESET << endl;
            continue;
        }
        if (x < 1 || x > 3 || y < 1 || y > 3 || !isalpha(this->symbol)) {
            cerr << RED << "Invalid input. Please enter numbers for row and column, and a character again."  << RESET << endl;
            continue;
        }
        // Make the values valid for index
        --x;
        --y;
        break;
    }
}

// Constructor for wordTTT_Random_Player
template <typename T>
wordTTT_Random_Player<T>::wordTTT_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    static int random_computer_num = 0;
    random_computer_num++; // To know which random player (in case of two random playing)
    this->dimension = 3;
    this->name = "Random Computer Player " + std::to_string(random_computer_num);
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
    }

template <typename T>
void wordTTT_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
    this->symbol = 'A' + rand() % 26; // Random Alphabit
    cout << CYAN << "\nRandom copmuter: " << RESET << (x + 1) << " " << (y + 1)<< endl;
    Sleep(500); // To see the move
}
#endif //_wordTTT_H