#include "stack.h" 
#include <cmath> 

Stack::Stack(){} 

Stack::~Stack(){

	// delete all point in vectors 
	delete bottom; 
	for(auto s : Q) delete s; 

}

void Stack::push(int idx){ _stack.push_back(Q[idx]); }  

// POP
void Stack::pop(){ 

	if(_stack.empty()) throw std::runtime_error("Stack Empty\n"); 
	else _stack.pop_back(); 

} 

// TOP - returns ptr to top of stack 
Point* Stack::top(){ 

	Point * tp;

	// return 'top' of stack (last element in vector)
	if(_stack.empty()) throw std::runtime_error("Stack Empty\n"); 
	else{ tp = _stack[_stack.size() - 1]; } 

	return tp; 

} 

// NEXT TO TOP
// returns ptr to Point 2nd from top in the stack 
Point* Stack::next_to_top(){ 

	Point * nxt_to_top;

	// return 'next to top' of stack (second-to-last element in vector)
	if(_stack.empty()) throw std::runtime_error("Stack Empty\n"); 
	else{ nxt_to_top = _stack[_stack.size() - 2]; } 

	return nxt_to_top; 
} 							                                        

// ADD POINT
// Add points to candidate points vector 
void Stack::add_point(int x, int y){ Q.push_back(new Point{x, y}); }


// BOTTOM MOST - returns which point is bottom-most (closer to bottom left of coordinate plane) 
// returns -1 for min points, 1 for new point, 0 for equal 
int Stack::bottomMost(int min_y, int min_x, int x, int y){

	int result = 0; 

	// compare y values 
	if(min_y < y){ result = -1; }

	// if equal, lowest x val will determine bottom-most
	else if(min_y == y){

		if(min_x < x){ result = -1; } 		// min point is lower
		else if(min_x == x){ result = 0; } 	// points are equal 
		else{ result = 1; }			// new x val is lower

	}

	// new y val is lower
	else{ result = 1;  }

	return result; 

} 

// PUSH BOTTOM
// finds bottommost candidate point and moves to stack  
void Stack::push_bottom(){

	// Linear search for min value
	// index 0 is default min
	int min_idx = 0, result = 0; 
	int y = 0, min_y = Q[min_idx]->get_y();		
	int x = 0, min_x = Q[min_idx]->get_x(); 
	for(int i = 1; i < Q.size(); ++i){

		// get new point's x and y 
		y = Q[i]->get_y(); 
		x = Q[i]->get_x(); 

		// check which is bottommost
		result = bottomMost(min_y, min_x, x, y); // -1 = min point, 1 = new point, 0 = points are equal 
		
		if(result == 1){			// new point is min
			min_idx = i; 
			min_y = Q[min_idx]->get_y();		
			min_x = Q[min_idx]->get_x(); 
		}
		else if(result == 0){			// min and new point are identical 
			
			// delete new identical point 
			delete Q[i]; 
			Q.erase(Q.begin() + i);		// O(n) must resettle all elements 
			
			// decrement to return to this index next loop 
			i--; 

		}
		else{}					// current min is bottom-most 
	
	}

	// Push bottom point to stack and delete from Q
	push(min_idx); 

	// Set bottom_most point of stack 
	bottom = Q[min_idx]; 

	// Remove from Q
	Q.erase(Q.begin() + min_idx); 			// O(n) 
	

}                                                         

