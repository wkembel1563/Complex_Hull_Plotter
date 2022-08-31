# Complex_Hull_Plotter
Takes cartesian coordinates as input, then calculates and plots their complex hull

main.cpp controls the logic of the program. First it reads cartesian coordinates - which are randomly generated - from a text file. It then proceeds to perform various calculations on the points following the Graham's Scan algorithm to determine their complex hull. 

The complex hull data is then output to another text file and runs the python script to plot the points with their complex hull.
