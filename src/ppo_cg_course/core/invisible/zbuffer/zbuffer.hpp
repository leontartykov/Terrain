#ifndef _ZBUFFER_HPP_
#define _ZBUFFER_HPP_

#include "zbuffer.h"

void ZBuffer::_init_zbuffer(int width, int height)
{
    _width = width, _height = height;

    std::vector<double> temp;
    std::vector<QColor> temp_color;

    for (int i = 0; i < _width; i++){
        for (int j = 0; j < _height; j++){
            temp.push_back(std::numeric_limits<int>::min());
            temp_color.push_back(QColor(255, 255, 255)); // в идеале поменять бы на текущий цвет фона
        }

        _zbuffer_matrix.push_back(temp);
        _color_matrix.push_back(temp_color);
        temp.clear();
        temp_color.clear();
    }
}

ZBuffer::~ZBuffer()
{
    for (int i = 0; i < _width; i++){
        for (int j = 0; j < _height; j++){
            _zbuffer_matrix[i].clear();
            _color_matrix[i].clear();
        }
    }

     _zbuffer_matrix.clear();
     _color_matrix.clear();
}

double ZBuffer::get_z_point(int index_i, int index_j) const{
    return _zbuffer_matrix[index_i][index_j];
}

void ZBuffer::set_z_point(int index_i, int index_j, double value){
    _zbuffer_matrix[index_i][index_j] = value;
}

std::vector<std::vector<double>> &ZBuffer::get_zbuffer_matrix(){
    return _zbuffer_matrix;
}

std::vector<std::vector<QColor>> &ZBuffer::get_color_matrix(){
    return _color_matrix;
}

int ZBuffer::get_width() const{
    return _width;
}

int ZBuffer::get_height() const{
    return _height;
}

/*!
 * \brief ZBuffer::is_background -- check if a pixel is background
 * \param index_i -- pixel color position in zbuffer
 * \param index_j -- pixel color position in zbuffer
 * \return true if success, else false
 */

bool ZBuffer::is_background(int index_i, int index_j)
{
    bool is_background = false;
    int r = 0, g = 0, b = 0;
    _color_matrix[index_i][index_j].getRgb(&r, &g, &b);
    if (r == 255 && g == 255 && b == 255)
        is_background = true;

    return is_background;
}

/*!
 * \brief ZBuffer::is_equal_colors -- check if colors are equal
 * \param index_i -- pixel color position in zbuffer
 * \param index_j -- pixel color position in zbuffer
 * \param rgb -- color
 * \return true if success, else false
 */

bool ZBuffer::is_equal_colors(int index_i, int index_j, QColor color)
{
    bool is_equal = false;
    int r_matrix = 0, g_matrix = 0, b_matrix = 0;
    _color_matrix[index_i][index_j].getRgb(&r_matrix, &g_matrix, &b_matrix);

    int r = 0, g = 0, b = 0;
    color.getRgb(&r, &g, &b);
    if (r_matrix == r && g_matrix == g && b_matrix == b){
        is_equal = true;
    }

    return is_equal;
}

void ZBuffer::set_color(int index_i, int index_j, QRgb color){
    _color_matrix[index_i][index_j].setRgb(color);
}

/*!
 * \brief ZBuffer::reset -- reset zbuffer to default
 */
void ZBuffer::reset()
{
    for (int i = 0; i < _width; i++){
        for (int j = 0; j < _height; j++){
            _zbuffer_matrix[i][j] = std::numeric_limits<int>::min();
            _color_matrix[i][j] = QColor(255, 255, 255);
        }
    }
}

#endif
