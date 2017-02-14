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

int main()
{
	string option = "restart";
	cout << "Welcome to linkedList - designed by Waleed El-Geresy\n";
	do
	{
		if(option=="restart")
		{
			linkedListElement* nextElementPointer = NULL; //We create a pointer that will be used as the end of the list
			int n;
			cout << "How many elements would you like this LL to have? ";
			cin >> n;
			
			while(option!="y"&&option!="n") //Checks an appropriate selection has been made
			{
				cout << "Would you like to populate this linked list randomly (y/n)? Your choice will automatically be overridden for list sizes greater than 10: ";
				cin >> option;
				
				if(option=="y"||n>10)
				{
					int maxValue;
					int minValue;
					int jumps;
					cout << "Please enter the maximum value you would like the data to take (integer): ";
					cin >> maxValue;
					cout << "Please enter the minimum value you would like the data to take (integer): ";
					cin >> minValue;
					cout << "Please enter the required spacing you would like (just enter 1 for a random range in all numbers (integer): ";
					cin >> jumps;
					if(jumps>maxValue||minValue>maxValue)
					{
						cout << "These parameters are not compatible, please try again...\n";
						option="NOT VALID";
					}
					else
					{
						maxValue = maxValue + (jumps-((maxValue-minValue)%jumps)); //Sanity check to ensure that we have number of jumps that eventually reaches maximum (can't have 3->4 with jumps 2 : this will change to 3->5)
						cout << "Running with the following parameters... (Your MaxValue may have been changed)\n";
						cout << "MaxValue: " << maxValue << "\n";
						cout << "MinValue: " << minValue << "\n";
						cout << "Jumps: " << jumps << "\n";
						for(int i=0; i<n; i++) //Less than n because the list is indexed from 0 to n-1 (n elements)
						//Note that this linked list is populated in reverse order
						{
							linkedListElement* l = new linkedListElement;
							l->nextElement = nextElementPointer; //Initialised to NULL, and then repetitively set to the current element
							cout << "Data for element " << i+1 << " is: ";
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
				
				if(option=="n"&&n<=10)
				{
					for(int i=0; i<n; i++) //Less than n because the list is indexed from 0 to n-1 (n elements)
					//Note that this linked list is populated in reverse order
					{
						linkedListElement* l = new linkedListElement;
						l->nextElement = nextElementPointer; //Initialised to NULL, and then repetitively set to the current element
						cout << "Data for element " << i+1 << ": ";
						cin >> l->data;
						nextElementPointer = l;
					}
				}
			}
			
			linkedListElement* accessPointer = nextElementPointer; //Sets this to point to the first element in the linked list
			
			cout << "Enter a number to search for in the linked list, and we will show the elements that contain it: ";
			int searchInt;
			cin >> searchInt;
			
			int numberCheck = 1; //The first instance of int
			
			while(accessPointer!=NULL) //Sequentially searches through the linked list from start to end and outputs the numbers of elements which contain the data (in the reverse order to that entered)
			{
				cout << "Checking element " << numberCheck << ", data is: " << accessPointer->data << "\n";
				if(accessPointer->data==searchInt)
				{
					cout << "FOUND! In element number " << numberCheck << "\n";
				}
				numberCheck++;
				accessPointer = accessPointer->nextElement;
			}
			
			cout << "Please wait... Freeing memory space occupied by the linked list...\n";
			while(nextElementPointer!=NULL)
			{
				linkedListElement* tmpPointer = nextElementPointer->nextElement; //Must store the value of the address of the next element in a temporary variable before it is deleted
				delete nextElementPointer;
				nextElementPointer = tmpPointer;
			}
			cout << "Complete!\n";
		}
		cout << "Please enter 'exit' to continue, 'restart' to go again: ";
		cin >> option;
	}
	while(option!="exit");
	cout << "Thank you for using this program!";
}