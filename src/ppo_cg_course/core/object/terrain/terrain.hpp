#ifndef _TERRAIN_HPP_
#define _TERRAIN_HPP_

#include "terrain.h"
#include "../../invisible/zbuffer/zbuffer.hpp"
#include "../../geometry/triangle/triangle_3d.hpp"
#include "../../geometry/vector/vector_3d.h"

/*!
 * \brief Terrain::Terrain
 * the terrain landscape size is a number of triangles in rows and columns
 */
Terrain::Terrain()
{
    _width = _default_height + 1, _height = _default_width + 1;
    this->init_terrain(_width, _height);
}

Terrain::Terrain(int width, int height)
{
    _width = height + 1, _height = width + 1;
    this->init_terrain(_width, _height);
}

void Terrain::init_terrain(int width, int height)
{
    std::vector<Point3D<double>> temp;

    for (int i = 0; i < _width; i++){
        for (int j = 0; j < _height; j++){
            temp.push_back(Point3D<double>(0, 0, 0));
        }
        _points.push_back(temp);
        _start_points.push_back(temp);
        _screen_points.push_back(temp);
        temp.clear();
    }

    _meta_config.gain = 0, _meta_config.lacunarity = 0, _meta_config.octaves = 0;
    _meta_config.frequency = 0, _meta_config.seed = 0;
}

Terrain::~Terrain()
{
    for (int i = 0; i < _width; i++){
        for (int j = 0; j < _height; j++){
            _points[i].clear();
            _start_points.clear();
            _screen_points.clear();
        }
    }

    _points.clear();
    _start_points.clear();
    _screen_points.clear();
}

Point3D<double> Terrain::get_point(int index_i, int index_j){
    return _points[index_i][index_j];
}

Point3D<double> Terrain::get_screen_point(int index_i, int index_j){
    return _screen_points[index_i][index_j];
}

int Terrain::get_height(){
    return _height;
}

int Terrain::get_width(){
    return _width;
}

Point3D<double> Terrain::get_center_figure(){
    return _center_terrain_point;
}

void Terrain::set_center_figure(Point3D<double> &point){
    _center_terrain_point.set_point(point.get_x(), point.get_y(), point.get_z());
}

/*!
 * \brief Terrain::remove_invisible_lines
 * \param zbuffer
 * \param light_position
 */
void Terrain::remove_invisible_lines(ZBuffer &zbuffer, Vector3D<int> light_position)
{
    plane_coeffs_t plane_coeffs_top, plane_coeffs_bottom;

    //все точки экранных треугольников (верхние, нижние)
    //берем матрицу для того, чтобы поделить на верхнюю часть треугольника
    //и нижнюю
    std::vector<std::vector<rasterised_points_t>> rasterized_points_up, rasterized_points_down;

    //нормали для треугольников (верхние, нижние)
    Vector3D<double> normal_top, normal_down;

    //нормали вершин для каждого треугольника (верхние, нижние)
    Triangle3D<double>top_triangle_normals, bottom_triangle_normals;

    //вершины треугольников (верхний и нижний) в 3д
    Triangle3D<double>triangle_top_3d, triangle_bottom_3d;

    Point3D<int> top_middle_point, bottom_middle_point;
    std::vector<std::vector<QColor>> color_matrix = zbuffer.get_color_matrix();
    std::vector<std::vector<double>> zbuffer_matrix = zbuffer.get_zbuffer_matrix();
    Triangle3D<double> triangle_top, triangle_bottom;

    for (int i = 0; i < _width - 1; i++){
        for (int j = 0; j < _height - 1; j++)
        {
            plane_coeffs_top = find_equation_plane(_points[i][j], _points[i][j+1], _points[i + 1][j + 1]);
            plane_coeffs_bottom = find_equation_plane(_points[i][j], _points[i+1][j], _points[i + 1][j + 1]);

            top_triangle_normals.set_triangle_vector(_shading_normals[i][j],
                                                     _shading_normals[i][j+1], _shading_normals[i+1][j+1]);
            bottom_triangle_normals.set_triangle_vector(_shading_normals[i][j],
                                                     _shading_normals[i+1][j], _shading_normals[i+1][j+1]);
            triangle_top.set_triangle(_screen_points[i][j], _screen_points[i][j+1], _screen_points[i + 1][j + 1]);
            triangle_bottom.set_triangle(_screen_points[i][j], _screen_points[i+1][j], _screen_points[i + 1][j + 1]);

            top_middle_point = rasterize_triangle(rasterized_points_up,
                                            triangle_top,
                                            top_triangle_normals, light_position,
                                            color_matrix, plane_coeffs_top);

            bottom_middle_point = rasterize_triangle(rasterized_points_down,
                                                     triangle_bottom,
                                                     bottom_triangle_normals, light_position,
                                                     color_matrix, plane_coeffs_bottom);

            find_depth_pixels(zbuffer_matrix, color_matrix,
                                                 rasterized_points_up, plane_coeffs_top, light_position, top_triangle_normals,
                                                 triangle_top_3d);
            find_depth_pixels(zbuffer_matrix, color_matrix,
                                                 rasterized_points_down, plane_coeffs_bottom,
                                                 light_position, bottom_triangle_normals,
                                                 triangle_bottom_3d);

            rasterized_points_up.clear(), rasterized_points_down.clear();
        }
    }
}

