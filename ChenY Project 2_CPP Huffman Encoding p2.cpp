/*
CSC 323/700 Spring 2015: Huffman Coding part-2 (C++)
Yan Chen
Due date: Feb 22, 2015
*/

#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class Node 
{
	public:
	int prob;
	int charCode;
	string charString;
	
	Node* next  = NULL;
	Node* left  = NULL;
	Node* right = NULL;
};

class LinkedList 
{
	public:
	Node* listHead    = new Node();
	Node* oldListHead = new Node();
	
	void insertionSort (Node* newNode);
	void printList     (std::ofstream& outfile);
	void listToBtree   (std::ofstream& outfile);
};

void LinkedList::insertionSort(Node* newNode)
{	
	//Step 2.5
	Node* walker = listHead;
	
	//Step 2.6 - 2.7
	while(walker->next != NULL && walker->next->prob < newNode->prob) 
	{
		walker = walker->next;
	}
	
	//Step 2.8
	newNode->next = walker->next;
	walker->next  = newNode;
}

void LinkedList::printList(std::ofstream& outfile)
{
		Node* walker = listHead;
		while(walker != NULL)
		{
			outfile<<"("<<walker->charString<<", "<<walker->prob<<", ";
			if( walker->next != NULL )
			{
			    outfile<< walker->next->charString << ")-->";	
			}
			else{
			    outfile<< "NULL" << ")-->NULLL";
			}
			walker = walker->next;
		}
		outfile<<endl;
}

void LinkedList::listToBtree(std::ofstream& outfile)
{
	while(listHead->next->next != NULL){
		//Step 3.2:
		Node* newNode  	    = new Node();
		newNode->charString = listHead->next->charString + listHead->next->next->charString;
		newNode->prob       = listHead->next->prob + listHead->next->next->prob;
		newNode->left       = listHead->next;
		newNode->right      = listHead->next->next;
		listHead->next      = listHead->next->next->next;
	
		//Step 3.3
		Node* walker = listHead;
	
		//Step 3.4
		while( walker->next != NULL && walker->next->prob < newNode->prob)
		{
			walker = walker->next;
		} //Step 3.5

		//Step 3.6
		newNode->next =  walker->next;
   		walker->next  = newNode;

		//Step 3.7
		printList(outfile);


	}//Step 3.8
}

class BinaryTree 
{
	public:
	Node* root = new Node();
};

int main(int argc, char* argv[]) 
{
	//Step 2.0
	string inFilename   = (string)argv[1] + ".txt";
	string outFilename1 = (string)argv[2] + ".txt";
	string outFilename2 = (string)argv[3] + ".txt";
	
	ifstream inFile (inFilename);
	ofstream oFile1 (outFilename1);
	ofstream oFile2 (outFilename2);
		
 	
	LinkedList ll;
	ll.listHead->charString = "dummy";	
		
	//int count = 0;
	//oFile1<<"Iteration "<<count<<": listHead--> ";
	//ll.printList(oFile1);	
	
	while(inFile)
	{
		//Step 2.2 - 2.4
		Node* temp = new Node();
		inFile>>temp->charString;
		inFile>>temp->prob;
		
		//Steps 2.5 - 2.8
		ll.insertionSort(temp);
		
		//count+=1;
		//oFile1<<"Iteration "<<count<<": listHead-->";
		//ll.printList(oFile1);						
	}//Step 2.9
	
	//Step 2.10
	//ll.printList(oFile2);
	
	//Step 3.1
	ll.oldListHead       = new Node();
	ll.oldListHead->next = ll.listHead->next;
	
	//Step 3.2 - Step 3.8	
	ll.listToBtree(oFile1);	
	
	//Step 3.9
    BinaryTree bt;
    bt.root->next = ll.listHead->next;
    ll.listHead   = ll.oldListHead;
    
	inFile.close();
	oFile1.close();
	oFile2.close();	
	
	cout<<"Successs: data successfully saved to file(s). ";
	return 0;
}
