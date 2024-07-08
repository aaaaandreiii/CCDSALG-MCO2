#include <stdio.h>         //standard library for input/output in C
#include <stdlib.h>        //standard library for C

#define MAX_NUM_NODES 4
typedef char String[256];

int count_elements(char* arr) {
  int count = 0;
  int i = 0;
  while (arr[i] != '\0') {
    count++;
    i++;
  }
  return count;
}


void degreeOfVertices(char *arr) {
	for (int i = 0; i < MAX_NUM_NODES; i++){
		int num = count_elements(arr);
		printf("%s: %d", arr[0], num);	
	}
}

void BFS(int* arr) {
	//Breadth First Search - Use Queue
	//Clark Diana Hal Bruce
		//finish all contents of parent node array first 
			//then iterate through each child node (each element in the parent node array)
			
	
}

void DFS(int* arr) {
	//Depth First Search - Use Stack
	//Clark Diana Bruce Hal
		//search all arrays for same index
			//iterate through all child nodes of parent index
			//then increment index
		
}

int main(){
	// lecture at https://zoom.us/wb/doc/s3D8rldSQVWHxFCDMTdF5A/p/73517940867072
	
	int numOfNodes = MAX_NUM_NODES; 										//should be scanf
	
	String tree[MAX_NUM_NODES][MAX_NUM_NODES + 1] = {{"Bruce", "Diana", "\0"}, 
													 {"Clark", "Diana", "Hal", "\0"}, 
													 {"Diana", "Bruce", "Clark", "Hal", "\0"}, 
													 {"Hal", "Clark", "Diana", "\0"}};				// \0 is for -1 end of list of vertices
	
	for (int i = 0; i < MAX_NUM_NODES; i++){
		int j = 0;
		do {
			printf("%s ", tree[i][j]);
			j++;
		} while (j < MAX_NUM_NODES); // || tree[i][j] != "\0");			//should have a condition to prematurely terminate the loop when \0 is found
		printf("\n");
	}
	
	
	
	
	//Output requirements:
	//list of IDs with degree of every vertex
			//im thinking, array.size of every vertex
	int num = count_elements(tree) - 1;						//do not count \0 character
	printf("\n\n\n\n%d", num);
//	degreeOfVertices(tree[MAX_NUM_NODES][MAX_NUM_NODES]);
//	//BFS - Queue
//	BFS(tree);
//	//DFS - Stack
//	DFS(tree);
			
	return 0;
}