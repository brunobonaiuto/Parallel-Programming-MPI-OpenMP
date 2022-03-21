/*
this program is a kd-tree by using 2 dimension, based on the tree data structure created from a vector by the standar library std::vector,
random data is used to create the vector among the threads by using parallel openmp
the implementation doesn't no include search and insert, since the kd-tree is done from immutable data set
*/
#include<iostream>
#include<algorithm> 
#include<vector> 
#include<bits/stdc++.h>
#include<random>
#include<omp.h>

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
this function builds the kd-tree, the kd-tree is made on multiples nodes
*/
static kdnode* build_kdtree(vector_type vect, bool axis, int* leaves){
	
    struct kdnode *new_kdnode = new kdnode;
    //creating a single node
    if(vect.size() == 1){
		new_kdnode -> point[0] = vect[0][0];
		new_kdnode -> point[1] = vect[0][1];
		new_kdnode -> right= nullptr;
		new_kdnode -> left= nullptr;
		*leaves = *leaves+1;
		return new_kdnode;
	}
	
	else{ //creating nodes from previous node
		int vector_size = vect.size();
		int median = vector_size/2;
		//axis false means we are on the x axis
		if(axis==false){
				std::sort(vect.begin(),vect.end());
		}else{
			//if(axis== true) so we are on the y axis
#pragma omp parallel shared(vect,median,vector_size)
	    {
            //sawping the vector
    #pragma omp for ordered
		    for(int i=0; i<vect.size(); i++){
        #pragma omp odered 
		    std::swap(vect[i][0], vect[i][1]);
		}
            //sorting the vector swaped
			std::sort(vect.begin(),vect.end());
	#pragma omp for ordered
			for(int i=0; i<vect.size(); i++){           
	#pragma omp ordered
                //swaping the vector one more time
				std::swap(vect[i][0], vect[i][1]);
                }
		    }//end of the pragma region
        }//end of the else

		vector_type left;
	    vector_type right;
        
	    new_kdnode-> point[0] = vect[median][0];
		new_kdnode-> point[1] = vect[median][1];
		for (int  i=0; i<median; i++)
			left.push_back(vect[i]);
		for(int i=median+1; i<vect.size();i++)
			right.push_back(vect[i]);

#pragma omp parallel
	{
#pragma omp single nowait
	    {
#pragma  omp task
		new_kdnode -> left =build_kdtree(left, !axis, leaves);
#pragma  omp task
	        {
	    if(right.size()>0)
		    new_kdnode -> right = build_kdtree(right, !axis, leaves);
	        }

	    }
	}
	return new_kdnode;	
	}
}//end of the function
};//end of the class

int main (int argc, char *argv[]){
	//root node
	struct kdnode* root = new kdnode;
	bool axis = false;
	int data;
    int leaves {0};
    data = pow(10, 2); 

	kdnode::vector_type vect{};
        // data * number of threads
		int n = data * 3; 
//generating random data in a parallalel region
#pragma omp parallel shared(vect,n)
{
			int rank = omp_get_thread_num(); 
			int nthrds = omp_get_num_threads(); 
			int count = n / nthrds;
			int start = start * count;
			int stop = start + count;
#pragma omp for 
	for(int i=0; i<data; i++)
    {	
		std::srand(i);
		double a = double( rand())/double(RAND_MAX);
		std::srand(i+10);
		double b = double( rand())/double(RAND_MAX);
	#pragma omp critical
		{
		vect.push_back({a,b});
		}
	}
}
	double startime = omp_get_wtime();
	root =  kdnode::build_kdtree(vect,axis,&leaves);
	double endtime = omp_get_wtime();
	//prints
		//std::cout<< "Len of the vector: " <<vect.size()<<""<<std::endl;
		std::cout<< "kd-tree's leaves: " <<leaves<<std::endl;
		std::cout<<"data: "<<data<<"\ntime: "<< endtime - startime << std::endl;
		std::cout<<"finished"<< std::endl;
	return 0;
}