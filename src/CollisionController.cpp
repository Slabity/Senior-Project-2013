#include "CollisionController.h"

CollisionController::CollisionController() {}

Polygon CollisionController::getPoly() const
{
    return m_Poly;
}

CollisionController::Rectangle CollisionController::getRectangle() const
{
    return m_Rectangle;
}

CollisionController::CollisionType CollisionController::getCollisionType() const
{
    return m_CollisionType;
}

void CollisionController::setPoly(const Polygon input)
{
    m_Poly = input;

    for(int i = 0; i < m_Poly.size(); i++) {
        Vector2d current = m_Poly[i];

        if(current.x < m_Rectangle.topLeft.x) {
            m_Rectangle.topLeft.x = current.x;
        }
        if(current.x > m_Rectangle.bottomRight.x) {
            m_Rectangle.bottomRight.x = current.x;
        }
        if(current.y < m_Rectangle.topLeft.y) {
            m_Rectangle.topLeft.y = current.y;
        }
        if(current.y > m_Rectangle.bottomRight.y) {
            m_Rectangle.bottomRight.y = current.y;
        }
    }
}

void CollisionController::setCollisionType(const CollisionType input)
{
    m_CollisionType = input;
}
