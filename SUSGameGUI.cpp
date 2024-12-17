#include <SFML/Graphics.hpp>
#include "SUSGame.h"
#include <vector>
#include <iostream>

void runSUSGameGUI() {
    SUSGame game(SUSGame::EASY);
    sf::RenderWindow window(sf::VideoMode(600, 700), "SUS Game");
    window.setFramerateLimit(60);

    // Load font
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading font" << std::endl;
        return;
    }

    // Create UI text elements
    sf::Text currentPlayerText, scoreText, gameOverText, instructionText;
    currentPlayerText.setFont(font);
    currentPlayerText.setCharacterSize(20);
    currentPlayerText.setFillColor(sf::Color::White);

    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(sf::Color::White);

    gameOverText.setFont(font);
    gameOverText.setCharacterSize(30);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(150, 650);

    instructionText.setFont(font);
    instructionText.setCharacterSize(20);
    instructionText.setFillColor(sf::Color::White);
    instructionText.setPosition(10, 600);
    instructionText.setString("Click on a cell to make your move.");

    // Game mode selection buttons
    sf::RectangleShape buttonHuman(sf::Vector2f(200, 50));
    sf::RectangleShape buttonAI(sf::Vector2f(200, 50));
    sf::RectangleShape buttonRandom(sf::Vector2f(200, 50));

    sf::Text buttonTextHuman, buttonTextAI, buttonTextRandom;
    buttonTextHuman.setFont(font);
    buttonTextAI.setFont(font);
    buttonTextRandom.setFont(font);

    buttonTextHuman.setCharacterSize(20);
    buttonTextAI.setCharacterSize(20);
    buttonTextRandom.setCharacterSize(20);

    buttonTextHuman.setFillColor(sf::Color::Black);
    buttonTextAI.setFillColor(sf::Color::Black);
    buttonTextRandom.setFillColor(sf::Color::Black);

    buttonHuman.setPosition(200, 250);
    buttonAI.setPosition(200, 320);
    buttonRandom.setPosition(200, 390);

    buttonTextHuman.setString("Play vs Human");
    buttonTextAI.setString("Play vs AI");
    buttonTextRandom.setString("Play vs Random");

    auto centerTextInButton = [](sf::Text& text, const sf::RectangleShape& button) {
        sf::FloatRect textBounds = text.getLocalBounds();
        sf::Vector2f buttonPos = button.getPosition();
        sf::Vector2f buttonSize = button.getSize();

        // Center the text within the button
        float x = buttonPos.x + (buttonSize.x - textBounds.width) / 2 - textBounds.left;
        float y = buttonPos.y + (buttonSize.y - textBounds.height) / 2 - textBounds.top;
        text.setPosition(x, y);
        };

    // Center text in buttons
    centerTextInButton(buttonTextHuman, buttonHuman);
    centerTextInButton(buttonTextAI, buttonAI);
    centerTextInButton(buttonTextRandom, buttonRandom);

    // Button colors
    sf::Color buttonColor(200, 200, 200);
    buttonHuman.setFillColor(buttonColor);
    buttonAI.setFillColor(buttonColor);
    buttonRandom.setFillColor(buttonColor);

    bool modeSelected = false;
    bool againstAI = false;
    bool againstRandom = false;

    // Main loop for initial game mode selection
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (!modeSelected) {
                    // Handle game mode selection
                    if (buttonHuman.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        modeSelected = true;
                        againstAI = false;
                        againstRandom = false;
                    }
                    else if (buttonAI.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        modeSelected = true;
                        againstAI = true;
                        againstRandom = false;
                    }
                    else if (buttonRandom.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        modeSelected = true;
                        againstAI = false;
                        againstRandom = true;
                    }
                }
            }
        }

        // Clear the window before drawing
        window.clear(sf::Color(30, 30, 30));

        // Draw buttons and their corresponding text
        window.draw(buttonHuman);
        window.draw(buttonTextHuman);

        window.draw(buttonAI);
        window.draw(buttonTextAI);

        window.draw(buttonRandom);
        window.draw(buttonTextRandom);

        window.display();

        // If mode is selected, start the game loop
        if (modeSelected) {
            break;
        }
    }

    // Create the grid after the mode selection is done
    const int cellSize = 150;
    std::vector<std::vector<sf::RectangleShape>> cells(3, std::vector<sf::RectangleShape>(3));
    sf::Color gridColor(50, 50, 50);
    sf::Color textColorS(230, 100, 150);
    sf::Color textColorU(150, 100, 230);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cells[i][j].setSize(sf::Vector2f(cellSize - 5, cellSize - 5));
            cells[i][j].setFillColor(gridColor);
            cells[i][j].setOutlineColor(sf::Color::White);
            cells[i][j].setOutlineThickness(2);
            cells[i][j].setPosition(j * cellSize, i * cellSize);
        }
    }

    // Main game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && !game.game_is_over()) {
                int x = event.mouseButton.y / cellSize;
                int y = event.mouseButton.x / cellSize;
                
                if (event.type == sf::Event::MouseButtonPressed && !game.game_is_over()) {
                    int x = event.mouseButton.y / cellSize;
                    int y = event.mouseButton.x / cellSize;

                    // Handle move based on game mode
                    if (!againstAI && !againstRandom) {
                        // Human vs Human mode: Always allow move
                        if (!game.update_board(x, y, game.currentPlayerSymbol)) {
                            gameOverText.setString("Invalid Move! Try Again");
                        }
                        else {
                            gameOverText.setString("");
                            game.switchPlayer();
                        }
                    }
                    else if (game.currentPlayerSymbol == game.player1Symbol) {
                        // AI or Random mode: Only allow human player (S) to move
                        if (!game.update_board(x, y, game.currentPlayerSymbol)) {
                            gameOverText.setString("Invalid Move! Try Again");
                        }
                        else {
                            gameOverText.setString("");
                            game.switchPlayer();
                        }
                    }// AI or Random player moves
                    if (!game.game_is_over() && (againstAI || againstRandom)) {
                        if (game.currentPlayerSymbol == game.player2Symbol) {
                            std::pair<int, int> move;
                            if (againstAI) {
                                move = game.getAIMove();
                            }
                            else {
                                move = game.getRandomMove();
                            }
                            game.update_board(move.first, move.second, game.currentPlayerSymbol);
                            game.switchPlayer();
                        }
                    }
                }
            }
        }

        // AI or Random player moves
        if (!game.game_is_over() && (againstAI || againstRandom)) {
            if (game.currentPlayerSymbol == game.player2Symbol) {
                std::pair<int, int> move;
                if (againstAI) {
                    move = game.getAIMove();
                }
                else {
                    move = game.getRandomMove();
                }
                game.update_board(move.first, move.second, game.currentPlayerSymbol);
                game.switchPlayer();
            }
        }

        // Update UI text
        currentPlayerText.setString("Player " + std::string(1, game.currentPlayerSymbol) + "'s turn");
        currentPlayerText.setPosition(10, 510);

        scoreText.setString("Player S: " + std::to_string(game.player1Score) + " | Player U: " + std::to_string(game.player2Score));
        scoreText.setPosition(10, 550);

        if (game.game_is_over()) {
            if (game.player1Score > game.player2Score) {
                gameOverText.setString("Player S Wins!");
            }
            else if (game.player2Score > game.player1Score) {
                gameOverText.setString("Player U Wins!");
            }
            else {
                gameOverText.setString("It's a Draw!");
            }
            instructionText.setString("Restart the application to play again.");
        }

        // Draw everything
        window.clear(sf::Color(30, 30, 30));  // Clear window with dark background

        // Draw the cells of the grid
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                window.draw(cells[i][j]);

                // Get the cell's current value
                char cellValue = game.getBoardValue(i, j);
                if (cellValue != '.') {
                    sf::Text cellText;
                    cellText.setFont(font);
                    cellText.setCharacterSize(50);
                    cellText.setString(cellValue);
                    cellText.setFillColor(cellValue == 'S' ? textColorS : textColorU);

                    // Center the text within the cell
                    float textX = j * cellSize + (cellSize - cellText.getGlobalBounds().width) / 2;
                    float textY = i * cellSize + (cellSize - cellText.getGlobalBounds().height) / 2;
                    cellText.setPosition(textX, textY);

                    window.draw(cellText);
                }
            }
        }

        // Draw score, current player text, and instructions
        window.draw(currentPlayerText);
        window.draw(scoreText);
        window.draw(gameOverText);
        window.draw(instructionText);

        // Display the window contents
        window.display();
    }
}