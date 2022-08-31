#ifndef __POINT_H
#define __POINT_H 
#include <iostream> 
#include <vector> 
#include <string> 

class Point{
	public: 
		Point(int x, int y); 
		int get_x(); 
		int get_y(); 
		friend std::ostream& operator<<(std::ostream& ost, const Point& point); 

	private: 
		int _x; 
		int _y; 

}; 

#endif 
