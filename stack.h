#ifndef __STACK_H
#define __STACK_H
#include "point.h"  	// Point class, iostream, vector, string
#include <fstream> 

class Stack{
	public: 
		Stack(); 
		~Stack();			// destroys allocated points  
		void push(int idx); 
		void pop(); 
		Point* top(); 
		Point* next_to_top(); 		// returns ptr to Point 2nd from top in the stack 
    		void add_point(int x, int y); 	// adds a point to Q
    		void push_bottom();             // finds bottommost candidate point and moves to stack  
		void sort_Q();           	// sorts candidate points by polar angle to anchor point, removed duplicates  
							// places them in counterclockwise order around bottom point
    		void generate_convex_hull();    // places convex hull of points in stack using grahams scan
               		                        	// for use after finding bottom and sorting 
						// Streaming out the stack,  will call Point's << override
		friend std::ostream& operator<<(std::ostream& ost, const Stack& stack);  
    		void print_Q(std::ofstream& ofs); // Outputs Q vector points to file 	
		int Qsize(); 
						  // Returns which point is bottom-most (closer to bottom left of coordinate plane) 
		int bottomMost(int min_y, int min_x, int x, int y); 
						  // Compares polar angle of two points to bottom most point
		int compPlrAngle(Point * p0, Point * p1, bool show_collinear); 
		int compPlrAngle(Point * p, Point * p1, Point * p2); 
		int closestPoint(int i, int j);	  // Returns index to point closest to bottom 

		// Heap operations 
		void buildQHeap(); 
		void sinkDown(int idx, int N);
		int maxIdx(int p, int left, int right, int N); 

	private:
		std::vector<Point*> _stack; 
		std::vector<Point*> Q; 
	    	Point * bottom; 

}; 

#endif 
