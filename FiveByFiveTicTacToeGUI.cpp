#include <SFML/Graphics.hpp>
#include "5x5TicTacToeBoard.h"
#include <vector>
#include <iostream>

void run5x5TicTacToe() {
    FiveByFiveTicTacToeBoard game;
    sf::RenderWindow window(sf::VideoMode(600, 700), "5x5 Modern Three-in-a-Row");
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
    sf::RectangleShape buttonSmartAI(sf::Vector2f(200, 50));
    sf::RectangleShape buttonHard(sf::Vector2f(200, 50));
    sf::RectangleShape buttonUltimate(sf::Vector2f(200, 50));

    sf::Text buttonTextHuman, buttonTextAI, buttonTextSmartAI, buttonTextHard, buttonTextUltimate;
    buttonTextHuman.setFont(font);
    buttonTextAI.setFont(font);
    buttonTextSmartAI.setFont(font);
    

    buttonTextHuman.setCharacterSize(20);
    buttonTextAI.setCharacterSize(20);
    buttonTextSmartAI.setCharacterSize(20);
   

    buttonTextHuman.setFillColor(sf::Color::Black);
    buttonTextAI.setFillColor(sf::Color::Black);
    buttonTextSmartAI.setFillColor(sf::Color::Black);
   

    buttonHuman.setPosition(200, 250);
    buttonAI.setPosition(200, 320);
    buttonSmartAI.setPosition(200, 390);


    buttonTextHuman.setString("Play vs Human");
    buttonTextAI.setString("Play vs AI");
    buttonTextSmartAI.setString("Play vs Smart AI");

    auto centerTextInButton = [](sf::Text& text, const sf::RectangleShape& button) {
        sf::FloatRect textBounds = text.getLocalBounds();
        sf::Vector2f buttonPos = button.getPosition();
        sf::Vector2f buttonSize = button.getSize();

        // Center the text within the button
        float x = buttonPos.x + (buttonSize.x - textBounds.width) / 2 - textBounds.left;
        float y = buttonPos.y + (buttonSize.y - textBounds.height) / 2 - textBounds.top;
        text.setPosition(x, y);
    };

    // Call this function for each button-text pair
    centerTextInButton(buttonTextHuman, buttonHuman);
    centerTextInButton(buttonTextAI, buttonAI);
    centerTextInButton(buttonTextSmartAI, buttonSmartAI);


    bool modeSelected = false;
    std::string mode;


    // Main loop for initial game mode and difficulty selection
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
                        mode = "Human";
                        modeSelected = true;
                    }
                    else if (buttonAI.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        mode = "AI";
                        modeSelected = true;
                    }
                    else if (buttonSmartAI.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        mode = "SmartAI";
                        modeSelected = true;
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

        window.draw(buttonSmartAI);
        window.draw(buttonTextSmartAI);


        window.display();

        // If mode is selected, start the game loop
        if (modeSelected) {
            game.setGameMode(mode);
            break;
        }
    }

    // Create the grid after the mode selection is done
    const int cellSize = 100;
    std::vector<std::vector<sf::RectangleShape>> cells(5, std::vector<sf::RectangleShape>(5));
    sf::Color gridColor(50, 50, 50);
    sf::Color textColorX(230, 100, 150);
    sf::Color textColorO(150, 100, 230);

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cells[i][j].setSize(sf::Vector2f(cellSize - 5, cellSize - 5));
            cells[i][j].setFillColor(gridColor);
            cells[i][j].setOutlineColor(sf::Color::Black);
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

                if (mode == "Human" || game.getCurrentPlayer() == 'X') {
                    if (!game.makeMove(x, y)) {
                        gameOverText.setString("Invalid Move! Try Again");
                    }
                    else {
                        gameOverText.setString("");
                    }
                }
            }
        }

        // AI Moves
        if (!game.game_is_over() && mode != "Human" && game.getCurrentPlayer() == 'O') {
            if (mode == "AI") {
                game.aiMove();
            }
            else if (mode == "SmartAI") {
                game.smartAiMove();
            }
        }

        // Update UI text
        currentPlayerText.setString("Player " + std::string(1, game.getCurrentPlayer()) + "'s turn");
        currentPlayerText.setPosition(10, 510);

        scoreText.setString("Player X: " + std::to_string(game.getPlayerXScore()) + " | Player O: " + std::to_string(game.getPlayerOScore()));
        scoreText.setPosition(10, 550);

        if (game.game_is_over()) {
            gameOverText.setString("Game Over!");
            instructionText.setString("Restart the application to play again.");
        }

        // Draw everything
        window.clear(sf::Color(30, 30, 30));  // Clear window with dark background

        // Draw the cells of the grid
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                window.draw(cells[i][j]);

                // Get the cell's current value ('X', 'O', or '.')
                char cellValue = game.getCell(i, j);
                if (cellValue != '.') {
                    sf::Text cellText;
                    cellText.setFont(font);
                    cellText.setCharacterSize(50);
                    cellText.setString(cellValue);
                    cellText.setFillColor(cellValue == 'X' ? textColorX : textColorO);

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
