# Fractal-Drawer
A script prints out fractals by instructions in .csv file using classes in Fractal.cpp

Reads a "recipe" for a fractal from a .csv file and uses the classes in Fractal.cpp to draw ascii fractals.

the csv file can have multiple lines containing two numbers separated by a comma, i.e. "1,2"

First number should be either 1, 2 or 3 denoting the type of fractal - Sierpinski Carpet, Sierpiski Triangle or Vicsek Fractal respectively.

Second number should be the order of the fractal (order of recursiun) - an int larger than 0 and smaller than 7.

each line in the csv would cause the appropriate fractal to be printed to std::cout.

------------------------------------------------------------

Files:

-FractalDrawer.cpp - script that draws the fractals according to given .csv file

-Fractal.h - header for Fractal class

-Fractal.cpp - an abstract base class and two subclasses of Fractals
