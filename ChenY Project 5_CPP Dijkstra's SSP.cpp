/*
CSC 323/700 Spring 2015: Project 5 (C++)
Yan Chen
Due date: April 19, 2015
*/

#include<iostream>
#include<string>
#include<fstream>
using namespace std;


int main(int argc, char* argv[]) 
{	 
	ifstream inFile1  (argv[1]);	 //input file1 include # of nodes follow by graph format: node1, node2, cost
  	ifstream inFile2  (argv[2]);	 //input file2 include the source node, an integer
	ofstream outFile  (argv[3]);	 //print graph, source node, all shortest paths from source
	
	int sourceNode;
	inFile2>>sourceNode;
	
	int numNode;
	inFile1>>numNode;
	int arrSize = numNode + 1;
	
	//zeroing entire matrix
	int costMatrix [arrSize] [arrSize]; 
	for( int i = 1; i<arrSize; i++ )
	{
		for( int j=1; j<arrSize; j++ )
		{	
			costMatrix[i][j] = 0;
		}	
	}
	
	//load graph to matrix
	int i, j, cost;
	while( !inFile1.eof() )
	{
		inFile1>>i;
		inFile1>>j;
		inFile1>>cost;	
		costMatrix [i][j] = cost;
	}
	
	int* marked   = new int[arrSize];	//1 = marked, 0 unmarked
	std::fill_n(marked, arrSize, 0);
	
	int* bestCost = new int[arrSize];
	std::fill_n(bestCost, arrSize, 999);
	
	int* parent   = new int[arrSize];
	std::fill_n(parent, arrSize, sourceNode);
	
   //load source row  from cost matrix to best cost array
	i = sourceNode;
	for(j= 1; j < arrSize; j++){
		if (costMatrix[i][j] > 0 )
			bestCost[j] = costMatrix[i][j];
	}
	
	//1
	int minNode = sourceNode;
	bool allMarked = false;
	
	while(allMarked != true){
	   //2
		marked[minNode] = 1;
	
	   //3 & 4
		for(int i =1; i<arrSize; i++)
		{
			if( marked[i] != 1 && costMatrix[minNode][i] != 0 ) 
			{
				int newNode = i;
				int tempCost = bestCost[minNode] + costMatrix[minNode][newNode];
				if(	tempCost < bestCost[newNode] )
				{
					bestCost[newNode] = tempCost;
					parent[newNode] = minNode;
				}
			}
		}
		
	   //5
		int temp = 999999;
		for( int i = 1; i < arrSize; i++)
		{	
			if( marked[i] != 1 )
			{	
				if( bestCost[i] < temp )
				{			
					temp = bestCost[i];
					minNode = i;
				}	  
			}		
		}
		
	   //6
		allMarked = true;
		for( int i = 1; i < arrSize; i++)
		{	
			if( marked[i] == 0 )
			{
				allMarked = false;
			}
		}
	}	
		
   //7
	for( int i = 1; i<arrSize; i++ )
	{
		for( int j=1; j<arrSize; j++ )
		{	
			outFile<<costMatrix[i][j]<<"\t";
		}	
		outFile<<endl;
	}
	outFile<<"Source Node: "<<sourceNode<<endl;
	for(int i = 1; i<arrSize; i++){
		if(i != sourceNode){
			outFile<<"source to "<<i<<" ("<<(bestCost[i])<<") and path: "<<i<<"<--";
			int p = i;
			while(parent[p] != sourceNode){
				outFile<<parent[p]<<"<--";
				p = parent[p];
			}
			outFile<<sourceNode<<endl;
		}
	}
	
	inFile1.close();
	inFile2.close();
	outFile.close();	
}
	
		
	
	
	
	
	
	
	


