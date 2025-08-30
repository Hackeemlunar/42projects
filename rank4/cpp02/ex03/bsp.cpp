#include "Point.hpp"

// Helper function to calculate area of triangle
static Fixed area(const Point &a, const Point &b, const Point &c) {
    return Fixed((a.getX().toFloat() * (b.getY().toFloat() - c.getY().toFloat()) +
                  b.getX().toFloat() * (c.getY().toFloat() - a.getY().toFloat()) +
                  c.getX().toFloat() * (a.getY().toFloat() - b.getY().toFloat())) / 2.0f);
}

// Returns true if p is inside triangle abc
bool bsp(Point const a, Point const b, Point const c, Point const p) {
    Fixed A = area(a, b, c);
    Fixed A1 = area(p, b, c);
    Fixed A2 = area(a, p, c);
    Fixed A3 = area(a, b, p);

    return (A1 > Fixed(0) && A2 > Fixed(0) && A3 > Fixed(0) && (A == (A1 + A2 + A3)));
}
