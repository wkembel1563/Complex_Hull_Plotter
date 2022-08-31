#include "point.h"

// POINT CONSTRUCTOR 
Point::Point(int x, int y) : _x{x}, _y{y} {} 

// GET X 
// Getter for x coordinate 
int Point::get_x(){ return _x; } 

// GET Y
// Getter for y coordinate
int Point::get_y(){ return _y; } 

// OPERATOR<< OVERLOAD
std::ostream& operator<<(std::ostream& ost, const Point& point){

  ost << point._x << "\n" << point._y; 

  return ost; 
} 
