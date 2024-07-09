#pragma once
#include <raylib.h>

typedef float Degree;

class Entity {
public:
    virtual float GetX();
    virtual float GetY();
    virtual int GetVelocity();
    virtual void IncrementX(float x, void *gamestate);
    virtual void IncrementY(float y, void *gamestate);

protected:
    int e_velocity;
    Vector2 position;
};

class Paddle : public Entity {
public:
    enum Side { left, right };
    Paddle(Side side, int speed, bool isbot);
    Side side;
    int score;
    float GetWidth();
    float GetHeight();
    void SetWidth(float new_width);
    void SetHeight(float new_heigth);

private:
    bool is_bot;
    float width, height;

};
class Ball : public Entity {
public:
    Ball(int speed, float ball_radius);
    float radius;
    void SetAngle(float new_angle);
    void ResetPosition(int side);
    Vector2 GetNextPosition();
    Degree GetAngle();
    void CheckCollision(Paddle* player);

private:
    Degree angle;
};
class Tile;
class Score;