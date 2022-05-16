#include <gtest/gtest.h>
#include "../core/geometry/point/point_3d.hpp"

TEST(tests_point_3d, positive)
{
    int x = 1;
    Point3D<int> point(x, 0, 0);
    int result = point.get_x();
    EXPECT_EQ(x, result);
}
