
/*
	Name: TuringMachine.h
	Author: Mustafa Anil Tuncel
	Date: 28.05.14 22:43
	Description: Header file for deterministic Turing Machine
	Contact Info: tuncel.manil@gmail.com
	LinkedIn: tr.linkedin.com/in/aniltuncel/
*/



#include <iostream>
#define NULL_NODE '_'
#ifndef TAPE_NODE
#define TAPE_NODE

struct TapeNode //TapeNode structure for the tape
{
	char data;
	TapeNode* left;
	TapeNode* right;
};

#endif // TAPE_NODE

#ifndef TURING_MACHINE
#define TURING_MACHINE

class TuringMachine 
{
	private:
		// ------------privata data--------------------
		
		TapeNode* iterator;
		TapeNode* first;
		
		
		// ----------- private methods ----------------
		void instantiate (char*); //fills the turing machine
		void moveLeft (); // moves the iterator to left
		void moveRight (); // moves the iterator to right
		void replace(char); //replaces the current element of the tape
		char currentData(); // returns the data of the current element of the tape
		void refresh(); // it moves the iterator to the first
		bool palindromeAutomata(); // recursive function checks whether the input string on the turing machine is a palindrome or not
		void destroy(TapeNode*&); //destroys the turing machine

		

	public:
		//----------------- public methods--------------------
		TuringMachine() //empty constructor
		{
			first = iterator = NULL;
		}
		
		TuringMachine(char* s) // constructor with argument
		{
			instantiate(s);
		}

		bool isPalindrome() // first it moves iterator to the first place and then it runs the palindromeAutomata function.
		{
			refresh();
			return palindromeAutomata();
		}
		
		~TuringMachine() // it sets the memory free.
		{
			destroy(first); 
		}
		

		
	

	
};

#endif // TURING_MACHINE

void TuringMachine::instantiate(char* s) //fills the tape with the input string
{
	TapeNode* q;
	iterator = new TapeNode;
	iterator -> left = iterator -> right = NULL;
	iterator -> data = NULL_NODE;
	first = iterator;
	
	for (int i = 0; s[i] != '\0'; ++i)
	{
		q = new TapeNode;
		q -> left = iterator;
		q -> right = NULL;
		q -> data = s[i];
		iterator -> right = q;
		iterator = q;
		
	}
	
	q -> right = new TapeNode;
	q -> right -> left = q;
	q -> right -> right = NULL;
	q -> right -> data = NULL_NODE;
	
	iterator = first;
}

bool TuringMachine::palindromeAutomata() 
{
	char ch = currentData();
	replace(NULL_NODE);
	
	if (iterator -> right -> data == NULL || iterator -> right -> data == NULL_NODE)  //end condition of the recursion
	{
		return true;
	}
	
	moveRight();
	
	while (currentData() != NULL_NODE)
	{
		moveRight();
	}
	
	moveLeft();
	
	if (currentData() == ch) //continue
	{
		replace(NULL_NODE);
		moveLeft();
		
		
		
		while (currentData() != NULL_NODE)
		{
			moveLeft();
			
		}
		
		moveRight();
		palindromeAutomata();  

	}
	
	else
	{
		return false;
	}
}

void TuringMachine::destroy(TapeNode*& p) //destroys the turing machine
{
	if (p -> data != NULL_NODE)
	{
		destroy(p->right);
		destroy(p->left);
		delete p;
		p = NULL;
	}
	else
		delete p;
}

void TuringMachine::replace (char state2) //replace
{
		iterator -> data = state2;
}

char TuringMachine::currentData() // returns the data of the current element
{
	return iterator -> data;
}

void TuringMachine::moveRight() //moves iterator to right
{
	iterator = iterator -> right;
}

void TuringMachine::moveLeft() //moves iterator to left
{
	iterator = iterator -> left;
}

void TuringMachine::refresh() // moves iterator to the first place
{
	iterator = first -> right;
}

