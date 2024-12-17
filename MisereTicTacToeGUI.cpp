#include <SFML/Graphics.hpp>
#include "MisereTicTacToe.h"
#include <vector>
#include <iostream>

void runMisereTicTacToe() {
    MisereTicTacToe game(3, 3, NORMAL);  // Initialize the game with a 3x3 board
    sf::RenderWindow window(sf::VideoMode(400, 500), "Misere Tic Tac Toe");
    window.setFramerateLimit(60);

    // Load font
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading font" << std::endl;
        return;
    }

    // UI text elements
    sf::Text currentPlayerText, gameOverText;
    currentPlayerText.setFont(font);
    currentPlayerText.setCharacterSize(20);
    currentPlayerText.setFillColor(sf::Color::White);

    gameOverText.setFont(font);
    gameOverText.setCharacterSize(30);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(100, 450);

    // Create the grid
    const int cellSize = 100;
    std::vector<std::vector<sf::RectangleShape>> cells(3, std::vector<sf::RectangleShape>(3));
    sf::Color bgColor(30, 30, 30);
    sf::Color gridColor(50, 50, 50);
    sf::Color textColorX(230, 100, 150);
    sf::Color textColorO(150, 100, 230);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cells[i][j].setSize(sf::Vector2f(cellSize - 5, cellSize - 5));
            cells[i][j].setFillColor(gridColor);
            cells[i][j].setOutlineColor(sf::Color::Black);
            cells[i][j].setOutlineThickness(2);
            cells[i][j].setPosition(j * cellSize, i * cellSize);
        }
    }

    char currentPlayer = 'X';

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && !game.game_is_over()) {
                int x = event.mouseButton.y / cellSize;
                int y = event.mouseButton.x / cellSize;

                if (game.update_board(x, y, currentPlayer)) {
                    game.switchPlayer();
                    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
                    gameOverText.setString("");
                }
                else {
                    gameOverText.setString("Invalid Move!");
                }
            }
        }

        // Update UI
        currentPlayerText.setString("Player " + std::string(1, currentPlayer) + "'s turn");
        currentPlayerText.setPosition(10, 400);

        if (game.game_is_over()) {
            if (game.is_win()) {
                // Switch the winner display: if X wins, show O wins, and vice versa
                currentPlayerText.setString("Player " + std::string(1, (currentPlayer == 'X' ? 'X' : 'O')) + " wins!");
            }
            else {
                currentPlayerText.setString("Draw!");
            }
        }


        window.clear(bgColor);

        // Draw cells and other UI elements
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                window.draw(cells[i][j]);

                // Display the cell value
                char cellValue = game.getCell(i, j);
                if (cellValue != '.') {
                    sf::Text cellText;
                    cellText.setFont(font);
                    cellText.setCharacterSize(50);
                    cellText.setString(cellValue);
                    cellText.setFillColor(cellValue == 'X' ? textColorX : textColorO);
                    cellText.setPosition(j * cellSize + 25, i * cellSize + 10);
                    window.draw(cellText);
                }
            }
        }

        window.draw(currentPlayerText);
        window.draw(gameOverText);

        window.display();
    }

}
