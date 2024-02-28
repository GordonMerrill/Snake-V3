#pragma once
#include "Main.h"

struct Button {
    Rectangle hitBox;
};

class GameManager;

class MenuManager {
public:
    int selection;
    int coolDown = 0;
    int coolDownAmt = 20;

    int clr;

    Button btn_Easy;
    Button btn_Normal;
    Button btn_Hard;
    Button btn_Settings;
    Button btn_Exit;

    Button btn_Color;
    Button btn_Back;

    void Init();

    bool Update(GameManager* GM);

    void Draw();

    void InitSettings();

    bool UpdateSettings();

    void DrawSettings();

    void UpdateColor(int color);

    void DrawButton(const char* text, Rectangle rect, bool selected);

    Color SNAKE = { 142, 151, 117, 255 };
    Color APPLE = { 226, 143, 131, 255 };
    Color BACKGROUND = { 250, 242, 218, 255 };
    Color FOREGROUND = { 74,  80,  61, 255 };
    Color LIGHT_FOREGROUND = { 94, 100,  81, 255 };
};