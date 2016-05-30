/*
CSC 323/700 Spring 2015: Project 6 (C++)
Yan Chen
Due date: April 27, 2015
*/

#include<iostream>
#include<string>
#include<fstream>
using namespace std;
	
int main(int argc, char* argv[]) 
{	 
	ifstream inFile1  (argv[1]);	 //input file1 include # of nodes follow by adjacent graph format: node1, node2
  	ofstream outFile  (argv[2]);	 //print all result
	
	int numNode;
	inFile1>>numNode;
	int arrSize = numNode + 1;
	
	//zeroing entire matrix
	int adjMatrix [arrSize] [arrSize]; 
	for( int i = 0; i<arrSize; i++ )
	{
		for( int j=0; j<arrSize; j++ )
		{	
			adjMatrix[i][j] = 0;
		}	
	}
	
	//load graph to matrix
	int i, j;
	while( !inFile1.eof() )
	{
		inFile1>>i;
		inFile1>>j;
		outFile<<"("<<i<<" "<<j<<") "<<endl;
		adjMatrix [i][j] = 1;
	}
	
	//print matrix
	for( int i = 0; i<arrSize; i++ )
	{
		for( int j=0; j<arrSize; j++ )
		{	
			outFile<<adjMatrix[i][j]<<" ";
		}	
		outFile<<endl;
	}
	
	//zeroing color array
	int* nodeColor = new int[arrSize];
	std::fill_n(nodeColor, arrSize, 0);
	
	
	
	int newColor = 0;
	int repeat = 0;
	
	while ( repeat == 0 ){
		//1
		newColor++;

		//2 & 3
		int newNode = 0 ;
		while( newNode <= numNode ) 
		{
			if( nodeColor[newNode] == 0 )
			{
				bool adjSameColor = false;
				for( int i = 0; i <= numNode; i++)
				{
					if( adjMatrix[newNode][i] > 0  && nodeColor[i] == newColor )
					{
						adjSameColor = true;
					}
 				}
 		
 				if( adjSameColor == false ){
 					nodeColor[newNode] = newColor;
				}
			}
 			newNode++;
		}
	
		//4
		outFile<<endl<<" "<<newColor<<endl;
		for(int i = 0; i<= numNode; i++){
			outFile.width(2);
			outFile<<i<<" ";
		}
		outFile<<endl;
		for(int i = 0; i<= numNode; i++){
			outFile.width(2);
			outFile<<nodeColor[i]<<" ";
		}
		outFile<<endl<<endl;
	
		//5
		int o = 0;
		//find the next uncolor node, if all nodes iterated, there are no more uncolor nodes
		while( nodeColor[o] > 0 && o < numNode  ){
			o++;
		}
		repeat = nodeColor[o];
	}

	//6
	for(int i = 0; i <= numNode ; i++){
		adjMatrix[i][i] = nodeColor[i];
	}
	
	outFile<<"number of color used: "<<newColor<<endl;
	for( int i = 0; i<arrSize; i++ )
	{
		for( int j=0; j<arrSize; j++ )
		{	
			outFile<<adjMatrix[i][j]<<" ";
		}	
		outFile<<endl;
	}
	
	inFile1.close();
	outFile.close();	
}
	
		
	
	
	
	
	
	
	


