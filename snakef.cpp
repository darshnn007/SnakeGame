#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
//hello 

using namespace std;

const int GRID_WIDTH = 45;
const int GRID_HEIGHT = 20;
const int INITIAL_SNAKE_LENGTH = 3;

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };

struct Node {
    int x, y;
    Node* next;
    Node(int x, int y) : x(x), y(y), next(nullptr) {}
};

class Snake {
private:
    Node* head;
    Direction dir;

public:
    Snake() {
        initSnake();
    }

    ~Snake() {
        freeSnake();
    }

    // Initializes the snake with the starting length.
    void initSnake() {
        // Start from the center.
        head = new Node(GRID_WIDTH / 2, GRID_HEIGHT / 2);
        dir = STOP;
        // Build the rest of the snake downward (for example).
        for (int i = 1; i < INITIAL_SNAKE_LENGTH; i++) {
            Node* newNode = new Node(head->x, head->y + i);
            newNode->next = head;
            head = newNode;
        }
    }

    // Frees all allocated nodes.
    void freeSnake() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Resets the snake to its initial state.
    void reset() {
        freeSnake();
        initSnake();
    }

    Node* getHead() { return head; }

    void setDirection(Direction newDir) {
        // Prevent snake from reversing into itself.
        if ((dir == LEFT && newDir == RIGHT) || (dir == RIGHT && newDir == LEFT) ||
            (dir == UP && newDir == DOWN) || (dir == DOWN && newDir == UP))
            return;
        dir = newDir;
    }

    void move(bool grow = false) {
        // If no direction is set, do not move.
        if (dir == STOP) return;

        int newX = head->x, newY = head->y;
        switch (dir) {
            case LEFT:  newX--; break;
            case RIGHT: newX++; break;
            case UP:    newY--; break;
            case DOWN:  newY++; break;
            default: break;
        }

        Node* newHead = new Node(newX, newY);
        newHead->next = head;
        head = newHead;

        if (!grow) {
            // Remove the tail node.
            Node* temp = head;
            while (temp->next->next) {
                temp = temp->next;
            }
            delete temp->next;
            temp->next = nullptr;
        }
    }

    bool checkCollision() {
        // Check collision with self.
        for (Node* temp = head->next; temp != nullptr; temp = temp->next) {
            if (temp->x == head->x && temp->y == head->y)
                return true;
        }
        // Check collision with borders.
        // Since borders are at x == 0, x == GRID_WIDTH-1, y == 0, or y == GRID_HEIGHT-1.
        if (head->x == 0 || head->x == GRID_WIDTH - 1 ||
            head->y == 0 || head->y == GRID_HEIGHT - 1)
            return true;
        return false;
    }
};

class Game {
private:
    Snake snake;
    pair<int, int> food;
    bool gameOver;
    int score;

public:
    Game() : gameOver(false), score(0) {
        srand(static_cast<unsigned>(time(0)));
        spawnFood();
    }

    // Spawn food only in cells not occupied by the border.
    void spawnFood() {
        food.first = 1 + rand() % (GRID_WIDTH - 2);
        food.second = 1 + rand() % (GRID_HEIGHT - 2);
    }

    void input() {
        if (_kbhit()) {
            char key = _getch();
            switch (key) {
                case 'a': case 'A': snake.setDirection(LEFT); break;
                case 'd': case 'D': snake.setDirection(RIGHT); break;
                case 'w': case 'W': snake.setDirection(UP); break;
                case 's': case 'S': snake.setDirection(DOWN); break;
                case 'q': case 'Q': gameOver = true; break;
            }
        }
    }

    void logic() {
        // Get current head position before moving.
        pair<int, int> headPos = { snake.getHead()->x, snake.getHead()->y };
        bool grow = (headPos == food);
        snake.move(grow);
        if (grow) {
            score++;
            spawnFood();
        }
        if (snake.checkCollision())
            gameOver = true;
    }

    void draw() {
        // Reset the cursor to the top left.
        COORD cursorPos = { 0, 0 };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPos);
        // Create a grid filled with spaces.
        string grid(GRID_WIDTH * GRID_HEIGHT, ' ');

        // Draw the borders.
        for (int y = 0; y < GRID_HEIGHT; y++) {
            for (int x = 0; x < GRID_WIDTH; x++) {
                if (y == 0 || y == GRID_HEIGHT - 1 || x == 0 || x == GRID_WIDTH - 1) {
                    grid[y * GRID_WIDTH + x] = '#';
                }
            }
        }

        // Place the food.
        grid[food.second * GRID_WIDTH + food.first] = 'F';

        // Draw the snake’s body.
        for (Node* temp = snake.getHead(); temp != nullptr; temp = temp->next) {
            // Only draw if within valid grid coordinates.
            if (temp->x >= 0 && temp->x < GRID_WIDTH &&
                temp->y >= 0 && temp->y < GRID_HEIGHT)
            {
                grid[temp->y * GRID_WIDTH + temp->x] = 'O';
            }
        }

        // Display the grid.
        for (int y = 0; y < GRID_HEIGHT; y++) {
            for (int x = 0; x < GRID_WIDTH; x++) {
                cout << grid[y * GRID_WIDTH + x];
            }
            cout << endl;
        }

        // Display the score.
        cout << "Score: " << score << endl;
    }

    void run() {
        while (!gameOver) {
            input();
            logic();
            draw();
            Sleep(300);  // Adjust delay as needed for smooth gameplay.
        }
        cout << "Game Over! Final Score: " << score << endl;
        cout << "Press R to Restart or Q to Quit." << endl;
        char choice;
        while (true) {
            choice = _getch();
            if (choice == 'r' || choice == 'R') {
                resetGame();
                run();
                break;
            } else if (choice == 'q' || choice == 'Q') {
                break;
            }
        }
    }

    void resetGame() {
        snake.reset();
        score = 0;
        gameOver = false;
        spawnFood();
    }
};

int main() {
    cout << "Welcome to the Snake Game! Press any key to start..." << endl;
    _getch();  // Wait for user to start the game
    Game game;
    game.run();
    return 0;
}
