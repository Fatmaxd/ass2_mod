# Tic Tac Toe Game

This project is a graphical Tic-Tac-Toe game built using C++ and the [SFML](https://www.sfml-dev.org/) library for rendering. The game offers various levels of AI difficulty, customizable board sizes, and win conditions, providing an engaging experience for players of all skill levels.

## Features

- **Graphical User Interface (GUI)**: The game uses SFML to create a simple and interactive interface.
- **Multiple AI Difficulty Levels**: Players can choose between Easy, Medium, Hard, and Ultra levels of AI difficulty.
- **Customizable Board**: You can adjust the board size and win condition length from the options panel.
- **Interactive Gameplay**: Play against the AI or another player locally with full mouse support.
- **Win/Tie Detection**: The game automatically detects wins and ties, displaying results with custom graphics.

## Getting Started

### Prerequisites

To build and run this project, you'll need:

- C++ Compiler
- SFML 2.5+ (Simple and Fast Multimedia Library)
- CMake (optional, for building)

## Controls
- **Start Game**: Click the "Start Game" button to begin playing.
- **Board Size**: Use the + and - buttons to adjust the board size.
- **Win Condition**: Adjust the win length (number of marks in a row needed to win).
- **AI Difficulty**: Choose AI difficulty from Easy, Medium, Hard, and Ultra.
- **Gameplay**: Click on the board to make a move. The AI will respond automatically.

## How to Play
- Select the board size and difficulty level from the options.
- Click "Start Game" to begin.
- Take turns placing X's and O's on the board.
- The game ends when a player gets the required number of marks in a row (win length) or when the board is full (tie).

## Future Improvements
- **Multiplayer Mode**: Add a local multiplayer option to allow two players to play on the same device.
- **Online Multiplayer**: Implement an online multiplayer mode.
- **Improved AI**: Make the AI more challenging and unpredictable.

---

## Game Concept: Tic-Tac-Toe, But With a Twist!

Now, let's talk about the *not-so-boring* part — the game itself! This isn’t your average Tic-Tac-Toe, folks. While the concept is simple (X’s and O’s), we’ve kicked it up a notch with **different board sizes** and **customizable win conditions**. Want to play on a 5x5 board? Go ahead! Feel like making it harder with a win condition of 4-in-a-row? Absolutely!

But here’s the fun part: this is built using a **generic board game framework**! So while you’re enjoying the game of Tic-Tac-Toe (or X-O as it’s called in some circles), you’ll also appreciate the **magic of Object-Oriented Programming (OOP)** at work. It’s like a *Tic-Tac-Toe factory* in here.

Here’s what you get:
1. **GameManager**: It keeps things running smoothly, like a boss. It manages the game, players, and handles turn-swapping.
2. **Player**: This represents you, the hero, with a name and symbol. You make moves like a pro.
3. **Abstract Board**: The foundation for all games — this defines the rules, but it's up to each game to say how to play.
4. **ARandomPlayer**: Just like it sounds, this player loves to play randomly. No strategy, just moves like a wild card!

So while you’re battling it out in Tic-Tac-Toe, remember that this framework is a breeze to modify and create **new games**. All you need to do is take these classes and create your own fun, like making a crazy 3D Tic-Tac-Toe game or a super-challenging version with some quirky rules.

Get ready for some intense, nerdy fun and **let the games begin**!

