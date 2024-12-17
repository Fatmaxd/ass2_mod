#include <vector>
#include <climits>
#include <cstdlib>
#include <cmath> // For sine wave effect
#include <SFML/Graphics.hpp>
#include "5x5TicTacToeBoard.h"
#include "MisereTicTacToe.h"
#include "FourInARowBoard.h"
#include "NumericalTicTacToe.h"
#include "SUSGame.h"
#include "UltimateGame.h"
#include "BoardGames_Classes.h"

using namespace std;

// Function to create a button with text, position, and size
sf::RectangleShape createButton(float x, float y, float width, float height, sf::Font& font, const std::string& text, int textSize, sf::Text& buttonText) {
    sf::RectangleShape button(sf::Vector2f(width, height));
    button.setFillColor(sf::Color(70, 70, 70)); // Darker grey for the button
    button.setPosition(x, y);
    button.setOutlineColor(sf::Color(0, 0, 0));
    button.setOutlineThickness(2);

    buttonText.setFont(font);
    buttonText.setString(text);
    buttonText.setCharacterSize(textSize);
    buttonText.setFillColor(sf::Color(255, 255, 255)); // White text for contrast

    // Ensure the text is centered within the button
    buttonText.setPosition(
        x + (width - buttonText.getLocalBounds().width) / 2 - buttonText.getLocalBounds().left,  // Center horizontally
        y + (height - buttonText.getLocalBounds().height) / 2 - buttonText.getLocalBounds().top // Center vertically
    );

    return button;
}

// Function to create the help window text with game descriptions
class HelpWindow {
private:
    sf::Text helpText;
    sf::Font font;
    float scrollOffset = 0;
    float maxScrollOffset = 0;
    const float scrollSpeed = 20.0f;
    const float windowHeight = 500.0f; // Increased window height

public:
    HelpWindow(sf::Font& inputFont) {
        font = inputFont;
        helpText.setFont(font);
        helpText.setCharacterSize(18);
        helpText.setFillColor(sf::Color(220, 220, 220)); // Light grey text
        helpText.setString(
            "Game Descriptions:\n\n"
            "1. Pyramid Tic-Tac-Toe: A pyramid-shaped board.\n    Win by aligning 3 X's or O's vertically, horizontally, or diagonally.\n"
            "  --------------------------------------------------------------------------------\n"
            "2. Four-in-a-Row: A 7x6 grid game.\n    First to get four-in-a-row wins.\n"
            "  --------------------------------------------------------------------------------\n"
            "3. 5x5 Tic Tac Toe: Fill a 5x5 grid and\n    count the most three-in-a-rows to win.\n"
            "  --------------------------------------------------------------------------------\n"
            "4. Word Tic-Tac-Toe: Form valid words with letters\n    on a 3x3 grid. Win by completing a word in any direction.\n"
            "  --------------------------------------------------------------------------------\n"
            "5. Numerical Tic-Tac-Toe: Use numbers to form 15 in a row,\n    column, or diagonal. Odd vs. Even numbers.\n"
            "  --------------------------------------------------------------------------------\n"
            "6. Misere Tic Tac Toe: A twist on regular Tic-Tac-Toe.\n    Aim to force your opponent into winning.\n"
            "  --------------------------------------------------------------------------------\n"
            "7. 4x4 Tic Tac Toe: A 4x4 grid version of Tic Tac Toe.\n    Align 3 tokens in a row to win.\n"
            "  --------------------------------------------------------------------------------\n"
            "8. Ultimate Tic Tac Toe: Play on a 3x3 grid of smaller\n    Tic Tac Toe boards. Win 3 in a row on the main board.\n"
            "  --------------------------------------------------------------------------------\n"
            "9. SUS: Form the sequence \"S-U-S\" on a 3x3 grid.\n    Most sequences win.\n"
            "  --------------------------------------------------------------------------------\n\n"
            "Group Members:\nFatma, Yasmina, Ahmed\nFCAI, Cairo University"
        );


        // Calculate max scroll offset
        sf::FloatRect textBounds = helpText.getLocalBounds();
        maxScrollOffset = std::max(0.0f, textBounds.height - 300.0f); // Assuming window height is 400
    }

    void handleEvent(const sf::Event& event, sf::RenderWindow& helpWindow) {
        // Handle mouse wheel scrolling
        if (event.type == sf::Event::MouseWheelScrolled) {
            scrollOffset -= event.mouseWheelScroll.delta * scrollSpeed;

            // Clamp scroll offset
            scrollOffset = std::max(0.0f, std::min(scrollOffset, maxScrollOffset));
        }
    }

