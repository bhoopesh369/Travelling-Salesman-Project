#include <iostream>
#include <vector>
#include <climits>

using namespace std;


vector<vector<int> > GreedyApproach(vector<vector<int> > adj_matrix)
{
	int size = adj_matrix.size(); 

	//if the value == 1, we have visited the node already
	int visited_nodes[size];

	//initialise the array
	for(int j=0; j<size; j++){
		visited_nodes[j]=0;
	}

	//gives the array of the route the person would take 
	int route[size]; 
	int counter = 0; //current position where route is filled to

	

	//find the minimum distance in the adjacency matrix, and we will use one of the vertices as the starting index
	int min_dist_adj_vertex;
	int min_dist_adj = INT_MAX;

	for(int j=0; j<size; j++){
		for(int k=0; k<size; k++){
			if(adj_matrix[j][k]<min_dist_adj){
				min_dist_adj = adj_matrix[j][k];
				 min_dist_adj_vertex=j;
			}
		}
	}
	
	visited_nodes[ min_dist_adj_vertex] = 1;
	route[counter++]= min_dist_adj_vertex;

	int j = 0, i = 0;
	int min = INT_MAX;


	while ( j < size)
	{
		

		 //to prevent self loops

		// goes through all unvisited nodes from the i and finds the min
		if (j!=i && visited_nodes[j] == 0)
		{
			if (adj_matrix[i][j] < min)
			{
				min = adj_matrix[i][j];
				route[counter] = j ; 
			}
		}
		//in this manner would traverse and check all the possible paths originating from the node i
		j++;

		//at the end of the array (ie when all possible paths from the vertex is considered and route is found)
		if (j == size)
		{
			//reset
			j = 0;
			min= INT_MAX;

			//the route[counter] would point to the index of the next node that needs to be visited
			visited_nodes[route[counter]] = 1;	
			i = route[counter++] ;

			
			//break if the new i is out of bounds
			if(i >= size) break;
			
			//break when you reach the corder
			if(counter > size-1) break;
		}
	}

	//would find a path from 0,0 which would cover each and every element (since it is a complete graph)



	vector<vector<int> > output;

	vector<int> temp;
	temp.push_back(route[size-1]);
	temp.push_back(route[0]);
	temp.push_back(adj_matrix[temp[1]][temp[0]]);
	

	output.push_back(temp);

	for(int i=0; i<size-1; i++){
		vector<int> temp;
		
		temp.push_back(route[i]);
		temp.push_back(route[i+1]);
		temp.push_back(adj_matrix[temp[1]][temp[0]]);

		output.push_back(temp);
	}
	
	return output;
	
	
}

// int main()
// {

// 	// Input Adjacency matrix
// 	vector<vector<int> > adj_matrix =  { { -1, 10, 15, 20 },
// 								{ 10, -1, 35, 25 },
// 								{ 15, 35, -1, 30 },
// 								{ 20, 25, 30, -1 } };

// 	// Function giving the adjacenecymatrix
// 	vector<vector<int> > output = GreedyApproach(adj_matrix);

// 	for(int i=0; i<output.size(); i++){
// 		for(int j=0; j<3; j++){
// 			cout<<output[i][j]<<" ";
// 		}
// 		cout<<endl;
// 	}
// }
