#include <iostream>
#include "../core/geometry/point/point_3d.hpp"

int main()
{
    Point3D<int> point_1(1, 1, 2), point_2(2, 2, 3);
    point_1 += point_2;

    std::cout << point_1.get_x() << std::endl;
    return 0;

}
