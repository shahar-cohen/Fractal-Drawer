//
// Reads a "recipe" for a fractal from a .csv file and uses the classes in Fractal.cpp
// to draw ascii fractals.
// the csv file can have multiple lines containing two numbers separated by a comma, i.e. "1,2"
// First number should be either 1, 2 or 3 denoting the type of fractal - Sierpinski Carpet, Sierpiski Triangle or Vicsek Fractal respectively.
// Second number should be the order of the fractal (order of recursiun) - an int larger than 0 and smaller than 7.
//
// each line in the csv would cause the appropriate fractal to be printed to std::cout.
//
#include "Fractal.h"
#include <iostream>
#include <boost/tokenizer.hpp>
#include <boost/filesystem.hpp>
#include <string>


static const char *const DELIMITERS = ", \t\r";

static const int SIERPISKI_CARPET_TYPE = 1;

static const int SIERPISKI_TRIANGLE_TYPE = 2;

static const int VICSEK_FRACTAL_TYPE = 3;

static const char *const CSV_FILE_EXTENSION = ".csv";

/**
 * @brief fills fractalRecipeList with fractal attributes from a file, each line in file has 2 
 * attributes that define one fractal.
 * @param filePath - string file path
 * @param fractalRecipeList - stack<int>
 * @return true if succesful, false if encountered invalid input
 */
bool fillFractalRecipeStack(const std::string &filePath, stack<int> &fractalRecipeList)
{
    typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
    boost::char_separator<char> tokenSeparator{DELIMITERS}; //todo magic
    
    std::ifstream fileStream(filePath);

    string line;

    while (getline(fileStream, line))
    {
        tokenizer tok{line, tokenSeparator};

        int runNumber = 0;

        for (const auto &t: tok)
        {
            if (t.size() != 1)  // more than 1 char is not a valid number
            {
                return false;
            }
            try
            {
                int i = std::stoi(t);

                if (i < 1 || i > 6 || (i > 3 && runNumber == 0))  //validate args size
                {
                    return false;
                }

                fractalRecipeList.push(i);

                runNumber++;
            }
            catch (std::invalid_argument const &e)
            {
                return false;
            }
            catch (std::out_of_range const &e)
            {
                return false;
            }
        }

        if (runNumber != 2)  // makes sure that each line has 2 args
        {
            return false;
        }
    }
    return true;
}

/**
 * @brief checks that string filePath leads to a valid csv file
 * @param filePath  string 
 * @return true if valid csv, false otherwise 
 */
bool isValidFile(char* filePath)
{
    boost::filesystem::path myPath(filePath);

    return !(!boost::filesystem::exists(myPath) || !boost::filesystem::is_regular_file(myPath) ||
             boost::filesystem::extension(myPath) != CSV_FILE_EXTENSION);

}

/**
 * @brief creates a fractal and draws it for each recipe pushed to the stack.
 * @param fractalRecipeStack - stack<int>
 */
void printFractals(stack<int> fractalRecipeStack)
{
    while(!fractalRecipeStack.empty())
    {
        int dimension = fractalRecipeStack.top();
        fractalRecipeStack.pop();

        int fractalType = fractalRecipeStack.top();
        fractalRecipeStack.pop();

        switch(fractalType)
        {
            case SIERPISKI_CARPET_TYPE:
            {
                SierpinskiCarpet carpet(dimension);
                carpet.draw();
                continue;
            }

            case SIERPISKI_TRIANGLE_TYPE:
            {
                SierpinskiTriangle triangle(dimension);
                triangle.draw();
                continue;
            }


            case VICSEK_FRACTAL_TYPE:
            {
                VicsekFractal vicsekFractal(dimension);
                vicsekFractal.draw();
                continue;
            }

        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2) //todo magic
    {
        cerr << "Usage: FractalDrawer <file path>" << endl;
        exit(EXIT_FAILURE);
    }

    stack<int> fractalRecipeStack;

    if (!isValidFile(argv[1]) || !fillFractalRecipeStack(argv[1], fractalRecipeStack))
    {
        cerr << "Invalid input" << endl;
        exit(EXIT_FAILURE);
    }

    printFractals(fractalRecipeStack);
}

