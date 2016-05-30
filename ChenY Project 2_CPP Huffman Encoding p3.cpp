/*
CSC 323/700 Spring 2015: Huffman Coding part-3 (C++)
Yan Chen
Due date: March 8, 2015
*/
#include <iomanip> 
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class Node 
{
	public:
	int prob;
	string charCode;
	string charString;
	
	Node* next;
	Node* left;
	Node* right;
	
	Node();
	Node(string s);
};

Node::Node()
{
	prob = -1;
		
	next  = NULL;
	left  = NULL;
	right = NULL;
};

Node::Node(string s)
{
	prob = -1;
	charString = s;
		
	next  = NULL;
	left  = NULL;
	right = NULL;
};


class LinkedList 
{
	public:
	Node* listHead    = new Node();
	Node* oldListHead = new Node();
	
	char*   character;
	int*    prob;
	string* code;
	int*    bits;
	int*    entropy;
	
	LinkedList();
	void HuffmanLinkedList (Node* newNode);
	void HuffmanBinaryTree (std::ofstream& outfile);
	void printEntropyTable (std::ofstream& outfile);
	void printLinkedList   (std::ofstream& outfile);
};

LinkedList::LinkedList()
{
	listHead = new Node("dummy");
};

void LinkedList::HuffmanLinkedList(Node* newNode)
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
	walker-> next = newNode;
}

void LinkedList::printLinkedList(std::ofstream& outfile)
{
	Node* walker = oldListHead;
	while( walker != NULL )
	{
		outfile<<"("<<walker->charString<<", "<<walker->prob<<", ";
		if( walker->next != NULL )
		{
		    outfile<< walker->next->charString << ")--> ";	
		}
		else{
		    outfile<< "NULL" << ")-->NULL \n";
		}
			walker = walker->next;
	}
	outfile<<endl;
}

void LinkedList::HuffmanBinaryTree(std::ofstream& outfile)
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
		newNode->next = walker->next;
   		walker ->next = newNode;

		//Step 3.7
		//printList(outfile);

	}//Step 3.8
}

void LinkedList::printEntropyTable( std::ofstream& oFile )
{
   //Size <- # of single length charStrings 		
	int size = 0;
	Node* walker = listHead;
	while( walker->next != NULL )
	{
		if( walker->next->charString.length() == 1)
		{
			size++;
			walker = walker->next;
		}
		else
		{
			walker = walker->next;
		}
	}
		
	character = new char  [size+1];
	prob      = new int   [size+1];
	code      = new string[size+1];
	bits      = new int   [size+1];
	entropy   = new int   [size+1];
	
	//each array (total of 5) <- corresponding walker data
	int count = 0;
	walker = oldListHead;
	while( walker->next != NULL )
	{
		if( walker->charString.length() == 1)
		{
			character[count] = walker->charString[0];
			prob     [count] = walker->prob;
			code     [count] = walker->charCode;
			bits     [count] = walker->charCode.length();
			entropy  [count] = walker->charCode.length() * walker->prob;
			count++;
			walker = walker->next;
		}
		else
		{
			walker = walker->next;
		}
	}
	
	//print out to file
	oFile<<"Char\t Prob \t      code \t  #bits\t entropy  \n";
	oFile<<"============================================== \n";
	 
	for(int i = 0 ; i<size; i++)
	{
	 	oFile<<character[i]<<"\t ";
		oFile<<prob     [i]<<"\t  ";
		oFile<<setw(9)<<code[i]<<"\t   ";
		oFile<<bits     [i]<<"\t  ";
		oFile<<entropy  [i]<<"\t\n";
	}	
	oFile<<endl;
} 

class BinaryTree 
{
	public:
	Node* root = new Node();	
	
	void HuffmanCode(Node* T, string code);
	
};

void BinaryTree::HuffmanCode(Node* T, string code)
{	
   //Step 1
	Node* walker = T;

   //Step 2
	if( walker == NULL ){
		return;
	}
	
   //Step 3
    else if( walker->left == NULL && walker->right == NULL){
    	walker->charCode = code;
    	return;
	}
	
   //Step  4
   	else
	{
    	HuffmanCode (walker->left, code+"0");
   		HuffmanCode (walker->right, code+"1");
	}
}


int main(int argc, char* argv[]) 
{
	//Step 2.0
	ifstream inFile (argv[1]);
	ofstream oFile1 (argv[2]);
	ofstream oFile2 (argv[3]);
		
 	
	LinkedList ll;
	ll.listHead->charString = "dummy";	
		
	//int count = 0;
	//oFile1<<"Iteration "<<count<<": listHead--> ";
	//ll.printList(oFile1);	
	Node* temp;	
	while(!inFile.eof())
	{
		//Step 2.2 - 2.4
		temp = new Node();
		inFile>>temp->charString;
		inFile>>temp->prob;
		
		//Steps 2.5 - 2.8
		ll.HuffmanLinkedList(temp);
		//count+=1;
		//oFile1<<"Iteration "<<count<<": listHead-->";
		//ll.printList(oFile1);						
	}//Step 2.9
	
	//Step 2.10
	//ll.printList(oFile2);
	
	//Step 3.1
	ll.oldListHead       = new Node("dummy");
	ll.oldListHead->next = ll.listHead->next;
	
	//Step 3.2 - Step 3.8	
	ll.HuffmanBinaryTree(oFile1);
	
	//Step 3.9
    BinaryTree bt;
    
	bt.root->next = ll.listHead->next;
    ll.listHead   = ll.oldListHead;    
    
    ll.printLinkedList(oFile1);
	bt.HuffmanCode(bt.root->next, "");
    ll.printEntropyTable(oFile1);
    ll.printLinkedList(oFile1);
    
	inFile.close();
	oFile1.close();
	oFile2.close();	
	
	cout<<"Successs: data successfully saved to file(s). ";
	return 0;
}
