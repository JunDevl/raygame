#pragma once
#include <iostream>
#include <vector>

#include <raylib.h>

#include "pong.h"

class Scene {
public:
    enum class Gamestate {mainmenu, pausemenu, ponggame};
    enum class Gamemode {pvp, pve}; // to-do: Create AI for PVE
    Gamestate gamestate;
    Gamemode gamemode;
    struct Menu;

    Scene(float &wwidth, float &wheight);
    ~Scene();

    bool in_game = false;

    void InitGame();
    void Logic();
    void HandleInput();
    void Draw();

    static void SetWindowWidth(float *width);
    static void SetWindowHeight(float *height);
    static float GetWindowWidth();
    static float GetWindowHeight();

    // std::vector<Entity*> entities; to-do: initialize all entities to a vector so you don't need to declare every entity of this class

    Entity *p1 = nullptr, *p2 = nullptr, *p3 = nullptr, *p4 = nullptr, *ball = nullptr;

private:
    inline static float *window_width = nullptr, *window_height = nullptr;
    Menu *menu_instance;

};