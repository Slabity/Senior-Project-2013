#include "Polygon.h"
#include <SDL/SDL_opengl.h>
#include <cstdio>
#include <cfloat>
#include <climits>
#include <cmath>

//CONSTRUCTOR:
Polygon::Polygon()
{
    m_Position = Vector2d(0.0, 0.0);
}


//ADD, REMOVE, AND CLEAR POINTS:
void Polygon::add(const Vector2d newPoint)
{
    //Create a new point in the set.
    m_Points.push_back(newPoint);
}

void Polygon::remove(unsigned int index)
{
    //Erase the point at the given index.
    m_Points.erase(m_Points.begin() + (index % size()));
}

void Polygon::clear()
{
    //Delete all points in the polygon.
    m_Points.clear();
}

unsigned int Polygon::size() const
{
    return m_Points.size();
}


//OPERATORS
Vector2d& Polygon::operator[](const unsigned int index)
{
    //Return the modulus of the index within the number of points.
    return m_Points[index % size()];
}

Vector2d Polygon::operator[](const unsigned int index) const
{
    return m_Points[index % size()];
}

Polygon& Polygon::operator=(const Polygon &b)
{
    //Set the position.
    m_Position = b.getPosition();

    //Clear our polygon and set the new points.
    clear();
    for(int i = 0; i < b.size(); i++) {
        add(b[i]);
    }
}

Polygon Polygon::operator+(const Polygon &b)
{
    Polygon returnPoly;
    returnPoly = *this;

    for(int i = 0; i < b.size(); i++) {
        returnPoly.add(b[i] + b.getPosition());
    }

    return returnPoly;
}

//Position accessor and mutator:
Vector2d Polygon::getPosition() const
{
    return m_Position;
}

void Polygon::setPosition(Vector2d position)
{
    m_Position = position;
}



Vector2d Polygon::castRay(Vector2d rayStart, Vector2d rayEnd)
{
    //Store the index of the closest intersecting line and its distance.
    int closestLine = INT_MAX;
    Vector2d closestIntersect = Vector2d(FLT_MAX, FLT_MAX);

    //Use to offset everything by using rayStart as the origin.
    Vector2d offset = rayStart;
    rayStart = Vector2d(0.0, 0.0);
    rayEnd = rayEnd - offset;

    //Find the closest intersecting line.
    for(int i = 0; i < size(); i++) {

        //Store the line with the offset.
        Vector2d lineStart = (*this)[i] - offset;
        Vector2d lineEnd   = (*this)[i+1] - offset;

        //Skip if there is no intersect.
        if(!Vector2d::Intersect(rayStart, rayEnd, lineStart, lineEnd)) {
            continue;
        }

        //Set line as closest intersect if we have no previous intersect.
        if(closestLine == INT_MAX) {
            closestLine = i;
            closestIntersect = Vector2d::GetIntersect(rayStart, rayEnd, lineStart, lineEnd);
            continue;
        }

        Vector2d currentIntersect = Vector2d::GetIntersect(rayStart, rayEnd, lineStart, lineEnd);

        //Set the closest intersect if the current distance is closer.
        if(currentIntersect < closestIntersect) {
            closestLine = i;
            closestIntersect = currentIntersect;
        }
    }

    return closestIntersect;
}


Polygon Polygon::minkowskiDifference(const Polygon &a, const Polygon &b)
{
    //Subtract each point of polygon a from polygon b.
    Polygon returnPoly;
    for(int i = 0; i < a.size(); i++) {
        for(int j = 0; j< b.size(); j++) {
           returnPoly.add((a[i]+a.getPosition()) - (b[j]+b.getPosition()));
        }
    }
    return returnPoly;
}

Polygon Polygon::grahamScan(const Polygon &inputPoly)
{
    Polygon sortedPoly = Polygon::sort(inputPoly);

    //Delete vertices that create concave angles.
    for(int i = 1; i < sortedPoly.size(); i++) {
        Vector2d p1 = sortedPoly[i-1];
        Vector2d p2 = sortedPoly[i];
        Vector2d p3 = sortedPoly[i+1];
        float direction = (p2.x - p1.x) *
                          (p3.y - p1.y) -
                          (p2.y - p1.y) *
                          (p3.x - p1.x);

        if(direction <= 0) {
            sortedPoly.remove(i);
            i = 1;
        }
    }
    return sortedPoly;
}

