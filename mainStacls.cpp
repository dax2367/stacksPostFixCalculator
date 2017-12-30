// Program:		Postfix Calculator
// Author:		Holly Eaton
// Description:	Program which takes user input 'infix' converts it to postfix and outputs the results.

#include "EatonStacks.h"

using namespace std;

void main()
{
	//Create PostfixCalc instance
	PostfixCalc calc;
	char choice;

	while (true)
	{
		cout << "Use postfix calculator? (y/n)" << endl << ">";
		cin >> choice;
		cin.ignore();

		while (tolower(choice) != 'y' && tolower(choice) != 'n')
		{
			cout << endl << "Oops! y or no only Try again..." << endl;
			cout << "Use postfix calculator? (y/n)" << endl << ">";
			cin >> choice;
			cin.ignore();
		}

		if (tolower(choice) == 'y')
		{
			calc.PostfixCalculator();
			cout << endl << endl;
		}
		else
		{
			cout << endl << "Thanks for trying the postfix calculator...";
			this_thread::sleep_for(chrono::seconds(1));
			break;
		}
	}
}