#include "Camera.h"
#include "Application.h"

Camera::Camera()
{
    m_Position = Vector2d(0.0, 0.0);
    m_Velocity = Vector2d(0.0, 0.0);
    m_Heading  = Vector2d(0.0, 0.0);
}

Camera::Camera(Vector2d position)
{
    m_Position = position;
    m_Velocity = Vector2d(0.0, 0.0);
    m_Heading  = position;
}

//Update the position of the camera based on the heading.
void Camera::update()
{
    //Create a velocity reasonable to the dampening given.
    m_Velocity.x = (m_Heading.x - m_Position.x) / DAMPING;
    m_Velocity.y = (m_Heading.y - m_Position.y) / DAMPING;

    //Coerce the x velocity.
    if(m_Velocity.x > MAX_SPEED) {
        m_Velocity.x = MAX_SPEED;
    } else if(m_Velocity.x < -MAX_SPEED) {
        m_Velocity.x = -MAX_SPEED;
    }

    //Coerce the y velocity.
    if(m_Velocity.y > MAX_SPEED) {
        m_Velocity.y = MAX_SPEED;
    } else if(m_Velocity.y < -MAX_SPEED) {
        m_Velocity.y = -MAX_SPEED;
    }

    //Add the velocity to the position.
    m_Position = m_Position + m_Velocity;
}

void Camera::setHeading(Vector2d heading)
{
    m_Heading = heading;
}

Vector2d Camera::getHeading()
{
        return m_Heading;
}

Vector2d Camera::getPosition()
{
    return m_Position;
}
