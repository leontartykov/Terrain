#ifndef _TERRAIN_HPP_
#define _TERRAIN_HPP_

#include "terrain.h"

template <typename T1, typename T2>
Vector3D<T1> Terrain::find_int_normal(Point3D<T2> point_1, Point3D<T2> point_2, Point3D<T2> point_3)
{
    Vector3D<T2> normal = find_normal(point_1, point_2, point_3);
    Vector3D<T1> int_normal;
    int_normal.set_vector(normal.get_x(), normal.get_y(), normal.get_z());

    return int_normal;
}

#endif
