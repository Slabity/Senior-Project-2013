#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include "Vector2d.h"

/*The Polygon class is an object consisting of a set of Vector2d
  objects and a position Vector2d.*/

class Polygon {
public:
    /*The constructor itself does not actually create any points.
      A new polygon consists of a zero-length set of Vector2d
      objects and a position of (0.0, 0.0)*/
    Polygon();

    //Accessors to m_Points data.
    void         add(const Vector2d);
    void         remove(const unsigned int);
    void         clear();
    unsigned int size() const;

    //Operators to set the data points.
    Vector2d& operator[](const unsigned int);
    Vector2d  operator[](const unsigned int) const;
    Polygon&  operator=(const Polygon&);
    Polygon   operator+(const Polygon&);

    //Accessor and mutators for m_Position.
    Vector2d getPosition() const;
    void     setPosition(Vector2d);

    //Create new polygons based on their difference.
    static Polygon minkowskiDifference(const Polygon&, const Polygon&);

    //Sort the points clockwise and delete concave points.
    static Polygon grahamScan(const Polygon&);

    //Delete duplicate points.
    static Polygon deleteDuplicates(const Polygon&);

    //Return a polygon sorted in clockwise order.
    static Polygon sort(const Polygon&);

    //Check if polygons are overlapping.
    static bool overlapping(const Polygon&, const Polygon&);
    static bool separatingAxis(const Polygon&, const Polygon&);

    Vector2d castRay(Vector2d, Vector2d);

    void render() const;

private:
    std::vector<Vector2d> m_Points;
    Vector2d m_Position;
};

#endif
