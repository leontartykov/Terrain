#ifndef _TERRAIN_H_
#define _TERRAIN_H_

#include <vector>
#include "base_terrain.h"
#include "../../geometry/point/point_3d.h"
#include "../../geometry/vector/vector_3d.h"
#include "../../invisible/zbuffer/zbuffer.h"
#include "../../heightmap/perlin_noise/perlin_original.h"
#include "../../geometry/triangle/triangle_3d.h"

class Terrain
{
    private:
        std::vector<std::vector<Point3D<double>>> _start_points, _points, _screen_points;
        std::vector<std::vector<Vector3D<int>>> _normals_up_triangles, _normals_down_triangles;
        std::vector<std::vector<Vector3D<double>>> _shading_normals;

        const int _default_width = 100, _default_height = 100;
        int _width, _height;
        double _scale;
        Point3D<double> _center_terrain_point;
        meta_data_t _meta_config;

        void init_terrain(int width, int height);

        template <typename T1, typename T2>
        Vector3D<T1> find_int_normal(Point3D<T2> point_1, Point3D<T2> point_2, Point3D<T2> point_3);

        Vector3D<double> find_shading_normals(std::vector<Vector3D<int>> &normals, int i, int j);
    public:
        Terrain();
        Terrain(int width, int height);
        ~Terrain();

        Point3D<double> get_point(int index_i, int index_j);
        Point3D<double> get_screen_point(int index_i, int index_j);

        int get_height();
        int get_width();

        Point3D<double> get_center_figure();
        void set_center_figure(Point3D<double> &point);

        void remove_invisible_lines(ZBuffer &zbuffer, Vector3D<int> light_position);
        void find_all_normals();
        void find_average_normals_of_each_node();
        void clear_normals();
};

#endif
