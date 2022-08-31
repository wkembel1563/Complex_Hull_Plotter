# Complex Hull Plotter

## HOW TO RUN THE PROGRAM
- Before running the program compile with 'make' command

1. To run the code with 10 random points
	- type: ./chull < 10.txt

2. To run the code with 1000 random points 
	- type: ./chull < 1000.txt

3. To run the code with hand picked special cases 
	- type: ./chull < special.txt

4. To run with any input file
	- type: ./chull
	- Enter filename when prompted 

5. To run with 20 NEW points generated randomly at runtime 
	- type: ./chull < default_filename.txt


## HOW THE CODE IS STRUCTURED
This program implements Graham's Scan to find the convex hull of a set of points. 

The points are read and processed is C++. Q points and convex hull are printed to
'convex_hull.txt'. The C++ code then calls a python script which plots the points 
with matplotlib library. 

There are two classes: Point and Stack. Stack contains a vector Q which holds the
input points, and a vector _stack which acts as the stack. Each vector aggregates
a set of points. 

C++ Files:
main.cpp
stack.h
stack.cpp
point.h 
point.cpp

The header files define the two classes. The cpp files hold the implementation of 
their methods. The majority of the work is done by the stack methods as it manipulates
its _stack and Q vectors. 

Main starts by calling a random point generator and places those points in rand_points.txt. 
The number and range of those points are determined by macros on lines 5-6 of main.cpp. 
A Stack object is instanced. 

Then the program prompts for a filename which should contain the program input, 
which can be provided manually or via redirection with another file that contains the name
of a file with points stored inside. 

The files size and points are read and the points are stored in the Q vector via the 
add_point() method of Stack.

Stack's push_bottom method is called which finds the bottom-most point in Q, removes it, 
and pushes it to the stack. A pointer attribute of Stack called 'bottom' also points to it. 

Stack's sort_Q method is then called which takes the remaining points in Q, sorts them
into a Max Heap based on their polar angle relative to the bottom-most point, 
and then applies heapsort to remove each max of the heap, replace it with the 
last element of the vector, and then place the max at the end of the vector. 
sinkDown is called to restore the heap properties after each swap. 

All polar angles are determines via 

Each successive max value is placed before the previous max at the end of the vector, 
so the result after heap sort is the points sorted from min to max from the 0th to 
last element (ascending order). 

The last part of sort_Q finds any pair of points with the same polar angle and calculates
their distance from the bottom point. The closer of the pair, is removed from Q. If a point
is identical to another, one will be removed by default. 

Next Stack's generate_convex_hull method is called which implements the typical graham's scan
method of pushing two points to the stack, and calculating whether they form a right or 
left turn with the next point in Q via cross product. If a left turn is made, the new point
is pushed to the stack. If a right turn is made, the top is popped, and the next top two points
of the stack are compared with the same point in Q until a left turn is made. 
Then that point in Q is pushed to the stack, and the process repeats for the next point in 
Q until the points that make up all left turns are left in the stack - the convex hull. 

Finally the _stack vector is output to convex_hull.txt via the overloaded << operator for 
the Stack object. 

The last part of main.cpp makes a system call to run the python script which takes the 
convex_hull.txt points with all original Q points and the convex hull points as input. 
Q and the convex hull are plotted in different plots for easy comparison. 

### TXT Files:
 
10.txt
- contains filename 10_point.txt to allow redirection 

1000.txt
- contains filename 1000_point.txt to allow redirection 

1000_point.txt
- contains 1000 random points 

10_point.txt
- contains 10 random points 

special.txt
- contains filename special_cases.txt to allow redirection 

special_cases.txt
- contains handpicked special case points plus some extra points

convex_hull.txt
- contains Q and convex hull point output from C++ 

default_filename.txt
- contains filename rand_points.txt which contains 20 random points generated at 
	
runtime by the c++ program 
- can be used for redirection 

rand_points.txt
- contains 20 new randomly generated points after each run of the program
