#ifndef PLAYER_H
#define PLAYER_H

#include "Vector2d.h"
#include "Polygon.h"
#include "CollisionController.h"
#include <vector>

const float WALKING_ACCEL = 0.5;
const float MAX_WALKING_SPEED = 11.0;
const float FALLING_ACCEL = 1.2;
const float MAX_FALLING_SPEED = 20.0;
const float JUMPING_SPEED = -25.0;

class Player {
public:
    Player(Vector2d, std::vector<Polygon*>*);
    ~Player();

    void control();
    void update();
    void render();

    bool verticalCollision(const Polygon&);
    bool horizontalCollision(const Polygon&);

    void setPosition(const Vector2d);
    void setVelocity(const Vector2d);
    void setAcceleration(const Vector2d);

    Vector2d getPosition() const;
    Vector2d getVelocity() const;
    Vector2d getAcceleration() const;

private:

    bool grounded;
    bool groundedLatch;
    bool jumping;

    //Position and derivatives for movement.
    Vector2d m_Position;
    Vector2d m_Velocity;
    Vector2d m_Acceleration;

    //Polygon for rendering.
    Polygon m_Polygon;

    std::vector<Polygon*> *m_Platforms;

    void enableGrounded();
};

#endif
