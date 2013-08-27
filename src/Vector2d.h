#ifndef VERTEX_H
#define VERTEX_H


#include <cfloat>
#include <climits>

/*The Vector2d class is an object consisting of simply an x and
  y value. Certain operators are overloaded to make it easier
  for vector math to be performed.*/

class Vector2d {
public:
    /*The x and y values are public to give easier access for
      outside funtions. Accessors and mutators are not really
      necessary*/
    float x;
    float y;

    //Constructor assigns the inputs to x and y.
    Vector2d();
    Vector2d(float, float);

    /*The following operators simply return a vertex with the
      operators working on both x and y.*/
    Vector2d operator+(const Vector2d&) const;
    Vector2d operator-(const Vector2d&) const;
    Vector2d operator*(const Vector2d&) const;
    Vector2d operator/(const Vector2d&) const;

    bool operator==(const Vector2d&) const;
    bool operator>(const Vector2d&) const;
    bool operator<(const Vector2d&) const;
    bool operator>=(const Vector2d&) const;
    bool operator<=(const Vector2d&) const;

    Vector2d operator-() const;
    Vector2d operator*(const float&) const;
    Vector2d operator/(const float&) const;

    //Unsure what these functions do.
    static float DotProduct(const Vector2d&, const Vector2d&);
    static float CrossProduct(const Vector2d&, const Vector2d&);
    static float Magnitude(const Vector2d&);

    //Return the unit vector of the input
    static Vector2d Normal(const Vector2d&);

    //Return a perpendicular vector.
    static Vector2d Perpendicular(const Vector2d&);

    //Return true if two line segments intersect.
    static bool Intersect(const Vector2d&, const Vector2d&, const Vector2d&, const Vector2d&);

    //Return the point where two lines intersect.
    static Vector2d GetIntersect(const Vector2d&, const Vector2d&, const Vector2d&, const Vector2d&);

};

#endif
