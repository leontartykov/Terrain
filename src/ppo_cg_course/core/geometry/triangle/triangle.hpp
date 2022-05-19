#ifndef _TRIANGLE_HPP_
#define _TRIANGLE_HPP_

#include "triangle.h"

template <typename T>
Triangle<T>::Triangle()
{
    _triangle[0] = Point3D<T>(0.0, 0.0, 0.0);
    _triangle[1] = Point3D<T>(0.0, 0.0, 0.0);
    _triangle[2] = Point3D<T>(0.0, 0.0, 0.0);
}

template <typename T>
Triangle<T>::Triangle(Point3D<T> point_1, Point3D<T> point_2, Point3D<T> point_3)
{
    _triangle[0] = point_1;
    _triangle[1] = point_2;
    _triangle[2] = point_3;
}

template <typename T>
Triangle<T>::~Triangle(){

}

template <typename T>
void Triangle<T>::output(){
    std::cout << "[";
    _triangle[0].output();
    _triangle[1].output();
    _triangle[2].output();
    std::cout << "]" << std::endl;
}

template <typename T>
void Triangle<T>::set_triangle(Point3D<T> point_1, Point3D<T> point_2, Point3D<T> point_3)
{
    _triangle[0] = point_1;
    _triangle[1] = point_2;
    _triangle[2] = point_3;
}

template <typename T>
void Triangle<T>::swap_points(int index_first, int index_second)
{
    Point3D<T> temp_point;
    temp_point = _triangle[index_first - 1];
    _triangle[index_first - 1] = _triangle[index_second - 1];
    _triangle[index_second - 1] = temp_point;
    //temp_point = (*this).get_point(index_first);
}

template <typename T>
Point3D<T> Triangle<T>::operator[] (int index){
    return _triangle[index];
}

#endif