template <typename T1, typename T2>
Vector3D<T1> Terrain::find_int_normal(Point3D<T2> point_1, Point3D<T2> point_2, Point3D<T2> point_3)
{
    Vector3D<T2> normal = find_normal(point_1, point_2, point_3);
    Vector3D<T1> int_normal;
    int_normal.set_vector(normal.get_x(), normal.get_y(), normal.get_z());

    return int_normal;
}

void Terrain::find_all_normals()
{
    std::vector<Vector3D<int>> row_normals_up_triangles;
    std::vector<Vector3D<int>> row_normals_down_triangles;
    Vector3D<int> normal_up_triangle, normal_down_triangle;
    for (int i = 0; i < _width - 1; i++)
    {
        for (int j = 0; j < _height - 1; j++)
        {
             normal_up_triangle = find_int_normal<int, double>(_points[i][j],
                                                                                    _points[i][j+1],
                                                                                    _points[i+1][j+1]);
             normal_down_triangle= find_int_normal<int, double>(_points[i][j],
                                                                                            _points[i+1][j],
                                                                                            _points[i+1][j+1]);
             row_normals_up_triangles.push_back(normal_up_triangle);
             row_normals_down_triangles.push_back(normal_down_triangle);
        }
        _normals_up_triangles.push_back(row_normals_up_triangles);
        _normals_down_triangles.push_back(row_normals_down_triangles);
        row_normals_up_triangles.clear();
        row_normals_down_triangles.clear();
    }
}

Vector3D<double> Terrain::find_shading_normals(std::vector<Vector3D<int>> &normals, int i, int j)
{
    Vector3D<int> sum_normal;
    Vector3D<double>average_normal;

    int count_normals = normals.size();

    for (int i = 0; i < count_normals; i++){
        sum_normal = sum_normal + normals[i];
    }
    average_normal.set_vector(sum_normal.get_x(), sum_normal.get_y(), sum_normal.get_z());

    average_normal /= count_normals;
    return average_normal;
}

/*!
 * \brief Landscape::find_average_normals_of_each_node
 *  //расчет нормалей в вершинах полигонов
    //случаи:
    //1случай: угловые узлы карты высот (левый верхний и нижний правый - усреднить 2 нормали)
    //2 случай: угловые узлы карты высот (правый верхний и нижний левый - усреднить 1 нормаль)
    //3 случай: все боковые узлы по горизонтали (кроме угловых) - усреднение 3 нормалей
    //4 случай: все боковые узлы по вертикали (кроме угловых) - усреднение 3 нормалей
    //5 случай: все остальные - усреднение 6 нормалей
 */
