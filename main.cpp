#include "stack.h" 
#include <cstdlib> 
#include <ctime> 
#include <filesystem> 

#define RAND_POINTS 20
#define MIN 10 
#define MAX 120 

// RAND NUM GENERATOR Generate random set of RAND_POINTS number of coordinates
// coordinates vary between MIN and MAX
void randomCoordinateGenerator(); 

int main(){

	// create random points, place in rand_points.txt
	randomCoordinateGenerator(); 

	// instance stack 
	Stack stack; 
	
	// read points from file and push to stack's 'Q' vector  
	std::string filename; 			// Get filename
	std::cout << "Input File Name: "; 
	std::cin >> filename; 
	std::cout << std::endl; 

	std::ifstream ifs{filename}; 		// Open file 
	if(!ifs) throw std::runtime_error("Could not open file"); 
	
	int num_of_points;      		// Get num of points 
	ifs >> num_of_points; 
	
	if(num_of_points < 3){			// Validate input file has at least 3 points 
		std::cout << "Convex hull is empty. Exiting..." << std::endl; 
		return 1; 
	}

	int x, y;				// Place candidate points in Q vector  
	int size = num_of_points; 
	while(num_of_points > 0){      		
		ifs >> x >> y; 
		stack.add_point(x, y); 
		num_of_points--; 
	}

	// Validate num of points read is consistent with total num of points specified in file 
	if(size != stack.Qsize()){
		std::cout << "Num of points not consistent with input file" << std::endl; 
		return 1; 
	}

	// Write Q to output file 
	std::string outputfile{"convex_hull.txt"}; 
	std::ofstream ofs{outputfile}; 
	stack.print_Q(ofs); 

	// find bottom-most point and push it to the stack 
	stack.push_bottom(); 
	
	// sort remaining candidate points by polar angle to bottom point, delete duplicates 
	stack.sort_Q(); 

	// Verify at least 2 points remain in Q 
	if(stack.Qsize() < 2){			
		std::cout << "Convex hull is empty. Exiting..." << std::endl; 
		return 1; 
	}
	
	// find convex hull and store in stack 
	stack.generate_convex_hull(); 
	
	// write convex hull to file 
	ofs << stack; 

	// plot points
	std::string working_dir = std::filesystem::current_path(); // get current directory path 
	std::string pythonfile = "/plot_points.py"; 			
	std::string command = "python3 ";
	working_dir += pythonfile; 				   // add python file to path 
	command += working_dir;					   // generate command to run python script 
	system(command.c_str());				   // run command 	

	return 0; 
} 

void randomCoordinateGenerator(){

	srand(time(NULL)); 

	// open file and output num of points 
	std::ofstream ofs{"rand_points.txt"}; 
	ofs << RAND_POINTS; 

	// generate random points and output to text file
	int x = 0, y = 0; 
	for(int i = 0; i < RAND_POINTS; i++){

		// move to next line in file 
		ofs << std::endl; 

		// generate coordinate
		// num = (rand() % (upper – lower + 1)) + lower
		x = (rand() % (MAX - MIN + 1)) + MIN; 
		y = (rand() % (MAX - MIN + 1)) + MIN; 

		// output "x y" to file 
		ofs << x << " " << y; 

	} 

} 