    void draw(sf::RenderWindow& helpWindow) {
        // Create a view for scrolling
        sf::View scrollView = helpWindow.getView();
        scrollView.reset(sf::FloatRect(0, scrollOffset, helpWindow.getSize().x, helpWindow.getSize().y));
        helpWindow.setView(scrollView);

        // Draw the text
        helpText.setPosition(30, 30);
        helpWindow.draw(helpText);

        // Reset to default view
        helpWindow.setView(helpWindow.getDefaultView());
    }
};

void showHelpWindow(sf::RenderWindow& helpWindow, sf::Font& font) {
    HelpWindow helpWindowManager(font);

    while (helpWindow.isOpen()) {
        sf::Event event;
        while (helpWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                helpWindow.close();

            helpWindowManager.handleEvent(event, helpWindow);
        }

        helpWindow.clear(sf::Color(18, 18, 18)); // Dark background
        helpWindowManager.draw(helpWindow);
        helpWindow.display();
    }
}

class ParticleSystem {
private:
    struct Particle {
        sf::Vector2f position;
        sf::Vector2f velocity;
        sf::CircleShape shape;
    };
    std::vector<Particle> particles;

public:
    ParticleSystem(int count, sf::RenderWindow& window) {
        for (int i = 0; i < count; ++i) {
            Particle p;
            p.position = sf::Vector2f(rand() % window.getSize().x, rand() % window.getSize().y);
            p.velocity = sf::Vector2f(((rand() % 200) - 100) / 50.0f, ((rand() % 200) - 100) / 50.0f);
            p.shape = sf::CircleShape(2); // Small particle
            p.shape.setFillColor(sf::Color(150, 150, 255, 200)); // Soft blue
            p.shape.setPosition(p.position);
            particles.push_back(p);
        }
    }
    void update(float deltaTime, sf::RenderWindow& window) {
        for (auto& p : particles) {
            p.position += p.velocity * deltaTime;
            // Wrap-around screen edges
            if (p.position.x < 0) p.position.x += window.getSize().x;
            if (p.position.y < 0) p.position.y += window.getSize().y;
            if (p.position.x > window.getSize().x) p.position.x -= window.getSize().x;
            if (p.position.y > window.getSize().y) p.position.y -= window.getSize().y;
            p.shape.setPosition(p.position);
        }
    }

    void draw(sf::RenderWindow& window) {
        for (const auto& p : particles) {
            window.draw(p.shape);
        }
    }
};


