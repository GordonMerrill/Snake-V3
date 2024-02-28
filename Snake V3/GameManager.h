#pragma once
#include "Main.h"

struct Snake {
    bool    Alive;
    int     Dir;
    int     Length;
    Vector2 head;
    Vector2 tail[GRID_HEIGHT * GRID_WIDTH];
};

class MenuManager;

class GameManager {
public:
    Vector2 apple;
    struct Snake snake;
    int tempDir; // Temporary direction to prevent immediate direction reversals.
    int frameCount; // Frame counter for game updates.
    int speed;

    void Init();

    void RandomizeApplePosition();

    bool Update(MenuManager* MM);

    void Draw(MenuManager* MM);
};