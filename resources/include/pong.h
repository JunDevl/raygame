#pragma once
#include <raylib.h>

class Entity {
public:
    virtual float GetX();
    virtual float GetY();
    virtual int GetSpeed();
    virtual void SetX(float x);
    virtual void SetY(float y);

protected:
    int e_speed;
    float xpos, ypos;
};

class Paddle : public Entity {
public:
    enum Side { left, right };
    Paddle(Side side, int speed, bool isbot);
    float GetWidth();
    float GetHeight();
    void SetWidth(float new_width);
    void SetHeight(float new_heigth);
    Rectangle GetRekt();

private:
    float width, height;
    bool is_bot;
    Side side;
    int score;

};
class Ball : public Entity {
public:
    float GetAngle();
    void SetAngle(float new_angle);

private:
    float angle;
};
class Tile;
class Score;