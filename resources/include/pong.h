#pragma once
#include <raylib.h>

class Entity {
public:
    virtual float GetX();
    virtual float GetY();
    virtual void SetX(float value);
    virtual void SetY(float value);

protected:
    int e_speed;
    float xpos, ypos;
};

class Paddle : public Entity {
public:
    enum { left_side, right_side };
    Paddle(int side, int speed, bool isbot);
    float GetWidth();
    float GetHeight();
    void SetWidth(float value);
    void SetHeight(float value);
    int GetSpeed();
    Rectangle GetRekt();

private:
    float width, height;
    bool is_bot;
    int side, score;

};
class Ball;
class Tile;
class Score;