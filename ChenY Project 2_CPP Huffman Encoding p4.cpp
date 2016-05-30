/*
CSC 323/700 Spring 2015: Project 4 (C++)
Yan Chen
Due date: March 30, 2015
*/
#include <iomanip> 
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class Node 
{
	public:
	float prob;
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
	
	int     numChars;
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
	Node* walker = listHead;
	while( walker != NULL )
	{
		outfile<<"("<<walker->charString<<", "<<walker->prob<<", ";
		if( walker->next != NULL )
		{
		    outfile<< walker->next->charString << ")--> ";	
		}
		else{
		    outfile<< "NULL" << ")-->NULL ";
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
		printLinkedList(outfile);

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
	
	numChars  = size;
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
	 	oFile<<character    [i]<<"\t ";
		oFile<<prob         [i]<<"\t  ";
		oFile<<setw(9)<<code[i]<<"\t   ";
		oFile<<bits         [i]<<"\t  ";
		oFile<<entropy      [i]<<"\t\n";
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


void printCharProb( string in , string out )
{
	ifstream inFile ( in );
	ofstream oFile1 ( out );
	
	float charCount = 0;
	int size = 256;
	int Hist[size]; 
	std::fill_n(Hist, size, 0);
	
	int index;
	unsigned char charString;	
	

	while( !inFile.eof() )
	{	
		inFile>>std::noskipws>>charString;
		index = (int)charString;
		Hist[index]++;
		charCount++;
	}
		
	index = 0;
	while(index <256 ){
		if( Hist[index] >0){
			if(index == 10){
				oFile1<<(char)236<<" "<<std::setprecision(2)<<(Hist[index]/charCount)*100<<endl;
			}
			else if(index == 32){
				oFile1<<(char)237<<" "<<std::setprecision(2)<<(Hist[index]/charCount)*100<<endl;
			}
			else{
				oFile1<<(char)index<<" "<<std::setprecision(2)<<(Hist[index]/charCount)*100<<endl;
			}
		}	
		index++;
	}
	
	inFile.close();
	oFile1.close();
}


int main(int argc, char* argv[]) 
{
	//create <char prob>
	printCharProb(argv[1], argv[2]); 
	
	ifstream inFile1 (argv[1]);
	ifstream inFile2 (argv[2]); //created <char prob> in argv[2]	
	ofstream oFile2  (argv[3]);
	ofstream oFile3  (argv[4]);
	ofstream oFile4  (argv[5]);
	ofstream oFile5  (argv[6]);	
	ofstream oFile6  (argv[7]);
 	
	 //creating linkedlist
	LinkedList ll;
	ll.listHead->charString = "dummy";	 
	while( !inFile2.eof() )
	{
		Node* temp = new Node();
		
		inFile2>>temp->charString;
		inFile2>>temp->prob;
		
		if(temp->prob > 0 )
			ll.HuffmanLinkedList(temp);	
	}
	inFile2.close();
	
	//print created linkedlist
	ll.printLinkedList(oFile2);
	
	
	
	ll.oldListHead       = new Node("dummy");
	ll.oldListHead->next = ll.listHead->next;
	
	//create BinaryTree and print 
	ll.HuffmanBinaryTree(oFile3);
	oFile3 .close();
    BinaryTree bt;
	bt.root->next = ll.listHead->next;
	
	//resetting listHead pointer
    ll.listHead   = ll.oldListHead;    

    //create code for each letter
	bt.HuffmanCode(bt.root->next, "");
	
	//create and print entropy table
    ll.printEntropyTable(oFile4);
    oFile4 .close();
    
	//encoding
	char input;
	while( !inFile1.eof() ){
		inFile1>>std::noskipws>>input;
		
		if( input == '\n' ){
			input = char(236);
		
		}	
		else if( input == ' ' ){
			input = char(237);
			
		}
			
		for(int i = 0; i <= ll.numChars; i++){
			if( input == ll.character[i]){
				oFile5<< ll.code[i];	

			}
		}

	}	
	inFile1.close();
	oFile5 .close();
	
	string spcCode;
	string nlCode;
	string rCode;
	for(int i = 0; i <= ll.numChars; i++){
		if ( ll.character[i] == char(236)){	
			nlCode = ll.code[i];
		}
		if ( ll.character[i] == char(237)){	
			spcCode = ll.code[i];
		}	
		
	}
	
	//decoding
	//I can't figure out why decoding outfile space after every character
	//if I remove the if and if else statement, 
	//the characters will be without space and newline but no space afterevery character
	ifstream inFile3 (argv[6]);
	string word = "";
	char in;
	while( !inFile3.eof() )
	{	
		inFile3>>in;
		word+= in;
		
		if ( word == nlCode){
			oFile6<<'\n';
			word="";
		}
		
		else if ( word == spcCode){
			oFile6<<' ';
			word="";
		}
		
		
		for(int i = 0; i <= ll.numChars; i++)
		{		
			if ( word == ll.code[i]){	
				oFile6<<ll.character[i];
				word = "";	
			}	
		}
	}
	inFile3.close();
	oFile6 .close();	
	
	cout<<"Successs: data successfully saved to file(s). ";
	return 0;
}
