#ifndef HEADERS_H
#define HEADERS_H

#ifndef CLASSES_H
#define CLASSES_H
class Entity;
class Paddle;
class Ball;

#endif

namespace Scene {
    enum Gamestate;
    struct Menu;
    void Draw(Paddle&, Paddle&, Ball&, Gamestate&);
    void Logic(Paddle&, Paddle&, Ball&, Gamestate&);
    void Update(Paddle&, Paddle&, Ball&, Gamestate&);
}

#endif