// COMPARE POLAR ANGLE - find MAX 
// Compares p1 and p0 by their angle to the bottom-most point 
// Mode 1 (show_collinear = false): returns 1 is p1's angle is bigger. returns 0 if p0's angle is bigger or collinear. 
// Mode 2 (show_collinear = true): same as mode 1, except collinear points will return -1 
int Stack::compPlrAngle(Point * p1, Point * p0, bool show_collinear){

	int result = 1; 
	Point * p = bottom; 
	
	// Find vectors <pp0> and <pp1> where p = bottom
	// <ab> is the vector from point a to point b
	Point pp0{p0->get_x() - p->get_x(), p0->get_y() - p->get_y()}; // <pp0> 
	Point pp1{p1->get_x() - p->get_x(), p1->get_y() - p->get_y()}; // <pp1> 
		
	// Calc cross product
	// pp1 X pp0 = x1y0 - x0y1
	int x1, y1, x0, y0; 
	x1 = pp1.get_x(); y1 = pp1.get_y();  	// get pp1 coordinates 
	x0 = pp0.get_x(); y0 = pp0.get_y();	// get pp0 coordinates  

	int cross_product = (x1 * y0) - (x0 * y1);	

	// if cp < 0, p1 has smaller angle. If cp > 0, p0 has smaller angle. If cp == 0, collinear
	if(show_collinear == false){ 		// return 1 or 0 
		if(cross_product < 0) result = 1; 
		else result = 0; 
	}
	else{					/// return 1, 0, or -1
		if(cross_product < 0) result = 1; 
		else if(cross_product > 0) result = 0; 
		else result = -1; 
	}
		
	return result; 

}

// COMPARE POLAR ANGLE - find MIN 
// Compares p1 and p0 by their angle relative to p
// returns 1 if p2's angle is smaller. returns 0 if p1's angle is smaller or collinear
int Stack::compPlrAngle(Point * p, Point * p1, Point * p2){

	int result = 1; 
	
	// Find vectors <pp1> and <pp2> 
	// <ab> is the vector from point a to point b
	Point pp2{p2->get_x() - p->get_x(), p2->get_y() - p->get_y()}; // <pp2> 
	Point pp1{p1->get_x() - p->get_x(), p1->get_y() - p->get_y()}; // <pp1> 
		
	// Calc cross product
	// pp2 X pp1 = x2y1 - x1y2
	int x2, y2, x1, y1; 
	x2 = pp2.get_x(); y2 = pp2.get_y();  	// get pp2 coordinates 
	x1 = pp1.get_x(); y1 = pp1.get_y();	// get pp1 coordinates  

	int cross_product = (x2 * y1) - (x1 * y2);	

	// If cp < 0, left turn.  If cp > 0, right turn. If cp == 0, collinear with no turn 
	if(cross_product <= 0) result = 1; 
	else if(cross_product > 0) result = 0; 
		
	return result; 

} 

// MAX INDEX - HEAP 
// Returns index of the node with largest angle relative to bottom 
int Stack::maxIdx(int p, int left, int right, int N){

	int min = p; 	

	if(left < N && compPlrAngle(Q[left], Q[min], false)) min = left;     //compPlrAngle is true when left has larger angle than min
	if(right < N && compPlrAngle(Q[right], Q[min], false)) min = right; 

	return min; 
} 

// SINK DOWN 
// Max Heap sinkDown
void Stack::sinkDown(int p, int N){

	Point * temp = NULL; 
	int left = 2*p + 1; 
	int right = 2*p + 2; 
	int imv = maxIdx(p, left, right, N); 
	while(p != imv){
	
		// swap parent with max 
		temp = Q[p]; 
		Q[p] = Q[imv]; 
		Q[imv] = temp; 

		// reset parent and children index for next comparison   
		p = imv; 
		left = 2*p + 1; 
		right = 2*p + 2; 
		
		// find max of this set
		imv = maxIdx(p, left, right, N); 	

	}	

}

// BUILD Q HEAP 
// initialize Q as max heap - bottom up process
void Stack::buildQHeap(){

	int i; 
	int N = Q.size(); 
	for(i = (N - 2)/2; i >= 0; --i){ sinkDown(i, N); }

}

