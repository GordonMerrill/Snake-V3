#include "GameManager.h"
#include "MenuManager.h"

// Initializes game settings, including window size and position, and sets up the initial state of the snake and apple.
void GameManager::Init() {
    // Set screen dimensions based on grid size and border.
    screenWidth  = GRID_WIDTH  * GRID_UNIT_SIZE + BORDER_SIZE * 2;
    screenHeight = GRID_HEIGHT * GRID_UNIT_SIZE + BORDER_SIZE * 2;
    SetWindowSize(screenWidth, screenHeight);

    SetWindowPosition(GetMonitorWidth(GetCurrentMonitor()) * .5 - screenWidth * .5, GetMonitorHeight(GetCurrentMonitor()) * .5 - screenHeight * .5); // Center the game window on the screen.

    frameCount = 0;
    tempDir = 0;

    // Initialize snake properties.
    snake.Alive  = true;
    snake.head.x = GRID_WIDTH  / 2.f; // Start position in the middle of the grid.
    snake.head.y = GRID_HEIGHT / 2.f;
    snake.Dir    = 0;                 // Initial direction.
    snake.Length = 3;                 // Starting length.

    // Set initial tail positions to the same as the head.
    for (int i = 0; i < snake.Length; i++) {
        snake.tail[i].x = snake.head.x;
        snake.tail[i].y = snake.head.y;
    }

    RandomizeApplePosition(); // Place the apple in a random position.
}

// Helper function to check if a position is occupied by the snake.
bool IsPositionOnSnake(const Vector2& pos, const Snake& snake) {
    // Check head position.
    if (pos.x == snake.head.x && pos.y == snake.head.y) return true;

    // Check tail positions.
    for (int i = 0; i < snake.Length; ++i) {
        if (pos.x == snake.tail[i].x && pos.y == snake.tail[i].y) return true;
    }

    return false;
}

// Places the apple in a random position that is not occupied by the snake.
void GameManager::RandomizeApplePosition() {
    do {
        apple.x = GetRandomValue(0, GRID_WIDTH - 1);
        apple.y = GetRandomValue(0, GRID_HEIGHT - 1);
    } while (IsPositionOnSnake(apple, snake));
}

bool GameManager::Update(MenuManager* MM) {
    windowShouldClose = WindowShouldClose();

    // Controler
    if ((snake.Dir == 1 || snake.Dir == 3) && IsKeyDown(KEY_W)) tempDir = 0;
    else if ((snake.Dir == 0 || snake.Dir == 2) && IsKeyDown(KEY_D)) tempDir = 1;
    else if ((snake.Dir == 1 || snake.Dir == 3) && IsKeyDown(KEY_S)) tempDir = 2;
    else if ((snake.Dir == 0 || snake.Dir == 2) && IsKeyDown(KEY_A)) tempDir = 3;

    if ((frameCount % speed) == 0) {
        snake.Dir = tempDir;

        // Tail Updater
        for (int i = snake.Length; i > 0; i--) {
            snake.tail[i].x = snake.tail[i - 1].x;
            snake.tail[i].y = snake.tail[i - 1].y;
        }

        snake.tail[0].x = snake.head.x;
        snake.tail[0].y = snake.head.y;

        // Moves the snake in the direction its facing / Wall Collision Detection
        switch (snake.Dir) {
        case 0:
            snake.head.y--;
            if (snake.head.y == -1) snake.Alive = false;
            break;
        case 1:
            snake.head.x++;
            if (snake.head.x == GRID_WIDTH) snake.Alive = false;
            break;
        case 2:
            snake.head.y++;
            if (snake.head.y == GRID_HEIGHT) snake.Alive = false;
            break;
        case 3:
            snake.head.x--;
            if (snake.head.x == -1) snake.Alive = false;
            break;
        }

        // Tail Collision Detection
        for (int i = snake.Length - 1; i >= 0 && snake.Alive; i--) {
            if ((snake.head.x == snake.tail[i].x) && (snake.head.y == snake.tail[i].y)) snake.Alive = false;
        }

        // Death Detection
        if (!snake.Alive) {
            scene = 0;
            MM->coolDown = MM->coolDownAmt * 4;
            return false;
        }

        // Apple Detection
        if (snake.head.x == apple.x && snake.head.y == apple.y) {
            snake.Length++;
            RandomizeApplePosition();
        }
    }

    frameCount++;
    return true;
}

void GameManager::Draw(MenuManager* MM){
    BeginDrawing();

    ClearBackground(MM->BACKGROUND);

    // Apple
    DrawRectangle(
        apple.x * GRID_UNIT_SIZE + BORDER_SIZE,
        apple.y * GRID_UNIT_SIZE + BORDER_SIZE,
        GRID_UNIT_SIZE,
        GRID_UNIT_SIZE,
        MM->APPLE);

    // Tail
    for (int i = snake.Length - 1; i >= 0; i--) {
        DrawRectangle(
            snake.tail[i].x * GRID_UNIT_SIZE + BORDER_SIZE,
            snake.tail[i].y * GRID_UNIT_SIZE + BORDER_SIZE,
            GRID_UNIT_SIZE,
            GRID_UNIT_SIZE,
            MM->SNAKE);
    }

    // Head
    DrawRectangle(
        snake.head.x * GRID_UNIT_SIZE + BORDER_SIZE,
        snake.head.y * GRID_UNIT_SIZE + BORDER_SIZE,
        GRID_UNIT_SIZE,
        GRID_UNIT_SIZE,
        MM->SNAKE);

    // Grid
    for (int i = GRID_WIDTH; i >= 0; i--) {
        DrawLine(
            GRID_UNIT_SIZE * i + BORDER_SIZE,
            BORDER_SIZE,
            GRID_UNIT_SIZE * i + BORDER_SIZE,
            screenHeight - BORDER_SIZE,
            MM->FOREGROUND);
    }

    for (int i = GRID_HEIGHT; i >= 0; i--) {
        DrawLine(
            BORDER_SIZE,
            GRID_UNIT_SIZE * i + BORDER_SIZE,
            screenWidth - BORDER_SIZE,
            GRID_UNIT_SIZE * i + BORDER_SIZE,
            MM->FOREGROUND);
    }

    EndDrawing();
}