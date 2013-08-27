#ifndef COLLISIONCONTROLLER_H
#define COLLISIONCONTROLLER_H

#include <vector>
#include "Vector2d.h"
#include "Polygon.h"

class CollisionController {
public:
    /*Enum used to decide what kind of collision
      the object creates.*/
    typedef enum {
        CLIP,
        DAMAGE,
        PLAYER,
        BOUNCE
    } CollisionType;

    /*Struct used to hold information for broad
      phase collision.*/
    typedef struct {
        Vector2d topLeft;
        Vector2d bottomRight;
    } Rectangle;

    CollisionController();

    //Accessors
    Polygon getPoly() const;
    Rectangle getRectangle() const;
    CollisionType getCollisionType() const;

    //Mutators
    void setPoly(const Polygon);
    void setCollisionType(const CollisionType);

private:
    Polygon m_Poly;
    Rectangle m_Rectangle;
    CollisionType m_CollisionType;
};

#endif
