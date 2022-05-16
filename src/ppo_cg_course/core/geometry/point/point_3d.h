#ifndef _POINT_3D_H_
#define _POINT_3D_H_

template <typename T>
class Point3D
{
private:
    T _x;
    T _y;
    T _z;

public:
    Point3D();
    Point3D(T x, T y, T z) noexcept;
    ~Point3D();

    void set_point(const T data_x, const T data_y, const T data_z);
    T get_x() const;
    T get_y() const;
    T get_z() const;

    void set_x(T x);
    void set_y(T y);
    void set_z(T z);
    Point3D<T> &operator *= (double scale);
    Point3D<T> &operator += (double scale);
    Point3D<T> &operator -= (double scale);

    void output_point();
};

#endif
