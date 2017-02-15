#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <random>
#include <time.h>

using namespace std;

struct linkedListElement
{
	int data;
	linkedListElement* nextElement; //This will be null if at end of list
};

typedef linkedListElement* linkedListElementPointer;
//TODO: Add arguments for a .txt file input which will alter the population of the linked list

bool populateList(string option, int n, linkedListElementPointer &nextElementPointer);
linkedListElementPointer deleteElements(int searchInt, linkedListElementPointer accessPointer);
void printList(linkedListElementPointer accessPointer);
void deleteList(linkedListElementPointer &nextElementPointer);

int main()
{
	string option = "restart";
	cout << "Welcome to linkedList - designed by Waleed El-Geresy\n";
	do
	{
		if(option=="restart")
		{
			linkedListElementPointer initialPointer = NULL; //We create a pointer that will be used as the end of the list
			int n;
			cout << "How many elements would you like this LL to have?";
			cin >> n;
			
			bool Populated = false;
			
			while(!Populated) //Populated becomes true once population occurs without error
			{
				cout << "Populate randomly (y/n)? ";
				cin >> option;
				
				Populated = populateList(option,n,initialPointer);
			}
			
			cout << "Enter the values you wish to delete from the linked list: ";
			int searchInt;
			cin >> searchInt;
			
			int numberCheck = 1; //The first instance of int
			
			initialPointer = deleteElements(searchInt,initialPointer);
			
			cout << "Here is the new linked list: \n";
			
			printList(initialPointer);
			
			deleteList(initialPointer);
		}
		cout << "Please enter 'exit' to continue, 'restart' to go again: ";
		cin >> option;
	}
	while(option!="exit");
	cout << "Thank you for using this program!";
}

bool populateList(string option, int n, linkedListElementPointer& nextElementPointer)
{
	if(option=="y"||n>10)
		{
			if(n>10) cout << "Your list will be automatically populated randomly due to its size... \n";
			int maxValue;
			int minValue;
			int jumps;
			cout << "Enter the max random value (integer): ";
			cin >> maxValue;
			cout << "Enter the min random value (integer): ";
			cin >> minValue;
			cout << "Enter the spacing between these (integer): ";
			cin >> jumps;
			if(jumps>maxValue||minValue>maxValue||jumps<1||minValue<0)
			{
				cout << "These parameters are not compatible, please try again...\n";
				return false;
			}
			else
			{
				maxValue = maxValue + (((maxValue-minValue)%jumps)); //Sanity check to ensure that we have number of jumps that eventually reaches maximum (can't have 3->4 with jumps 2 : this will change to 3->5)
				cout << "Running with the following parameters... (Your MaxValue may have been changed)\n";
				cout << "MaxValue: " << maxValue << "\n";
				cout << "MinValue: " << minValue << "\n";
				cout << "Jumps: " << jumps << "\n";
				for(int i=0; i<n; i++) //Less than n because the list is indexed from 0 to n-1 (n elements)
				//Note that this linked list is populated in reverse order
				{
					linkedListElementPointer l = new linkedListElement;
					l->nextElement = nextElementPointer; //Initialised to NULL, and then repetitively set to the current element
					cout << "Data for element " << n-(i) << " is: ";
					srand (time(NULL));
					int random =  rand() % (1+(maxValue-(minValue))/jumps); //The +1 is to add the possibility for reaching the maximum
					random = minValue + (random)*jumps; //Modulo to make the maximum possible value equal to rand
					//Scaling and descaling by jumps in the above makes the jumps work
					cout << random << "\n";
					l->data = random;
					nextElementPointer = l;
					Sleep(1000); //Wait for a second to change the seed
				}
			}
		}
				
	if(n<0)
	{
		return false;
	}
	
	if(option=="n"&&n<=10)
	{
		for(int i=0; i<n; i++) //Less than n because the list is indexed from 0 to n-1 (n elements)
		//Note that this linked list is populated in reverse order
		{
			linkedListElementPointer l = new linkedListElement;
			l->nextElement = nextElementPointer; //Initialised to NULL, and then repetitively set to the current element
			cout << "Data for element " << n-(i) << ": ";
			cin >> l->data;
			nextElementPointer = l;
		}
	}
	
	return true;
}

linkedListElementPointer deleteElements(int searchInt, linkedListElementPointer accessPointer) //set access pointer to the first element of the list to initialise
{
	linkedListElementPointer prevElement = accessPointer;
	int numberCheck = 1;
	
	bool foundFirstPointer = false;
	
	linkedListElementPointer headerPointer = NULL;
	
	while(accessPointer!=NULL) //Sequentially searches through the linked list from start to end and outputs the numbers of elements which contain the data (in the reverse order to that entered)
	{
		//cout << "Checking element " << numberCheck << ", data is: " << accessPointer->data << "\n";
		if(accessPointer->data==searchInt)
		{
			cout << "FOUND! Will delete element number " << numberCheck << "\n";
			linkedListElementPointer nextElementPTR = accessPointer->nextElement; //NextElement is the element after accessPointer
			if(foundFirstPointer) //to ensure we don't access this until it is ACTUALLY the previous pointer and not just the initial now deleted pointer
			{
			prevElement->nextElement = nextElementPTR; //The previous element is the element before it
			}
			delete accessPointer; //Delete the current pointer
			accessPointer = nextElementPTR; //The access pointer will then point to the next element
		}
		else //otherwise the prev pointer will continue to point to the same place and access pointer has already been increased
		{
			if(!foundFirstPointer)
			{
				headerPointer = accessPointer; //This will give us the first non-deleted element
				foundFirstPointer = true;
			}
			prevElement = accessPointer;
			accessPointer = accessPointer->nextElement;
		}
		numberCheck++;
	}
	
	return headerPointer;
}

void printList(linkedListElementPointer accessPointer) //the pointer passed must be the first element
{
	int numberCheck = 1;
	while(accessPointer!=NULL)
	{
		cout << numberCheck << ": " << accessPointer->data << endl;
		accessPointer = accessPointer->nextElement;
		numberCheck++;
	}
	return;
}

void deleteList(linkedListElementPointer &nextElementPointer)
{
	cout << "Please wait... Freeing memory space occupied by the linked list...\n";
		while(nextElementPointer!=NULL)
		{
			linkedListElementPointer tmpPointer = nextElementPointer->nextElement; //Must store the value of the address of the next element in a temporary variable before it is deleted
			delete nextElementPointer;
			nextElementPointer = tmpPointer;
		}
		cout << "Complete!\n";
}