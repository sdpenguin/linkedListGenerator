#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>

using namespace std;

struct linkedListElement
{
	int data;
	linkedListElement* nextElement; //This will be null if at end of list
};

int main()
{
	string option = "restart";
	cout << "Welcome to linkedList - designed by Waleed El-Geresy\n";
	do
	{
		if(option=="restart")
		{
			linkedListElement* nextElementPointer = NULL; //We create a pointer that will be used as the end of the list
			int n,el;
			cout << "How many elements would you like this LL to have? ";
			cin >> n;
			for(int i=0, j=0; i<n; i++,j++) //Less than n because the list is indexed from 0 to n-1 (n elements)
			{
				linkedListElement* l = new linkedListElement;
				l->nextElement = nextElementPointer; //Initialised to NULL, and then repetitively set to the current element
				cout << "Data for element " << i+1 << ": ";
				cin >> el; //TEST this to see whether you can simply replace el with l->data?
				l->data = el;
				nextElementPointer = l;
			}
		}
		cout << "Please enter 'exit' to continue, 'restart' to go again: ";
		cin >> option;
	}
	while(option!="exit");
	cout << "Thank you for using this program!";
}