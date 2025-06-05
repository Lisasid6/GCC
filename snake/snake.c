#include "raylib.h"
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define CELL_SIZE 20
#define COLS (SCREEN_WIDTH / CELL_SIZE)
#define ROWS (SCREEN_HEIGHT / CELL_SIZE)
#define MAX_LENGTH 100

// Position 2D (x, y) sur la grille
typedef struct {
    int x;
    int y;
} Position;

// Directions possibles
typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT
} Direction;

// 🔁 Déclarations des fonctions utilisées
void GenerateFruit();
bool CheckCollisions();

// 🐍 Données du jeu
Position snake[MAX_LENGTH];   // Tableau contenant les segments du serpent
int snakeLength;              // Longueur actuelle du serpent
Position fruit;               // Position actuelle du fruit
Direction direction;          // Direction actuelle du serpent
bool gameOver;                // Indique si la partie est terminée
int score;                    // Score actuel

int frameCounter = 0;         // Compteur de frames (pour ralentir le jeu)
int updateRate = 10;          // Nombre de frames entre deux mouvements du serpent

// 🔄 Initialise tous les paramètres du jeu
void InitGame() {
    snakeLength = 1;
    snake[0].x = COLS / 2;
    snake[0].y = ROWS / 2;

    direction = RIGHT;
    gameOver = false;
    score = 0;

    srand(time(NULL));
    GenerateFruit();
}

// 🍏 Génére un fruit à une position aléatoire libre
void GenerateFruit() {
    bool valid = false;
    while (!valid) {
        fruit.x = rand() % COLS;
        fruit.y = rand() % ROWS;
        valid = true;

        // Vérifie que le fruit ne spawn pas sur le corps du serpent
        for (int i = 0; i < snakeLength; i++) {
            if (snake[i].x == fruit.x && snake[i].y == fruit.y) {
                valid = false;
                break;
            }
        }
    }
}

// 🔁 Met à jour la logique du jeu à chaque pas
void UpdateGame() {
    // 🔃 Gère les touches pour changer la direction
    if (IsKeyPressed(KEY_UP) && direction != DOWN) direction = UP;
    else if (IsKeyPressed(KEY_DOWN) && direction != UP) direction = DOWN;
    else if (IsKeyPressed(KEY_LEFT) && direction != RIGHT) direction = LEFT;
    else if (IsKeyPressed(KEY_RIGHT) && direction != LEFT) direction = RIGHT;

    // 🧱 Déplace tous les segments vers l’avant
    for (int i = snakeLength - 1; i > 0; i--) {
        snake[i] = snake[i - 1];
    }

    // 🧠 Déplace la tête selon la direction
    switch (direction) {
        case UP:    snake[0].y--; break;
        case DOWN:  snake[0].y++; break;
        case LEFT:  snake[0].x--; break;
        case RIGHT: snake[0].x++; break;
    }

    // 💥 Vérifie les collisions
    if (CheckCollisions()) {
        gameOver = true;
        return;
    }

    // 🍎 Mange le fruit
    if (snake[0].x == fruit.x && snake[0].y == fruit.y) {
        snakeLength++;
        score += 10;
        GenerateFruit();
    }
}

// 🎯 Vérifie les collisions avec murs ou soi-même
bool CheckCollisions() {
    // Collision avec les murs
    if (snake[0].x < 0 || snake[0].x >= COLS || snake[0].y < 0 || snake[0].y >= ROWS) {
        return true;
    }

    // Collision avec soi-même
    for (int i = 1; i < snakeLength; i++) {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
            return true;
        }
    }

    return false;
}

// 🎨 Dessine la scène du jeu
void DrawGame() {
    ClearBackground(RAYWHITE);

    // Grille (optionnel)
    /*
    for (int i = 0; i < COLS; i++) {
        for (int j = 0; j < ROWS; j++) {
            DrawRectangleLines(i * CELL_SIZE, j * CELL_SIZE, CELL_SIZE, CELL_SIZE, LIGHTGRAY);
        }
    }
    */

    // 🐍 Dessine le serpent
    for (int i = 0; i < snakeLength; i++) {
        DrawRectangle(snake[i].x * CELL_SIZE, snake[i].y * CELL_SIZE, CELL_SIZE, CELL_SIZE, DARKGREEN);
    }

    // 🍎 Dessine le fruit
    DrawRectangle(fruit.x * CELL_SIZE, fruit.y * CELL_SIZE, CELL_SIZE, CELL_SIZE, RED);

    // 🧮 Score
    DrawText(TextFormat("Score: %d", score), 10, 10, 20, BLACK);

    // 💀 Message Game Over
    if (gameOver) {
        DrawText("GAME OVER!", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 20, 40, MAROON);
        DrawText("Appuie sur R pour rejouer", SCREEN_WIDTH / 2 - 120, SCREEN_HEIGHT / 2 + 30, 20, DARKGRAY);
    }
}

// ♻ Réinitialise le jeu
void ResetGame() {
    InitGame();
}

// 🧠 Fonction principale
int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake avec Raylib");
    SetTargetFPS(60);

    InitGame();

    while (!WindowShouldClose()) {
        BeginDrawing();

        if (!gameOver) {
            frameCounter++;
            if (frameCounter >= updateRate) {
                UpdateGame();
                frameCounter = 0;
            }
        } else {
            if (IsKeyPressed(KEY_R)) {
                ResetGame();
            }
        }

        DrawGame();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
