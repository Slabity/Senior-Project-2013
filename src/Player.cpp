#include "Player.h"
#include "Application.h"

Player::Player(Vector2d position, std::vector<Polygon*> *platforms)
{
    m_Position = position;
    m_Velocity = Vector2d(0.0, 0.0);
    m_Acceleration = Vector2d(0.0, FALLING_ACCEL);

    m_Polygon.add(Vector2d(0.0, -63.0));
    m_Polygon.add(Vector2d(25.0, 0.0));
    m_Polygon.add(Vector2d(0.0, 64.0));
    m_Polygon.add(Vector2d(-25.0, 0.0));

    m_Platforms = platforms;
}

Player::~Player() {}

void Player::control()
{
    if(Application::s_Keyboard[SDLK_d]) {
        m_Acceleration.x = WALKING_ACCEL;
    } else if(Application::s_Keyboard[SDLK_a]) {
        m_Acceleration.x = -WALKING_ACCEL;
    } else if(Application::s_Joystick != NULL) {

        int axis = SDL_JoystickGetAxis(Application::s_Joystick, 0);
        if(axis > 1 || axis < -1) {
            m_Acceleration.x = WALKING_ACCEL * (axis / 32768.0);
        } else {
            m_Acceleration.x = -m_Velocity.x / 5.0;
        }
    } else {
        m_Acceleration.x = -m_Velocity.x / 5.0;
    }

    if((Application::s_Keyboard[SDLK_SPACE] || SDL_JoystickGetButton(Application::s_Joystick, 1)) &&
        grounded) {
        m_Velocity.y = JUMPING_SPEED;
    }
}

void Player::update()
{
    grounded = false;

    //Set the player's vectors.
    setVelocity(m_Velocity + m_Acceleration);

    if(m_Velocity.y > MAX_FALLING_SPEED) {
        m_Velocity.y = MAX_FALLING_SPEED;
    }

    if(m_Velocity.x > MAX_WALKING_SPEED) {
        m_Velocity.x = MAX_WALKING_SPEED;
    } else if(m_Velocity.x < -MAX_WALKING_SPEED) {
        m_Velocity.x = -MAX_WALKING_SPEED;
    }

    std::vector<int> collided;

    setPosition(m_Position + m_Velocity);
    for(int i = 0; i < m_Platforms->size(); i++) {
        Polygon platform = *m_Platforms->at(i);

        if(verticalCollision(platform)) {
            collided.push_back(i);
        }
    }

    for(int i = 0; i < m_Platforms->size(); i++) {
        bool skip = false;

        for(int j = 0; j < collided.size(); j++) {
            if(i == collided[j]) {
                skip = true;
            }
        }

        if(!skip) {
            Polygon platform = *m_Platforms->at(i);
            horizontalCollision(platform);
        }
    }
}

void Player::render()
{
    m_Polygon.render();
}

bool Player::verticalCollision(const Polygon &platform)
{
    Polygon vertical;
    vertical.add(m_Polygon[0]);
    vertical.add(m_Polygon[2]);
    vertical.setPosition(getPosition());

    if(!Polygon::overlapping(vertical, platform)) {
        return false;
    }
 
    Polygon minkowski = Polygon::minkowskiDifference(vertical, platform);
    minkowski = Polygon::grahamScan(minkowski);
    minkowski.render();

    Vector2d up    = minkowski.castRay(Vector2d(0.0, 0.0), Vector2d(0.0, 100000.0));
    Vector2d down  = minkowski.castRay(Vector2d(0.0, 0.0), Vector2d(0.0, -100000.0));
    
    Vector2d correction;

    if(up < down) {
        correction = up;
        enableGrounded();
    } else {
        correction = down;
    }

    m_Velocity.y = 0.0;
    setPosition(m_Position - correction);
    return true;
}

bool Player::horizontalCollision(const Polygon &platform)
{
    if(!Polygon::overlapping(m_Polygon, platform)) {
        return false;
    }

    Polygon minkowski = Polygon::minkowskiDifference(m_Polygon, platform);
    minkowski = Polygon::grahamScan(minkowski);

    Vector2d left   = minkowski.castRay(Vector2d(0.0, 0.0), Vector2d(100000.0, 0.0));
    Vector2d right  = minkowski.castRay(Vector2d(0.0, 0.0), Vector2d(-100000.0, 0.0));

    Vector2d correction;

    if(left < right) {
        correction = left;
    } else {
        correction = right;
    }

    m_Velocity.x = 0.0;
    setPosition(m_Position - correction);
    return true;
}


void Player::setPosition(const Vector2d position) { m_Position = position;
                                                    m_Polygon.setPosition(position); }
void Player::setVelocity(const Vector2d velocity) { m_Velocity = velocity; }
void Player::setAcceleration(const Vector2d acceleration) { m_Acceleration = acceleration; }

Vector2d Player::getPosition() const { return m_Position; }
Vector2d Player::getVelocity() const { return m_Velocity; }
Vector2d Player::getAcceleration() const { return m_Acceleration; }

void Player::enableGrounded()
{
    grounded = true;
    groundedLatch = true;
}
