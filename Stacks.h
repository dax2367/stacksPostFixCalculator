// Program:		Postfix Calculator/ Stacks
// Author:		Holly Eaton
// Description:	Program which takes user input 'infix' converts it to postfix and outputs the results.

#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <thread>
#include <chrono>

#ifndef POSTFIXCALC_H_
#define POSTFIXCALC_H_

using namespace std;

class PostfixCalc
{
public:
	bool PostfixCalculator();

private:
	string mStrInfix;
	string mStrPostfix;

	bool doGetInfix();
	bool doVerifyAndRemoveWhiteSpace();
	bool doPrintInfix();
	bool doConvertInfixToPostfix();
	bool doEvaluatePostfixAndPrint();

	//Is operator 1 greater than or equal to operator 2
	bool doCheckIsOp1GrtrOrEqlToOp2(char op1, char op2);

};

#endif