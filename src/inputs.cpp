#include <iostream>
#include "headers.h"

#ifdef CLASSES_H

void Scene::Update(Paddle& p1, Paddle& p2, Ball& ball, Gamestate& gamestate) {
    { // game input
        // Workarround to "fix" dragging window problem (to prevent the paddle from going offscreen if you do an input while dragging the window)
        if(p1.y <= 0) {
        p1.y = 1;
        }else if(p2.y <= 0) {
            p2.y = 1;
        }

        if(p1.y + p1.height >= WINDOW_HEIGHT) {
            p1.y = WINDOW_HEIGHT - p1.height - 1;
        }else if(p2.y + p2.height >= WINDOW_HEIGHT) {
            p2.y = WINDOW_HEIGHT - p1.height - 1;
        }

        // Game input logic
        if((IsKeyDown(KEY_W) && !IsKeyDown(KEY_S)) && p1.y > 0) 
            p1.y -= p1.speed * GetFrameTime();
        if((IsKeyDown(KEY_S) && !IsKeyDown(KEY_W)) && p1.y + p1.height < WINDOW_HEIGHT) 
            p1.y += p1.speed * GetFrameTime();

        if((IsKeyDown(KEY_UP) && !IsKeyDown(KEY_DOWN)) && p2.y > 0) 
            p2.y -= p2.speed * GetFrameTime();
        if((IsKeyDown(KEY_DOWN) && !IsKeyDown(KEY_UP)) && p2.y + p2.height < WINDOW_HEIGHT) 
            p2.y += p2.speed * GetFrameTime();
    }
    
}

#endif