void Terrain::find_average_normals_of_each_node()
{
    //усредненный вектор
    Vector3D<double> average_vector;

    //все усредненные векторы для каждого ряда узлов
    std::vector<Vector3D<double>> row_shading_normals;

    //векторы нормалей для каждого из случаев
    std::vector<Vector3D<int>> normals;

    for (int i = 0; i < _width; i++)
    {
        for (int j = 0; j < _height; j++)
        {
            //1 случай
            if ((i == 0 && j == 0) || (i == _width - 1 && j == _height - 1))
            {
                //qDebug()<< "Случай 1: " << "i = " << i << " j = " << j;
                if (i == 0){

                    normals.push_back(_normals_up_triangles[i][j]);
                    normals.push_back(_normals_down_triangles[i][j]);

                    average_vector = find_shading_normals(normals, i, j);
                    average_vector.normalize();
                    row_shading_normals.push_back(average_vector);
                }
                else{
                    normals.push_back(_normals_up_triangles[i - 1][j - 1]);
                    normals.push_back(_normals_down_triangles[i - 1][j - 1]);

                    average_vector = find_shading_normals(normals, i, j);
                    average_vector.normalize();
                    row_shading_normals.push_back(average_vector);
                }
            }
            //2 случай
            else if ((i == 0 && j == _height - 1) || (j == 0 && i == _width- 1))
            {
                //qDebug()<< "Случай 2: " << "i = " << i << " j = " << j;
                if (i == 0){
                    normals.push_back(_normals_up_triangles[i][j - 1]);

                    average_vector = find_shading_normals(normals, i, j);
                    average_vector.normalize();
                    row_shading_normals.push_back(average_vector);
                }
                else{
                    normals.push_back(_normals_down_triangles[i - 1][j]);

                    average_vector = find_shading_normals(normals, i, j);
                    average_vector.normalize();
                    row_shading_normals.push_back(average_vector);
                }
            }
            //3 случай
            else if((i == 0 && j > 0 && j < _height - 1) || (i == _width - 1 && j > 0 && j < _height - 1))
            {
                //qDebug()<< "Случай 3: " << "i = " << i << " j = " << j;
                if (i == 0)
                {
                    normals.push_back(_normals_up_triangles[i][j]);
                    normals.push_back(_normals_up_triangles[i][j - 1]);
                    normals.push_back(_normals_down_triangles[i][j]);

                    average_vector = find_shading_normals(normals, i, j);
                    average_vector.normalize();
                    row_shading_normals.push_back(average_vector);
                }
                else
                {
                    normals.push_back(_normals_up_triangles[i - 1][j-1]);
                    normals.push_back(_normals_down_triangles[i-1][j-1]);
                    normals.push_back(_normals_down_triangles[i-1][j]);

                    average_vector = find_shading_normals(normals, i, j);
                    average_vector.normalize();
                    row_shading_normals.push_back(average_vector);
                }
            }
            //4 случай
            else if((j == 0 && i > 0 && i < _width - 1) || (j == _height - 1 && i > 0 && i < _width - 1))
            {
                //qDebug()<< "Случай 4: " << "i = " << i << " j = " << j;
                if (j == 0)
                {
                    normals.push_back(_normals_down_triangles[i-1][j]);
                    normals.push_back(_normals_up_triangles[i][j]);
                    normals.push_back(_normals_down_triangles[i][j]);

                    average_vector = find_shading_normals(normals, i, j);
                    average_vector.normalize();
                    row_shading_normals.push_back(average_vector);
                }
                else
                {
                    normals.push_back(_normals_up_triangles[i-1][j - 1]);
                    normals.push_back(_normals_up_triangles[i][j-1]);
                    normals.push_back(_normals_down_triangles[i-1][j-1]);

                    average_vector = find_shading_normals(normals, i, j);
                    average_vector.normalize();
                    row_shading_normals.push_back(average_vector);
                }
            }
            else
            {
                //qDebug()<< "Случай 5: " << "i = " << i << " j = " << j;
                normals.push_back(_normals_up_triangles[i - 1][j - 1]);
                normals.push_back(_normals_up_triangles[i][j]);
                normals.push_back(_normals_up_triangles[i][j-1]);

                normals.push_back(_normals_down_triangles[i - 1][j - 1]);
                normals.push_back(_normals_down_triangles[i-1][j]);
                normals.push_back(_normals_down_triangles[i][j]);

                average_vector = find_shading_normals(normals, i, j);
                average_vector.normalize();
                row_shading_normals.push_back(average_vector);
            }
            normals.clear();
        }
        _shading_normals.push_back(row_shading_normals);
        row_shading_normals.clear();
    }
}

void Terrain::clear_normals()
{
    int width_landscape = (*this).get_width();
    for (int i = 0; i < width_landscape - 1; i++)
    {
        _normals_up_triangles[i].clear();
        _normals_down_triangles[i].clear();
        _shading_normals[i].clear();
    }
    _normals_up_triangles.clear();
    _normals_down_triangles.clear();
    _shading_normals.clear();
}


#endif
