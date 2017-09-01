//----------------------------------------------
//Name      : krishna Sai Anirudh Katamreddy
//SJSU ID   : 011814595
//Professor : Ronald Mak
//Course    : CMPE 180-92
//----------------------------------------------

#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
using namespace std;

double Calculation(stringstream& ss);

int main()
{
	string str;
	//Program runs until only '.' is entered in the input expression.
	while(str[0] != '.')
	{
		cout << "Expression? ";

		//reading the whole expression line entered at once.
		getline(cin,str);
		int len = str.length();
		//will proceed into calculation, if the expression entered is not '.'!
		if(str[0] != '.')
		{
			stringstream ss;
			//reading the entered expression into string stream.
			ss << str;
			//Checking for the forward and backward braces.
			int fb = 0;
			for(int i = 0; i < len; i++)
			{
				if(str[i] == '(')
				{
					fb += 1;
					//incrementing the value of 'fb' by 1 if we found any '(' in the expression.
				}
				else if(str[i] == ')')
				{
					fb -= 1;
					//decrementing the value of 'fb' by 1 if we found any ')' in the expression.
				}
			}
			// proceeding into the calculation, if the number of forward and backward braces are equal.
			if(fb == 0)
			{
				//The result of the calculation is assigned to a double type variable.
				double out = Calculation(ss);

				//Taking two highly impossible output conditions to print few common errors in the input expression.
				if(out != -0.00000134 && out != -0.00123)
				{
					cout << out << endl;
				}
				else if(out == -0.00000134)
				{
					cout << "***** Division by zero" << endl;
				}
			}
			else if(fb > 0)
			{
				cout << "***** Missing )" << endl;
			}
			else if(fb < 0)
			{
				cout << "***** Unexpected )" << endl;
			}
		}
		cout << '\n';
	}
	//Comes out of the while loop when '.' is entered as the expression and prints 'Done!' .
	if(str[0] == '.')
	{
		cout << "Done!";
	}
	return 0;
}

double Calculation(stringstream& ss)
{
	//reading spaces if any at the beginning of the expression & when ever the Calculation function is called.
	ss >> ws;
	char op;
	char ch = ss.peek();
	//If first character is a digit, go to the loop.
	if(isdigit(ch))
	{
		double f;
		ss >> ws;
		//reading the double type from the string stream
		ss >> f;
		ss >> ws;
		//reading a single character and assigning it to a char type 'op'
		//if the input expression reaches end of the file, return f;
		if(ss.eof() == 1)
		{
			return f;
		}
		ss >> op;
		ss >> ws;
		double div;
		double n1, n2;
		//checking for invalid factors!
		if(op == '+'|| op == '-'|| op == '*'|| op == '/')
		{
			char opn = ss.peek();
			//checking for +,- after the current operator 'op'.
			if(opn == '+' || opn == '-')
			{
				cout << "***** Invalid factor" << endl;
				return -0.00123;
			}
		}
		//Depending on the 'op' value, doing different operations.
		switch(op)
		{
		case '+': return f + Calculation(ss); break;            //Addition
		case '-': return f - Calculation(ss); break;            //Subtraction
		case '*': return f * Calculation(ss); break;            //Multiplication
		case '/':                                               //Division
			n1 = f;
			n2 = Calculation(ss);

			//If the denominator is zero, output will not be returned
			//and comment printing will be done as written in int main().
			if(n2 != 0)
			{
				div = n1 / n2;
				return div;
			}
			else
			{
				return -0.00000134;
			}
			break;

		case '^': return pow(f, Calculation(ss)); break;
		case ')': return f; break;
		case '=': return f; break;
		default:
			/*
			 *if the 'op' reads some other character, then default case is activated.
			 *in this the unexpected 'op' is printed and,
			 *the output calculated value should not be printed.
			 *for that I am returning a highly impossible value,
			 *if the value matches to the output in int main(),
			 *No output will be printed.
			 */
			cout << "***** Unexpected " << op << endl;
			return -0.00123;
			break;
		}
	}
	else if(ch == '(')
	{
		ss >> ch;
		ss >> ws;
		/*
		 *if the char is '(', that character is read and then, the expression inside braces '()' is read by
		 *the Calculation(ss) function and the returned value is assigned to a double type variable named 'ins'.
		 */
		double ins = Calculation(ss);
		/*
		 * after 'ins' is equated to the value inside the braces, 'ins' is not returned directly,
		 * but checks if any other expression is present,
		 * if present! the calculation is continued till the end of the string.
		 * or till the last character in the string is '='!
		 */
		if(ins == -0.00123)
		{
			return -0.00123;
		}
		ch = ss.peek();
		//checking for the closing braces ')'
		if(ss.eof() == 0 && ch != '=')
		{
			while(ch == ')')
			{
				ss >> ch;
				ss >> ws;
				ch = ss.peek();
			}
		}
		//On reaching the end of the string stream, returning the value in 'ins'!
		if(ch == '=' || ss.eof() == 1)
		{
			return ins;
		}
		//if not the end of the stream, continuing the calcultion!
		else
		{
			char op;
			ss >> ws;
			ss >> op;
			ss >> ws;

			switch(op)
			{
			case '+': return ins + Calculation(ss); break;
			case '-': return ins - Calculation(ss); break;
			case '*': return ins * Calculation(ss); break;
			case '/': return ins / Calculation(ss); break;
			case ')': return ins; break;
			case '=': return ins; break;
			default:
				cout << "***** Unexpected " << op << endl;
				return -0.00123;
				break;
			}
		}
	}
	/*if the first character is '+' or '-',
	 *the sign's are considered & multiplied with the remaining expression.
	 */
	else if(ch == '+' || ch == '-')
	{
		char nch;
		ss >> ch;

		nch = ss.peek();
		if(ch == '+')
		{
			if(isdigit(nch) || nch == '(')
			{
				return 1 * Calculation(ss);
			}
			else
			{
				cout << "***** Invalid factor" << endl;
				return -0.00123;
			}
		}
		else if(ch == '-')
		{
			if(isdigit(nch) || nch == '(')
			{
				return -1 * Calculation(ss);
			}
			else
			{
				cout << "***** Invalid factor" << endl;
				return -0.00123;
			}
		}
	}
	else
	{
		cout << "Expression is not valid" << endl;
		return -0.00123;
	}
}

