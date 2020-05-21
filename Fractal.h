//
// c++ base class and two subclasses used to print ascii fractals
//

#include <vector>
using namespace std;

#ifndef CPP_EX2_FRACTAL_H
#define CPP_EX2_FRACTAL_H

static const char FILLER_CHAR = '#';

static const char SPACE_CHAR = ' ';

static const int SIERPISKI_TRIANGLE_BASE_SIZE = 2;


static const int VICESEK_FRACTAL_EMPTY_CELL_IDX_DIFF = 1;

static const int SIERPINSKI_SHAPE_EMPTY_CELL_IDX = 1;

static const int SIERPINSKI_CARPET_BASE_SIZE = 3;

static const int VICSEK_FRACRAL_BASE_SIZE = 3;

/**
 * @brief abstract base class for fractal classes, constructs an empty matrix of an appropriate
 * size to later house the drawing of the fractal
 * has draw function for subclasses to use.
 * has shouldCellBeFull that subclasses MUST implement.
 * @param baseFactor -int  the size of the hight/width of the base (dim = 1) form of the fractal
 * @param dimension - int the dimention of the fractal
 */
class Fractal
{
public:
    /**
     * @brief constructor
     * @param baseFactor - shape's side size at dimension 1
     * @param dimension - the dimension of the fractal
     */
    Fractal(int baseFactor, int dimension);

    /**
     * @brief virtual destructor, because class has virtual methods
     */
    virtual ~Fractal() = default;

    /**
    * @brief draws the fractal matrix of a fractal subclass instance.
    */
    void draw();

protected:
    int _baseFactor;
    int _dimension;
    vector<vector<char>> _matrix;

private:
    virtual bool _shouldCellBeFull(int i, int j) = 0;

};

/**
 * @brief subclass of Fractal, creates a fractal using super class and fills it's matrix by the
 * rules of a SierpinskiCarpet.
 * is super class to SierpinskiTriangle and supplies the shouldCellBeFull method for it to use.
 * @param dimension - the dimension of the fractal
 * @param baseFactor - base factor of fractal - default set to 3
 */
class SierpinskiCarpet: public Fractal
{
public:
    SierpinskiCarpet(int dimension, int baseFactor = SIERPINSKI_CARPET_BASE_SIZE);

private:
    bool _shouldCellBeFull (int i, int j) override;
};

/**
 * @brief a subclass of SierpinskiCarpet, basically a SierpinskiCarpet of base factor 2.
 * @param dimension - dimension of fractal
 */
class SierpinskiTriangle: public SierpinskiCarpet
{
public:
    SierpinskiTriangle(int dimension);
};

/**
 * @brief subclass of Fractal, creates a fractal using super class and fills it's matrix by the
 * rules of a Vicsek Fractal.
 * @param dimension - the dimension of the fractal
 * @param baseFactor - base factor of fractal - default set to 3
 */

class VicsekFractal: public Fractal
{
public:
    VicsekFractal(int dimension, int baseFactor = VICSEK_FRACRAL_BASE_SIZE);

private:
    bool _shouldCellBeFull (int i, int j) override;
};


#endif //CPP_EX2_FRACTAL_H
