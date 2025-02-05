
---

# Snake Game 

This is classic snake game inspired from old keypad phone game using linked list in c++. this is a simple game in which snake's movement can be control from keyboard .

## Features:

- **Snake Movement**: The snake moves continuously, and its direction is controlled by the player.
- **Food Collection**: The snake collects food, growing longer with each piece of food eaten.
- **Score Tracking**: The player's score increases as the snake eats food. The high score is tracked throughout the game session.
- **Self-Collision**: If the snake collides with its own body, the game ends.
- **Boundary Collision**: If the snake hits the boundary of the grid, the game ends.
- **Linked List Implementation**: The snake’s body is managed using a linked list, where each node represents a part of the snake's body.

## Controls:

- **W**: Move up.
- **S**: Move down.
- **A**: Move left.
- **D**: Move right.
- **Q**: Quit the game.
- **R**: Restart the game after a game over.

## How to Play:

1. Run the program. You’ll be greeted with a welcome message.
2. Use the **W**, **S**, **A**, **D** keys to control the direction of the snake.
3. The goal is to collect the food (represented by the letter "F") to grow the snake and increase your score.
4. Avoid colliding with the boundaries or the snake’s own body.
5. The game ends when the snake collides with itself or the boundary.
6. After the game ends, you can choose to restart the game by pressing **R** or quit by pressing any other key.
## System requirement:
1. Operating system must be windows .
2. disk should have free space for code.
## Compilation Instructions:

To compile and run this game, follow the instructions 

1. Make sure you have a C++ compiler .
2. Save the game code in a file named `SnakeGame.cpp`.
3. Open a command prompt and navigate to the directory where the file is located.
4. Compile the program using the following command (for MinGW):
    
    ```
    g++ SnakeGame.cpp -o SnakeGame
    ```
    
5. Run the game:
    
    ```
    SnakeGame.exe
    ```
    
