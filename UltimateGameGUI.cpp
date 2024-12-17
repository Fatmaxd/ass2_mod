#include <SFML/Graphics.hpp>
#include "UltimateGame.h"
#include <vector>
#include <iostream>

void runUltimateTicTacToe() {
    BigBoard game;  // Initialize the game
    sf::RenderWindow window(sf::VideoMode(900, 900), "Ultimate Tic Tac Toe"); // Set window to 900x900 for 9x9 grid
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
    gameOverText.setPosition(150, 850); // Adjusted for the new window height

    // Create the grid
    const int cellSize = 100;
    std::vector<std::vector<std::vector<sf::RectangleShape>>> cells(BIG_BOARD_SIZE, std::vector<std::vector<sf::RectangleShape>>(BIG_BOARD_SIZE, std::vector<sf::RectangleShape>(SMALL_BOARD_SIZE * SMALL_BOARD_SIZE)));

    sf::Color gridColor(50, 50, 50);
    sf::Color textColorX(230, 100, 150);
    sf::Color textColorO(150, 100, 230);
    sf::Color bgColor(30, 30, 30);
    sf::Color starLineColor(255, 215, 0); // A golden color for the separating lines

    // Setup the cell shapes for all small boards
    for (int bigRow = 0; bigRow < BIG_BOARD_SIZE; ++bigRow) {
        for (int bigCol = 0; bigCol < BIG_BOARD_SIZE; ++bigCol) {
            for (int smallRow = 0; smallRow < SMALL_BOARD_SIZE; ++smallRow) {
                for (int smallCol = 0; smallCol < SMALL_BOARD_SIZE; ++smallCol) {
                    int xPos = (bigCol * SMALL_BOARD_SIZE + smallCol) * cellSize;
                    int yPos = (bigRow * SMALL_BOARD_SIZE + smallRow) * cellSize;

                    cells[bigRow][bigCol][smallRow * SMALL_BOARD_SIZE + smallCol].setSize(sf::Vector2f(cellSize - 5, cellSize - 5));
                    cells[bigRow][bigCol][smallRow * SMALL_BOARD_SIZE + smallCol].setFillColor(gridColor);
                    cells[bigRow][bigCol][smallRow * SMALL_BOARD_SIZE + smallCol].setOutlineColor(sf::Color::Black);
                    cells[bigRow][bigCol][smallRow * SMALL_BOARD_SIZE + smallCol].setOutlineThickness(2);
                    cells[bigRow][bigCol][smallRow * SMALL_BOARD_SIZE + smallCol].setPosition(xPos, yPos);
                }
            }
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
        currentPlayerText.setPosition(10, 850); // Adjusted for the new window height

        if (game.game_is_over()) {
            if (game.is_win()) {
                currentPlayerText.setString("Player " + std::string(1, (currentPlayer == 'X' ? 'O' : 'X')) + " wins!");
            }
            else {
                currentPlayerText.setString("Draw!");
            }
        }

        window.clear(bgColor);

        // Draw cells for each small board
        for (int bigRow = 0; bigRow < BIG_BOARD_SIZE; ++bigRow) {
            for (int bigCol = 0; bigCol < BIG_BOARD_SIZE; ++bigCol) {
                for (int smallRow = 0; smallRow < SMALL_BOARD_SIZE; ++smallRow) {
                    for (int smallCol = 0; smallCol < SMALL_BOARD_SIZE; ++smallCol) {
                        window.draw(cells[bigRow][bigCol][smallRow * SMALL_BOARD_SIZE + smallCol]);

                        // Display the cell value
                        char cellValue = game.getSmallBoard(bigRow, bigCol).grid[smallRow][smallCol];
                        if (cellValue != '.') {
                            sf::Text cellText;
                            cellText.setFont(font);
                            cellText.setCharacterSize(50);
                            cellText.setString(cellValue);
                            cellText.setFillColor(cellValue == 'X' ? textColorX : textColorO);
                            cellText.setPosition(bigCol * SMALL_BOARD_SIZE * cellSize + smallCol * cellSize + 25,
                                bigRow * SMALL_BOARD_SIZE * cellSize + smallRow * cellSize + 10);
                            window.draw(cellText);
                        }
                    }
                }
            }
        }

        // Draw a golden "star" line separating 3x3 blocks
        for (int i = 1; i < 3; ++i) {
            // Horizontal line
            sf::RectangleShape horizontalLine(sf::Vector2f(900, 5));
            horizontalLine.setFillColor(starLineColor);
            horizontalLine.setPosition(0, i * 3 * cellSize); // Separating after every 3 rows
            window.draw(horizontalLine);

            // Vertical line
            sf::RectangleShape verticalLine(sf::Vector2f(5, 900));
            verticalLine.setFillColor(starLineColor);
            verticalLine.setPosition(i * 3 * cellSize, 0); // Separating after every 3 columns
            window.draw(verticalLine);
        }

        window.draw(currentPlayerText);
        window.draw(gameOverText);

        window.display();
    }
}
