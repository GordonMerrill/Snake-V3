#include "Main.h"
#include "GameManager.h"
#include "MenuManager.h"

int screenWidth = 0;
int screenHeight = 0;

int scene = 0;
bool windowShouldClose = false;

int main(void) {
    SetConfigFlags(FLAG_WINDOW_UNDECORATED);
    InitWindow(screenWidth, screenHeight, "Snake");

    SetTargetFPS(144);

    GameManager GM;
    MenuManager MM;

    // Main Loop
    while (!windowShouldClose) {
        switch (scene) {
        case -1:   // Exit
            windowShouldClose = true;
            break;
        case 0:    // Menu
            MM.Init();
            while (MM.Update(&GM) && !windowShouldClose) MM.Draw();
            break;
        case 1:    // Game
            GM.Init();
            while ( GM.Update(&MM) && !windowShouldClose) GM.Draw(&MM);
            break;
        case 2:    // Settings
            MM.InitSettings();
            while (MM.UpdateSettings() && !windowShouldClose) MM.DrawSettings();
            break;
        }
    }

    CloseWindow();

    return 0;
}

/*
Gordon Merrill(Avərəs)
5/10/2023
*/