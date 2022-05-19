

#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include <array>
#include <vector>

#include "driver/geometry/point/point.h"
#include "../point/point_3d.h"

template <typename T>
class Triangle
{
private:
    std::array<Point3D<T>, 3> _triangle;
public:
    Triangle();
    Triangle(Point3D<T> point_1, Point3D<T> point_2, Point3D<T> point_3);
    ~Triangle();

    void set_triangle(Point3D<T> point_1, Point3D<T> point_2, Point3D<T> point_3);
    void swap_points(int index_first, int index_second);

    Point3D<T> operator[] (int index);

    void output();
};

#endif