Polygon Polygon::deleteDuplicates(const Polygon &inputPoly)
{
    Polygon returnPoly = inputPoly;

    //Delete duplicate points.
    for(int i = 0; i < returnPoly.size(); i++) {
        for(int j = 0; j < returnPoly.size(); j++) {
            if(j == i) {
                continue;
            }

            if(returnPoly[i] == returnPoly[j]) {
                returnPoly.remove(j);
            }
        }
    }

    return returnPoly;
}

Polygon Polygon::sort(const Polygon &inputPoly)
{
    Polygon sortedPoly = Polygon::deleteDuplicates(inputPoly);
        
    //Get the upper most point.
    Vector2d upperPoint = Vector2d(FLT_MAX, FLT_MAX);
    for(int i = 0; i < sortedPoly.size(); i++) {
        Vector2d currentPoint = sortedPoly[i];
        if(currentPoint.y > upperPoint.y) {
            continue;
        }
        if(currentPoint.y < upperPoint.y) {
            upperPoint = currentPoint;
            continue;
        }
        if(currentPoint.x < upperPoint.x) {
            upperPoint = currentPoint;
        }
    }

    //Create an array of angles per three vertices.
    float angles[sortedPoly.size()];
    for(int i = 0; i < sortedPoly.size(); i++) {
        if(sortedPoly[i] == upperPoint) {
            angles[i] = 0;
            continue;
        }
        Vector2d offsetVector = sortedPoly[i] - upperPoint;
        angles[i] = atan2(offsetVector.y, offsetVector.x);
        angles[i] += 3.14159;
    }

    //Sort the angles and vectors.
    for(int i = 0; i < sortedPoly.size(); i++) {
        for(int j = i; j < sortedPoly.size(); j++) {
            if(angles[j] <= angles[i]) {

                //If both angles are the same, skip if first is closer.
                if(angles[j] == angles[i]) {
                    Vector2d p1 = sortedPoly[i] - sortedPoly[0];
                    Vector2d p2 = sortedPoly[j] - sortedPoly[0];
                    if(p1 < p2) {
                        continue;
                    }
                }

                float tempAngle = angles[i];
                angles[i] = angles[j];
                angles[j] = tempAngle;

                Vector2d tempVect = sortedPoly[i];
                sortedPoly[i] = sortedPoly[j];
                sortedPoly[j] = tempVect;
            }
        }
    }

    return sortedPoly;
}

bool Polygon::overlapping(const Polygon &polyOne, const Polygon &polyTwo)
{
    return Polygon::separatingAxis(polyOne, polyTwo) &&
           Polygon::separatingAxis(polyTwo, polyOne);
}

bool Polygon::separatingAxis(const Polygon &polyOne, const Polygon &polyTwo)
{
    //Go through each side of the first polygon.
    for(int i = 0; i < polyOne.size(); i++) {

        Vector2d offset = polyOne[i];

        //Create the vector we must project onto.
        Vector2d projVect = Vector2d::Perpendicular(polyOne[i+1] - offset);

        //Store a bool if the current point is behind the projVect.
        bool behind = false;

        //Go through each point of the second polygon.
        for(int j = 0; j < polyTwo.size(); j++) {

            //Project the current point.
            float projection = Vector2d::DotProduct(projVect, (polyTwo[j]+polyTwo.getPosition()) -
                                                                 (polyOne[i]+polyOne.getPosition()));

            //If any point is behind the line, we can skip this entire side.
            if(projection <= 0) {
                behind = true;
                break;
            }
        }

        if(behind == false) {
            return false;
        }
    }

    return true;
}


//RENDER
void Polygon::render() const
{
    glBegin(GL_LINES);
        //Go through each point
        for(int i = 0; i < size(); i++) {
            //Select the starting and ending point of each line.
            Vector2d startPoint = (*this)[i] + m_Position;
            Vector2d endPoint = (*this)[i + 1] + m_Position;

            //Draw each line.
            glVertex3f(startPoint.x, startPoint.y, 0.0f);
            glVertex3f(endPoint.x, endPoint.y, 0.0f);
        }
    glEnd();
}

