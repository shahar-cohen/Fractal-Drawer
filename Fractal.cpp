//
// c++ base class and two subclasses used to print ascii fractals
//
#include<cmath>
#include <iostream>
#include "Fractal.h"

/**
 * @brief base class for fractal classes, constructs an empty matrix of an appropriate size to
 * later house the drawing of the fractal
 * has draw function for subclasses to use.
 * @param baseFactor -int  the size of the hight/width of the base (dim = 1) form of the fractal
 * @param dimension - int the dimention of the fractal
 */
Fractal::Fractal(int baseFactor, int dimension)
    : _baseFactor(baseFactor), _dimension(dimension),
    _matrix(vector<vector<char>>(pow(baseFactor, dimension),
            vector<char>(pow(baseFactor, dimension))))
{
    // normally would have initialized the _matrix here after checking that baseFactor and
    // dimensions are valid, but since i do that in FractalDrawer it seems redundant.
}

/**
 * @brief draws the fractal matrix of a fractal subclass instance.
 */
void Fractal::draw()
{
    int size = pow(_baseFactor, _dimension);

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            cout << _matrix[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

/**
 * @brief subclass of Fractal, creates a fractal using super class and fills it's matrix by the
 * rules of a SierpinskiCarpet.
 * is super class to SierpinskiTriangle and supplies the shouldCellBeFull method for it to use.
 * @param dimension - the dimension of the fractal
 * @param baseFactor - base factor of fractal - default set to 3
 */
SierpinskiCarpet::SierpinskiCarpet(int dimension, int baseFactor) : Fractal(baseFactor, dimension)
{
    int size = pow(_baseFactor, _dimension);

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            _matrix[i][j] = (_shouldCellBeFull(i, j)) ? FILLER_CHAR : SPACE_CHAR;
        }
    }
}

/**
 * @brief a recursive function to check if the drawing of a SierpinskiCarpet in indices i,j should
 * be full or empty.
 * @param i - row
 * @param j - col
 * @return true if should be full, false otherwise.
 */
bool SierpinskiCarpet::_shouldCellBeFull(int i, int j)
{
    if (i == 0 || j == 0)
    {
        return true;
    }

    if (i % _baseFactor == SIERPINSKI_SHAPE_EMPTY_CELL_IDX &&
        j % _baseFactor == SIERPINSKI_SHAPE_EMPTY_CELL_IDX)
    {
        return false;
    }

    return _shouldCellBeFull(i / _baseFactor, j / _baseFactor);
}

/**
 * @brief a subclass of SierpinskiCarpet, basically a SierpinskiCarpet of base factor 2.
 * @param dimension - dimension of fractal
 */
SierpinskiTriangle::SierpinskiTriangle(int dimension)
                    : SierpinskiCarpet(dimension, SIERPISKI_TRIANGLE_BASE_SIZE)
{
}

/**
 * @brief subclass of Fractal, creates a fractal using super class and fills it's matrix by the
 * rules of a Vicsek Fractal.
 * @param dimension - the dimension of the fractal
 * @param baseFactor - base factor of fractal - default set to 3
 */
VicsekFractal::VicsekFractal(int dimension, int baseFactor) : Fractal(baseFactor, dimension)
{
    int size = pow(_baseFactor, _dimension);

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            _matrix[i][j] = (_shouldCellBeFull(i, j)) ? FILLER_CHAR : SPACE_CHAR;
        }
    }
}

/**
 * @brief a recursive function to check if the drawing of a Vicsek Fractal in indices i,j should
 * be full or empty.
 * @param i - row
 * @param j - col
 * @return true if should be full, false otherwise.
 */
bool VicsekFractal::_shouldCellBeFull(int i, int j)
{
    if (i == 0 && j == 0)
    {
        return true;
    }

    if (abs((i % _baseFactor)  - (j % _baseFactor) ) == VICESEK_FRACTAL_EMPTY_CELL_IDX_DIFF)
    {
        return false;
    }

    return _shouldCellBeFull(i / _baseFactor, j / _baseFactor);
}
