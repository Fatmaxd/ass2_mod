#include <iostream>
#include "BoardGame_Classes.h"
#include "4x4XO.h"

using namespace std;

int main() {
    cout << "                 ---------------------------\n"
    << YELLOW << "                 -=Welcome to 4x4 X O Game=-\n" << RESET
    << "                 ---------------------------\n";
    
    int choice;
    Player<char>* players[2];
    X_O_Board<char>* B = new X_O_Board<char>();
    string player1Name, player2Name;
    while (true){
        // Set up player 1
        cout << CYAN << "1) Human         2) Random Computer\n"
            << "Choose Player one type: " << RESET;
        cin >> choice;
        if (choice == 1) {
            cout << CYAN << "Enter Player one name: " << RESET;
            cin >> player1Name;
            players[0] = new X_O_Player<char>(player1Name, 'X');
        }else if (choice == 2){
            players[0] = new X_O_Random_Player<char>('X');
        }
        else{
            cerr << RED << "Invalid choice for Player 1.\n" << RESET;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << RED << "-------------------------------------------------\n\n" << RESET;
            continue;
        }

        // Set up player 2
        cout << CYAN << "Choose Player two type: " << RESET;
        cin >> choice;
        if (choice == 1) {
            cout << CYAN << "Enter Player 2 name: " << RESET;
            cin >> player2Name;
            players[1] = new X_O_Player<char>(player2Name, 'O');
        }else if (choice == 2){
            players[1] = new X_O_Random_Player<char>('O');
        }
        else{
            cerr << RED << "Invalid choice for Player 2.\n" << RESET;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << RED << "-------------------------------------------------\n\n" << RESET;
            continue;
        }
        
        // Create the game manager and run the game
        GameManager<char> wordTTT_game(B, players);
        wordTTT_game.run();

        // Clean up
        delete B;
        for (int i = 0; i < 2; ++i) {
            delete players[i];
        }
        break;
    }
    cout << RED << "\n-------------------------------------------------\n\n" << RESET;
    return 0;
}