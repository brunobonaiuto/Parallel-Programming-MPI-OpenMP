#include <iostream>
#include <vector> 
#include <algorithm>
#include <random> 


const int NDIM =2;
/*
The kd-tree is done by nodes, the class node is develop below
*/
struct kdnode{
	int point[NDIM];

	struct kdnode *left, *right;
	
	public:
	using vector_type = std::vector<std::vector<double>>;
/*
this function create one single node assigning left and right to nullprt
*/
static kdnode* create_node(vector_type vect, int* leaves){
		struct kdnode *new_kdnode = new kdnode;
		new_kdnode -> point[0] = vect[0][0];
		new_kdnode -> point[1] = vect[0][1];
		new_kdnode -> right= nullptr;
		new_kdnode -> left= nullptr;
		*leaves = *leaves+1;
		// so here we have create the node
		// [0,1] vect[row][col]
		return new_kdnode;
}
static vector_type sort_x_axis(vector_type& vect){
	std::sort(vect.begin(),vect.end());
	return vect;
}
static vector_type sort_y_axis(vector_type& vect){
	for(int i=0; i<vect.size(); i++)
			std::swap(vect[i][0], vect[i][1]);
			std::sort(vect.begin(),vect.end());
			for(int i=0; i<vect.size(); i++)
				std::swap(vect[i][0], vect[i][1]);
				return vect;	
}
/*
this function creates the nodes left and right
*/
static kdnode* create_all_nodes(vector_type& vect, bool axis, int* leaves){
	int median = vect.size() / 2;
	vector_type left;
	vector_type right;
	struct kdnode *new_kdnode = new kdnode;
		
		//we gonna add the value on the median
		new_kdnode-> point[0] = vect[median][0];
		new_kdnode-> point[1] = vect[median][1];

		//we are pushing to the right and left side
		for (int  i=0; i<median; i++)
			left.push_back(vect[i]);
		for(int i=median+1; i<vect.size();i++)
			right.push_back(vect[i]);

		new_kdnode -> left = build_kdtree(left, !axis, leaves);
	if(right.size()>0){
		new_kdnode -> right = build_kdtree(right, !axis, leaves);}
		return new_kdnode;
}
/*
this functions generates the data
*/
static kdnode* genarate_random_data(vector_type& vect, int& data){

	for(int i=0; i<data; i++){	
		std::srand(i);
		double a = double( rand())/double(RAND_MAX);
		std::srand(i+10);
		double b = double( rand())/double(RAND_MAX);
	 	vect.push_back({a,b});
	}
	//return vect;
}
/*
this function builds the kd-tree, the kd-tree is made on multiples nodes
*/
static kdnode* build_kdtree(vector_type vect, bool axis, int* leaves){
	//struct kdnode *new_kdnode = new kdnode;
	//if the vector is empty
	if(vect.size() == 1){
		create_node(vect, leaves);
	}
	//if node isn't empty(has some values like [0,1])
	else{
		//so axis false means we are on the x axis
		if(axis==false){
			sort_x_axis(vect);
		}else{
			//if(axis== true) so we are on the y axis
			sort_y_axis(vect);
		}
		create_all_nodes(vect,axis,leaves);
	}
}
};

int main (int argc, char *argv[]){
	//root node
	struct kdnode* root = new kdnode;
	bool axis = false;
	int leaves {0};
	int data = pow(10, 8);

	kdnode::vector_type vect{};
	kdnode::genarate_random_data(vect, data);
	root =  kdnode::build_kdtree(vect,axis,&leaves);
	
	//prints
		std::cout<< "Len of the vector: " <<vect.size()<<""<<std::endl;
		std::cout<< "kd-tree's leaves: " <<leaves<<std::endl;
	return 0;
}
