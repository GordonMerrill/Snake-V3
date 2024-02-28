#include "MenuManager.h"
#include "GameManager.h"

void MenuManager::Init() {
    selection = 0;
    clr = 0;

    screenWidth = 160;
    screenHeight = 280;
    SetWindowSize(screenWidth, screenHeight);

    SetWindowPosition(GetMonitorWidth(GetCurrentMonitor()) * .5 - screenWidth * .5, GetMonitorHeight(GetCurrentMonitor()) * .5 - screenHeight * .5);

    int xOffset = 20;
    int yOffset = 60;

    btn_Easy.hitBox.x = xOffset;
    btn_Easy.hitBox.y = 10 + yOffset;
    btn_Easy.hitBox.width = 120;
    btn_Easy.hitBox.height = 30;

    btn_Normal.hitBox.x = xOffset;
    btn_Normal.hitBox.y = 50 + yOffset;
    btn_Normal.hitBox.width = 120;
    btn_Normal.hitBox.height = 30;

    btn_Hard.hitBox.x = xOffset;
    btn_Hard.hitBox.y = 90 + yOffset;
    btn_Hard.hitBox.width = 120;
    btn_Hard.hitBox.height = 30;

    btn_Settings.hitBox.x = xOffset;
    btn_Settings.hitBox.y = 130 + yOffset;
    btn_Settings.hitBox.width = 120;
    btn_Settings.hitBox.height = 30;

    btn_Exit.hitBox.x = xOffset;
    btn_Exit.hitBox.y = 170 + yOffset;
    btn_Exit.hitBox.width = 120;
    btn_Exit.hitBox.height = 30;
}

bool MenuManager::Update(GameManager* GM) {
    windowShouldClose = WindowShouldClose();

    if (coolDown == 0) {
        if (IsKeyDown(KEY_W) && selection > 0) {
            selection--;
            coolDown = coolDownAmt;
        }
        else if (IsKeyDown(KEY_S) && selection < 4) {
            selection++;
            coolDown = coolDownAmt;
        }
    }

    if (IsKeyDown(KEY_SPACE) && coolDown == 0) {
        switch (selection) {
        case 0: // Easy
            GM->speed = 20;
            scene = 1;
            return false;
        case 1: // Normal
            GM->speed = 10;
            scene = 1;
            return false;
        case 2: // Hard
            GM->speed = 5;
            scene = 1;
            return false;
        case 3: // Settings
            scene = 2;
            coolDown = coolDownAmt;
            return false;
        case 4: // Exit
            scene = -1;
            return false;
        }
    }

    if (coolDown != 0) coolDown--;
    return true;
}

void MenuManager::Draw() {
    BeginDrawing();

    ClearBackground(BACKGROUND);

    DrawText("Snake", 20, 20, 40, FOREGROUND);

    DrawButton("Easy", btn_Easy.hitBox, selection == 0);
    DrawButton("Normal", btn_Normal.hitBox, selection == 1);
    DrawButton("Hard", btn_Hard.hitBox, selection == 2);
    DrawButton("Settings", btn_Settings.hitBox, selection == 3);
    DrawButton("Exit", btn_Exit.hitBox, selection == 4);

    EndDrawing();
}


void MenuManager::InitSettings() {
    selection = 0;

    screenWidth = 90;
    screenHeight = 90;
    SetWindowSize(screenWidth, screenHeight);

    SetWindowPosition(GetMonitorWidth(GetCurrentMonitor()) * .5 - screenWidth * .5, GetMonitorHeight(GetCurrentMonitor()) * .5 - screenHeight * .5);

    btn_Color.hitBox.x = 10;
    btn_Color.hitBox.y = 10;
    btn_Color.hitBox.width = 70;
    btn_Color.hitBox.height = 30;

    btn_Back.hitBox.x = 10;
    btn_Back.hitBox.y = 50;
    btn_Back.hitBox.width = 70;
    btn_Back.hitBox.height = 30;
}

bool MenuManager::UpdateSettings() {
    windowShouldClose = WindowShouldClose();

    if (coolDown == 0) {
        if (IsKeyDown(KEY_W) && selection > 0) {
            selection--;
            coolDown = coolDownAmt;
        }
        else if (IsKeyDown(KEY_S) && selection < 1) {
            selection++;
            coolDown = coolDownAmt;
        }
    }

    switch (selection) {
    case 0: // Color
        if (IsKeyDown(KEY_D) && coolDown == 0) {
            clr++;
            if (clr == 4) clr = 0;
            UpdateColor(clr);
            coolDown = coolDownAmt;
        }
        else if (IsKeyDown(KEY_A) && coolDown == 0) {
            clr--;
            if (clr == -1) clr = 3;
            UpdateColor(clr);
            coolDown = coolDownAmt;
        }
        break;
    case 1: // Back
        if (IsKeyDown(KEY_SPACE)) {
            scene = 0;
            coolDown = coolDownAmt;
            selection = 0;
            return false;
        }
        break;
    }

    if (coolDown != 0) coolDown--;

    return true;
}

void MenuManager::DrawSettings() {
    BeginDrawing();

    ClearBackground(BACKGROUND);

    DrawButton("Color", btn_Color.hitBox, selection == 0);
    DrawButton("Back", btn_Back.hitBox, selection == 1);

    EndDrawing();
}


void MenuManager::UpdateColor(int color) {
    switch (color) {
    case 0:
        SNAKE = { 142, 151, 117, 255 };
        APPLE = { 226, 143, 131, 255 };
        BACKGROUND = { 250, 242, 218, 255 };
        FOREGROUND = { 74,  80,  61, 255 };
        LIGHT_FOREGROUND = { 94, 100,  81, 255 };
        break;
    case 1:
        SNAKE = { 92,  70, 156, 255 };
        APPLE = { 212, 173, 252, 255 };
        BACKGROUND = { 12,  19,  79, 255 };
        FOREGROUND = { 29,  38, 125, 255 };
        LIGHT_FOREGROUND = { 39,  48, 135, 255 };
        break;
    case 2:
        SNAKE = { 149,   0,   0, 255 };
        APPLE = { 255,   0,   0, 255 };
        BACKGROUND = BLACK;
        FOREGROUND = { 61,   0,   0, 255 };
        LIGHT_FOREGROUND = { 71,   0,   0, 255 };
        break;
    case 3:
        SNAKE = { 147, 198, 231, 255 };
        APPLE = { 255,  77,   0, 255 };
        BACKGROUND = { 39,  33,  33, 255 };
        FOREGROUND = { 68,  55,  55, 255 };
        LIGHT_FOREGROUND = { 78,  65,  65, 255 };
        break;

    }
}

void MenuManager::DrawButton(const char* text, Rectangle rect, bool selected) {
    Rectangle buttonOne;
    buttonOne.width = rect.width;
    buttonOne.height = rect.height;
    buttonOne.x = rect.x;
    buttonOne.y = rect.y;

    DrawRectangleRec(buttonOne, LIGHT_FOREGROUND);

    Rectangle tempButton = buttonOne;
    tempButton.x += 2;
    tempButton.y += 2;
    tempButton.width -= 4;
    tempButton.height -= 4;

    DrawRectangleRec(tempButton, FOREGROUND);

    if (selected) DrawText(text, buttonOne.x + buttonOne.width * .5 - MeasureText(text, 20) * .5, buttonOne.y + 5, 20, APPLE);
    else DrawText(text, buttonOne.x + buttonOne.width * .5 - MeasureText(text, 20) * .5, buttonOne.y + 5, 20, SNAKE);
}