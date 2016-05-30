/*
CSC 323/700 Spring 2015: Huffman Coding part-1 (C++)
Yan Chen
Due date: Feb 12, 2015
*/

#include<iostream>
#include<fstream>
using namespace std;

class Node 
{
	public:
	string charString;
	int charProbability;
	Node* next = NULL;
	Node* left = NULL;
	Node* right = NULL;
	int charCode;
};


class BinaryTree 
{
	public:
	Node* listHead = new Node();
	
	void insertionSort(Node* newNode);
	void printList(std::ofstream& outfile);
};


void BinaryTree::insertionSort(Node* newNode)
{	
	//Step 2.5: walker <- listHead
	Node* walker = listHead;
	
	/*
	Step 2.6: if walker.next != NULL && walker.prob < probIn
                  walker <- walker.next
	Step 2.7: repeat step 2.5 until one of the two conditions failed
	*/
	while(walker->next != NULL && walker->next->charProbability < newNode->charProbability) 
	{
		walker = walker->next;
	}
	
	//Step 2.8: newNode.next <- walker.next
	//          walker.next <- newNode

	newNode->next = walker->next;
	walker->next = newNode;
}


void BinaryTree::printList(std::ofstream& outfile){
		Node* walker = listHead;
		while(walker != NULL)
		{
			outfile<<"("<<walker->charString<<", "<<walker->charProbability<<", ";
			if( walker->next != NULL )
			{
			    outfile<<walker->next->charString<<")-->";	
			}
			else{
			    outfile<<"NULL"<<")-->NULLL";
			}
			walker = walker->next;
		}
		outfile<<endl;
}


int main(int argc, char* argv[]) 
{
	//Step 2.0: prepareing everything, including a initialize linked list with a dummy node
	string inFilename = (string)argv[1] + ".txt";
	string outFilename1 = (string)argv[2] + ".txt";
	string outFilename2 = (string)argv[3] + ".txt";
	
	ifstream inFile (inFilename);
	ofstream oFile1(outFilename1);
	ofstream oFile2(outFilename2);
		
 	
	BinaryTree bt;
	bt.listHead->charString = "dummy";	
		
	int count = 0;
	oFile1<<"Iteration "<<count<<": listHead--> ";
	bt.printList(oFile1);
	
	
	while(!inFile.eof())
	{
		/*
		Step 2.2: charString <-get the next letter from the file
    				probIn <- get the next prob from the file
    	Step 2.3: newNode <- make a new node
    	Step 2.4: assign charString and probIn to newNode
		*/
		Node* temp = new Node();
		inFile>>temp->charString;
		inFile>>temp->charProbability;
		
		//Steps 2.5 - 2.8
		bt.insertionSort(temp);
		
		count+=1;
		oFile1<<"Iteration "<<count<<": listHead-->";
		bt.printList(oFile1);		
	}
	//Step 2.9: Repeat step 2.1 to step 2.8 until the file is empty
	
	//Step 2.10: print the linked list onto the output file 1 using the format given above:
	bt.printList(oFile2);
	
	inFile.close();
	oFile1.close();
	oFile2.close();	
	
	cout<<"Successs: data successfully saved to output1 and output2 file. ";
		
	return 0;
	
}