int main() {
    // Create the main window with a dark theme
    sf::RenderWindow window(sf::VideoMode(800, 600), "Tic-Tac-Toe Game Menu", sf::Style::Close | sf::Style::Titlebar);
    window.setFramerateLimit(60);

    // Load a modern font (change the font path if needed)
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
        return -1;
    }

    // Create text objects for the button labels
    sf::Text buttonText[10];

    // Create buttons for the game options (9 buttons)
    sf::RectangleShape btn[9];
    btn[0] = createButton(100, 150, 250, 50, font, "Pyramid Tic-Tac-Toe", 20, buttonText[0]);
    btn[1] = createButton(450, 150, 250, 50, font, "Four-in-a-Row", 20, buttonText[1]);
    btn[2] = createButton(100, 220, 250, 50, font, "5x5 Tic Tac Toe", 20, buttonText[2]);
    btn[3] = createButton(450, 220, 250, 50, font, "Word Tic-Tac-Toe", 20, buttonText[3]);
    btn[4] = createButton(100, 290, 250, 50, font, "Numerical Tic-Tac-Toe", 20, buttonText[4]);
    btn[5] = createButton(450, 290, 250, 50, font, "Misere Tic Tac Toe", 20, buttonText[5]);
    btn[6] = createButton(100, 360, 250, 50, font, "4 x 4 Tic-Tac-Toe", 20, buttonText[6]);
    btn[7] = createButton(450, 360, 250, 50, font, "Ultimate Tic Tac Toe", 20, buttonText[7]);

    // Center Game 9 button horizontally in its row
    btn[8] = createButton(275, 430, 250, 50, font, "SUS", 20, buttonText[8]);

    ParticleSystem particles(100, window);
    sf::Clock clock; // Timer for animations


    // Create a "Help" button
    sf::Text helpButtonText;
    sf::RectangleShape btnHelp = createButton(650, 20, 120, 50, font, "Help", 20, helpButtonText);

    // Main loop for the window
    // Main loop for the window
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear the screen with a smooth dark background
        window.clear(sf::Color(18, 18, 18)); // Very dark background color

        // Draw the welcome text with a fun and creative style
        sf::Text welcomeText("   Welcome to the Tic-Tac-Toe Menu!", font, 32);
        welcomeText.setFillColor(sf::Color(255, 255, 255)); // White color
        welcomeText.setStyle(sf::Text::Bold);
        welcomeText.setPosition(80, 50);


        // Smooth color transition (left to right effect)
        float elapsedTime = clock.getElapsedTime().asSeconds() * 0.5f; // Slows down the color change
        int r = static_cast<int>((sin(elapsedTime * 2.0f) * 127 + 128)); // Red component changes
        int g = static_cast<int>((sin(elapsedTime * 2.0f + 1.0f) * 127 + 128)); // Green component changes
        int b = static_cast<int>((sin(elapsedTime * 2.0f + 2.0f) * 127 + 128)); // Blue component changes

        welcomeText.setFillColor(sf::Color(r, g, b));


        window.draw(welcomeText);

        // Handle button hover effects
        for (int i = 0; i < 9; ++i) {
            // Get the mouse position
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            if (btn[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                // Lighter color with a gradient effect
                btn[i].setFillColor(sf::Color(90, 90, 90)); // Lighter gray color for the button on hover

                // Adding a subtle shadow effect (offset)
                btn[i].setOutlineColor(sf::Color(50, 50, 50));  // Darker outline
                btn[i].setOutlineThickness(3);  // Slightly thicker outline

                // Scale effect with smooth transition (use some smooth factor for scaling)
                btn[i].setScale(1.05f, 1.05f);  // Slightly bigger on hover for a modern effect
            }
            else {
                // Original button appearance
                btn[i].setFillColor(sf::Color(70, 70, 70)); // Default dark gray color
                btn[i].setOutlineColor(sf::Color(0, 0, 0));  // Reset outline color
                btn[i].setOutlineThickness(2);  // Reset outline thickness
                btn[i].setScale(1.0f, 1.0f);  // Return to original size
            }
        }

        // Handle hover effect for the Help button
        if (btnHelp.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
            // Lighter color with a gradient effect
            btnHelp.setFillColor(sf::Color(90, 90, 90)); // Lighter grey for the button on hover
            btnHelp.setOutlineColor(sf::Color(50, 50, 50)); // Darker outline for depth
            btnHelp.setOutlineThickness(3); // Slightly thicker outline for the help button

            // Scale effect for a subtle modern feel
            btnHelp.setScale(1.05f, 1.05f);
        }
        else {
            // Original color and size for Help button
            btnHelp.setFillColor(sf::Color(70, 70, 70)); // Default color
            btnHelp.setOutlineColor(sf::Color(0, 0, 0));  // Reset outline color
            btnHelp.setOutlineThickness(2);  // Reset outline thickness
            btnHelp.setScale(1.0f, 1.0f);  // Return to original size
        }


        // Draw buttons
        for (int i = 0; i < 9; ++i) {
            window.draw(btn[i]);
            window.draw(buttonText[i]);
        }

        // Draw Help button
        window.draw(btnHelp);
        window.draw(helpButtonText);

        // Handle button hover effects
        for (int i = 0; i < 9; ++i) {
            if (btn[i].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
                btn[i].setFillColor(sf::Color(100, 100, 100)); // Slightly lighter grey on hover
            }
            else {
                btn[i].setFillColor(sf::Color(70, 70, 70)); // Original dark grey color
            }
        }

        if (btnHelp.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
            btnHelp.setFillColor(sf::Color(100, 100, 100)); // Lighter grey on hover for Help button
        }
        else {
            btnHelp.setFillColor(sf::Color(70, 70, 70)); // Original color for Help button
        }

        // Handle button clicks
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            if (btn[1].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
                // Close the main menu window
                window.close();

                // Launch the Misere Tic Tac Toe game
                runFourInARowGame();
            }


            if (btn[2].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
                // Close the main menu window
                window.close();

                // Launch the 5x5 Tic Tac Toe game
                run5x5TicTacToe();
            }

            if (btn[4].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
                // Close the main menu window
                window.close();

                // Launch the 5x5 Tic Tac Toe game
                NumericalTicTacToe game;
                game.play();
            }

            if (btn[5].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
                // Close the main menu window
                window.close();

                // Launch the Misere Tic Tac Toe game
                runMisereTicTacToe();
            }

            if (btn[7].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
                // Close the main menu window
                window.close();

                runUltimateTicTacToe();
            }

            if (btn[8].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
                // Close the main menu window
                window.close();
                runSUSGameGUI();
            }

            if (btnHelp.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
                // Open the Help window
                sf::RenderWindow helpWindow(sf::VideoMode(600, 400), "Help - Game Descriptions", sf::Style::Close);
                showHelpWindow(helpWindow, font);
            }
        }

        // Display everything on the window
        window.display();
    }

    return 0;
}