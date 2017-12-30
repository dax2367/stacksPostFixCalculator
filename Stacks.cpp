// Program:		Postfix Calculator/ Stacks
// Author:		Holly Eaton
// Description:	Program which takes user input 'infix' converts it to postfix and outputs the results.

#include "EatonStacks.h"

using namespace std;

/*-------------------------------------------------------------------------------------------------
Function name:	PostfixCalculator
Description:	Main function that calls the other functions and prints out an error so I know
				where it failed
Arguments:		None
Return value:	bool - True if no errors. False if there was an error.
-------------------------------------------------------------------------------------------------*/
bool PostfixCalc::PostfixCalculator()
{
	if (doGetInfix())
	{
		if	(doVerifyAndRemoveWhiteSpace())
		{
			if (doPrintInfix())
			{
				if (doConvertInfixToPostfix())
				{
					if (doEvaluatePostfixAndPrint())
					{
						//All functions returned true YAY!
						return true;
					}
					else
					{
						/*Something broke message.. going to comment out cout statement
							but leave it in so it is eaiser to troubleshoot and see which curly braces
							belong where when making changes later.*/
						//cout << "Something in doEvaluatePostfixAndPrint broke" << endl << endl;
						return false;
					}
				}
				else
				{
					/*Something broke message.. going to comment out cout statement
						but leave it in so it is eaiser to troubleshoot and see which curly braces
						belong where when making changes later.*/
					//cout << "Something in doConvertInfixToPostfix broke" << endl << endl;
					return false;
				}
			}
			else
			{
				/*Something broke message.. going to comment out cout statement
					but leave it in so it is eaiser to troubleshoot and see which curly braces
					belong where when making changes later.*/
				/*cout << "Something in doPrintInfix broke" << endl << endl;*/
				return false;
			}
		}
		else 
		{
				/*Something broke message.. going to comment out cout statement
					but leave it in so it is eaiser to troubleshoot and see which curly braces
					belong where when making changes later.*/
				/*cout << "Something in doVerifyAndRemoveWhiteSpace broke" << endl << endl;*/
			return false;			
		}
	}
	else
	{
			/*Something broke message.. going to comment out cout statement
				but leave it in so it is eaiser to troubleshoot and see which curly braces
				belong where when making changes later.*/
		/*cout << "Something in doGetInfix broke" << endl << endl;*/
		return false;		
	}
}

