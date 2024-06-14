#pragma once
#include <iostream>
#include <tuple>

#include <raylib.h>

#include "pong.h"

class Scene {
public:
    enum class Gamestate {mainmenu, pausemenu, pong};
    enum class Gamemode {pvp, pve};
    Gamestate gamestate;
    Gamemode gamemode;
    struct Menu;

    Scene(float &wwidth, float &wheight);
    ~Scene();

    void InitGame();
    void Logic();
    void HandleInput();
    void Draw();

    static void SetWindowWidth(float &width);
    static void SetWindowHeight(float &height);
    static float GetWindowWidth();
    static float GetWindowHeight();

    Paddle *p1;
    Paddle *p2;

private:
    inline static float *window_width = nullptr, *window_height = nullptr;
    Menu *menu_instance;
    
};