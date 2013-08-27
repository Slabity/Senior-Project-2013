#ifndef CAMERA_H
#define CAMERA_H

#include "Vector2d.h"

/*The Camera class is created so that all camera 'views' share
  similar attributes when motion is necessary. The class makes
  motion simple by requiring the program to set a 'heading'. The
  camera will travel to the heading automatically at a fluid
  speed. No direct access to the camera's data is necessary.*/

//Change these constants to change the camera's feel.
const double MAX_SPEED = 100.0;
const double DAMPING   = 5.0;

class Camera {
public:
    //The camera must be initialized with an x and y value.
    Camera();
    Camera(Vector2d);

    //Update called each time the scene updates.
    void update();

    /*No more access than mutating the heading and accessing
      the position is necessary.*/
    void setHeading(Vector2d);
    Vector2d getHeading();
    Vector2d getPosition();

private:
    Vector2d m_Position;
    Vector2d m_Velocity;
    Vector2d m_Heading;
};

#endif