// CLOSEST POINT 
// Returns index of point closest to bottom by distance 
int Stack::closestPoint(int i, int j){

	// get x-distance between ith point, jth point and bottom 
	int dxi, dxj; 
	dxi = Q[i]->get_x() - bottom->get_x(); 
	dxj = Q[j]->get_x() - bottom->get_x(); 

	// get y-distance between ith point, jth point and bottom 
	int dyi, dyj; 
	dyi = Q[i]->get_y() - bottom->get_y(); 
	dyj = Q[j]->get_y() - bottom->get_y(); 

	// use pythagorean theorem to calc total point from bottom 
	double Di, Dj, sum;  
	dxi = dxi * dxi; 			// x^2
	dyi = dyi * dyi;			// y^2 
	sum = (double) dxi + (double) dyi;	// x^2 + y^2  
	Di = sqrt(sum);				// Dist = sqrt(x^2 + y^2)  
	
	dxj = dxj * dxj; 	
	dyj = dyj * dyj; 
	sum = (double) dxj + (double) dyj; 
	Dj = sqrt(sum); 

	// return index of point with min distance 
	if(Di >= Dj) return j; 
	else return i; 

}

// SORT Q
// heap sorts Q points by polar angle to bottom point, removed duplicates  
// least --> greatest on [0, pi]
void Stack::sort_Q(){

	// Initialize Q as max heap bottom up 
	buildQHeap(); 

	// Heapsort Q 
	// place each max node at the end of list, but in front of previous max nodes 
	// final result min --> max 
	int i = 0, N = Q.size(); 	
	Point * temp = NULL; 
	for(i = N-1; i > 0; --i){

		// swap root not with end node 
		temp = Q[i]; 
		Q[i] = Q[0]; 
		Q[0] = temp; 

		// decrement heap size
		N--; 

		// sinkDown new root node
		sinkDown(0, N); 

	}
	N = Q.size(); 

	// Remove duplicates 
	int cmp_result = 0; 
	int idx_to_del = 0; 
	for(i = 0; i < N-1; ++i){
	
		cmp_result = compPlrAngle(Q[i], Q[i+1], true); 

		// Delete duplicate closest to bottom 
		if(cmp_result == -1){
		
			idx_to_del = closestPoint(i, i+1);  	// get index of point closer to bottom 
			delete Q[idx_to_del];			// delete closer point from Q 
			Q.erase(Q.begin() + idx_to_del); 

			N = Q.size();				// reset N = size of new Q 
			i--; 					// reset i to check if farther point also has duplicates

		}

	} 

}                                                       

// GENERATE CONVEX HULL 
// uses sorted Q and bottom to find convex hull. final set place in stack in counterclockwise order 
void Stack::generate_convex_hull(){

	// bottom point is already pushed to stack 

	// push first two points of Q to stack 
	push(0); 
	push(1); 
	
	// compare top 2 points in stack with next point in Q
	// pop top if the 3 points make a right turn, push new Q point to stack if left turn 
	int i; 
	int left_turn; 
	for(i = 2; i < Q.size(); ++i){
	
		left_turn = compPlrAngle(next_to_top(), top(), Q[i]); 

		while(!left_turn){ 	// false for left turn or straight turn 

			pop(); 
			left_turn = compPlrAngle(next_to_top(), top(), Q[i]); 

		}
		
		push(i); 		// push next point to S

	}
}                                                                                                                                        

// OPERATER << OVERLOAD 
// Streaming out the stack,  will call Point's << override
std::ostream& operator<<(std::ostream& ost, const Stack& stack){
	
	// output x points 
	for(auto p : stack._stack) ost << p->get_x() << " "; 
	ost << std::endl; 

	// output y points 
	for(auto p : stack._stack) ost << p->get_y() << " ";
	ost << std::endl; 

	return ost;

}     

// PRINT Q
// Save all points in Q to file. x's on line 1. y's on line 2. 
void Stack::print_Q(std::ofstream& ofs){

  	// print out all candidate points 
  	for(auto& p : Q){
		// print x values on first line 
		ofs << p->get_x() << " "; 
	}
	ofs << std::endl; 

  	for(auto& p : Q){
		// print y values on second line 
		ofs << p->get_y() << " "; 
	}
	ofs << std::endl; 

} 

// SIZE OF Q
// Getter for num of points in Q vector
int Stack::Qsize(){ return Q.size(); }
