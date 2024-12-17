#include <iostream>
#include "BoardGame_Classes.h"
#include "wordTTT.h"

using namespace std;

int main() {
    cout << "                ------------------------------------\n"
        << YELLOW << "                -=Welcome to Word Tic-Tac-Toe Game=-\n" << RESET
        << "                ------------------------------------\n";
    while (true){
        int choice;
        Player<char>* players[2];
        wordTTT_Board<char>* B = new wordTTT_Board<char>();
        string player1Name, player2Name;
        char charactour;
        // Set up player 1
        cout << CYAN << "1) Human         2) Random Computer         3) Exit\n"
            << "Choose Player one type: " << RESET;
            // << "3. Smart Computer (AI)\n";
        cin >> choice;
        if (choice == 1) {
            cout << CYAN << "Enter Player one name: " << RESET;
            cin >> player1Name;
            players[0] = new wordTTT_Player<char>(player1Name, charactour);
        }else if (choice == 2){
            players[0] = new wordTTT_Random_Player<char>(charactour);
        }
        // else if (choice == 3){}
        else{
            cerr << RED << "Invalid choice for Player 1.\n" << RESET;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << RED << "-------------------------------------------------\n\n" << RESET;
            continue;
        }

        // Set up player 2
        cout << CYAN << "Choose Player two type: " << RESET;
            // << "3. Smart Computer (AI)\n";
        cin >> choice;
        if (choice == 1) {
            cout << CYAN << "Enter Player 2 name: " << RESET;
            cin >> player2Name;
            players[1] = new wordTTT_Player<char>(player2Name, charactour);
        }else if (choice == 2){
            players[1] = new wordTTT_Random_Player<char>(charactour);
        }
        // else if (choice == 3){}
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