/*-------------------------------------------------------------------------------------------------
Function name:	doGetInfix
Description:	Prompt user for the infix expression
Arguments:		None
Return value:	bool - True if something was entered. False if no expression was entered.
-------------------------------------------------------------------------------------------------*/
bool PostfixCalc::doGetInfix()
{
	cout << endl << endl;//Put some space between this and last time better spacing
	cout << "Please enter an infix expression (for example. 2+2*8... No implied multiplaction allowed):" << endl;
	cout << ">";
	getline(cin,mStrInfix);

	if (mStrInfix.size() != 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*-------------------------------------------------------------------------------------------------
Function name:	doVerifyAndRemoveWhiteSpace
Description:	Verify there are no invalid characters and remove all whitespace
Arguments:		None
Return value:	bool - True if expression was good. False if there was an invalid character.
-------------------------------------------------------------------------------------------------*/
bool PostfixCalc::doVerifyAndRemoveWhiteSpace()
{
	/*if(mStrInfix.size() == 0)
		return false;*/

	string tempInfixString=" ";

	for (int i = 0;  i < mStrInfix.size(); i++)
	{
		//Check for 0 and whitespace don't use it
		if (mStrInfix[i] == ' ' || mStrInfix[i] == 0)
		{			
			continue;
		}

		//Check for math characters
		if (mStrInfix[i] == '(' || mStrInfix[i] == ')' || mStrInfix[i] == '^' ||
			mStrInfix[i] == '*' || mStrInfix[i] == '/' || mStrInfix[i] == '+' || mStrInfix[i] == '-' ||
			(mStrInfix[i] >= '0' && mStrInfix[i] <= '9'))
		{
			tempInfixString += mStrInfix[i];
		}
		else
		{
			//There is an invalid character
			cout << endl << "Sorry those are invalid characters." << endl;
			return false;
		}
	}

	//Check if there is anyting there
	if (tempInfixString.size() != 0)
	{
		//Replace the member infix string with a temp string
		mStrInfix = tempInfixString;
		return true;
	}
	else
	{
		//The expression is empty stop
		cout << endl << "There are no characters. You will have to start over" << endl;
		return false;
	}
}

/*-------------------------------------------------------------------------------------------------
Function name:	doPrintInfix
Description:	Prints the infix expression
Arguments:		None
Return value:	bool - True if expression was there. False if there was no expression.
-------------------------------------------------------------------------------------------------*/
bool PostfixCalc::doPrintInfix()
{
	//Check to make sure there are characters present
	if (mStrInfix.size() != 0)
	{
		//Print out the infix
		cout << endl << "Infix: " << mStrInfix << endl;
		return true;
	}
	else
	{
		//The expression is empty so stop
		cout << endl << "No expression to print." << endl;
		return false;
	}
}

/*-------------------------------------------------------------------------------------------------
Function name:	doConvertInfixToPostfix
Description:	Converts the infix expression to a postfix expression and prints it out
Arguments:		None
Return value:	bool - True if conversion was successful. False if conversion failed.
-------------------------------------------------------------------------------------------------*/
bool PostfixCalc::doConvertInfixToPostfix()
{
	stack<char> infixToPostfixStack;

	//Go through each item of the infix
	for (int i = 0; i < mStrInfix.size(); i++)
	{
		if (mStrInfix[i] >= '0' && mStrInfix[i] <= '9')//Numbers
		{
			mStrPostfix += mStrInfix[i];//Append to postfix string
		}
		else if (mStrInfix[i] == '(')//Left parenthesis
		{
			infixToPostfixStack.push(mStrInfix[i]);//Add to stack
		}
		else if (mStrInfix[i] == '^' || mStrInfix[i] == '*' || mStrInfix[i] == '/' ||
			mStrInfix[i] == '+' || mStrInfix[i] == '-')//Is it one of the operators

		{
			while (!infixToPostfixStack.empty() &&
				infixToPostfixStack.top() != '(' &&
				doCheckIsOp1GrtrOrEqlToOp2(infixToPostfixStack.top(),mStrInfix[i]))//Not empty and top has precedence
			{
				mStrPostfix += infixToPostfixStack.top();//Append to postfix string
				infixToPostfixStack.pop();//Remove from stack
			}
			infixToPostfixStack.push(mStrInfix[i]);//Add to stack
		}
		else if (mStrInfix[i] == ')')//Right parenthesis
		{
			while (!infixToPostfixStack.empty() &&
				infixToPostfixStack.top() != '(')
			{
				mStrPostfix += infixToPostfixStack.top();//Append to postfix string
				infixToPostfixStack.pop();//Remove from stack
			}
			if (!infixToPostfixStack.empty())
			{
				if (!infixToPostfixStack.top() != '(')
					mStrPostfix += infixToPostfixStack.top();//Append to postfix string
				infixToPostfixStack.pop();//Remove from stack			
			}
		}
	}

	while (!infixToPostfixStack.empty())
	{
		if (infixToPostfixStack.top() == '(')
		{
			cout << endl << "Unmatched parentheses." << endl;
			mStrPostfix = " ";
			return false;//There was a left ( but no right )
		}

		mStrPostfix += infixToPostfixStack.top();//Append to postfix string
		infixToPostfixStack.pop();//Remove from stack
	}

	//Print
	cout << endl << "Postfix: " << mStrPostfix << endl;
	return true;
}

/*-------------------------------------------------------------------------------------------------
Function name:	doEvaluatePostfixAndPrint
Description:	Evaluates the postfix expression and prints result
Arguments:		None
Return value:	bool - True if evaluation was successful, False if there was an error
-------------------------------------------------------------------------------------------------*/
bool PostfixCalc::doEvaluatePostfixAndPrint()
{
	stack<double> evalPostfixStack;
	double num1;
	double num2;
	double result;

	//Go through infix
	for (int i = 0; i < mStrPostfix.size(); i++)
	{
		if (mStrPostfix[i] >= '0' && mStrPostfix[i] <= '9')//Numbers
		{
			evalPostfixStack.push(mStrPostfix[i]-'0');//Convert to real number add to stack 
		}
		else if (mStrPostfix[i] == '^' ||//Operators
			mStrPostfix[i] == '*' ||
			mStrPostfix[i] == '/' ||
			mStrPostfix[i] == '+' ||
			mStrPostfix[i] == '-')
		{
			
			if (!evalPostfixStack.empty())//if not empty
			{
				num1 = evalPostfixStack.top();//Store in num1
				evalPostfixStack.pop();//Remove from stack

				if (!evalPostfixStack.empty())//if not empty still
				{
					num2 = evalPostfixStack.top();//Store for use
					evalPostfixStack.pop();//Remove from stack

					//Determine which operator, then do math with that operator
					if (mStrPostfix[i] == '+')
						evalPostfixStack.push(num2 + num1);
					else if (mStrPostfix[i] == '-')
						evalPostfixStack.push(num2 - num1);
					else if (mStrPostfix[i] == '^')
						evalPostfixStack.push(pow(num2, num1));
					else if (mStrPostfix[i] == '*')
						evalPostfixStack.push(num2 * num1);
					else if (mStrPostfix[i] == '/')
					{
						if (num1 !=0)
						{
							evalPostfixStack.push(num2 / num1);
						}
						else
						{
							cout << "No division by zero." << endl;
							mStrPostfix = " ";
							return false;
						}
					}
				}
					else
					{
						cout << endl << "Invalid postfix expression." << endl;
						mStrPostfix = " ";
						return false;
					}
				}
				else
				{
					cout << endl << "Invalid postfix expression." << endl;
					mStrPostfix = " ";
					return false;
				}
			}
		}

		//Check if there is anyting in the stack
		if (!evalPostfixStack.empty())
		{
			result = evalPostfixStack.top();//Store for use
			evalPostfixStack.pop();//Remove from stack
			cout << endl << "Result: "  << result << endl;
			mStrPostfix = " ";
			return true;
		}
		else
		{
			cout << endl << "Invalid postfix expression." << endl;
			mStrPostfix = " ";
			return false;
		}
}

/*-------------------------------------------------------------------------------------------------
Function name:	doCheckIsOp1GrtrOrEqlToOp2
Description:	Determines if operator 1 is greater than or equal to operator 2 in precedence
Arguments:		None
Return value:	bool - True if op1 is >= op2, False if op1 is < op2
-------------------------------------------------------------------------------------------------*/
bool PostfixCalc::doCheckIsOp1GrtrOrEqlToOp2(char op1, char op2)
{
	int op1Precedence;
	int op2Precedence;

	if (op1 == '+' || op1 == '-')
		op1Precedence = 0;
	if (op2 == '+' || op2 == '-')
		op2Precedence = 0;

	if (op1 == '*' || op1 == '/')
		op1Precedence = 1;
	if (op2 == '*' || op2 == '/')
		op2Precedence = 1;

	if (op1 == '^')
		op1Precedence = 2;
	if (op2 == '^')
		op2Precedence = 2;

	if (op1 == '(' || op1 == ')')
		op1Precedence = 3;
	if (op2 == '(' || op2 == ')')
		op2Precedence = 3;

	if (op1Precedence >= op2Precedence)
	{
		return true;
	}
	else
	{
		return false;
	}
}