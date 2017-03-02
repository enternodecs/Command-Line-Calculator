#include "Polynomial.h"
#include <iostream>
#include <string>
#include <cctype>
#include <utility>
#define DEBUG

//typedef string (*CalcFunc)(string); map<string, CalcFunc>
using namespace std;

int getcmd(string& s);

//Function declarations
string expression_simplify(string s);
string variable_define(string s);
string polynomial_condense(string s);
string polynomial_divide(string s);
string polynomial_factor(string s);
Polynomial operator*(const Polynomial &poly, const pair<int, double> &p);

enum Commands {
	invalid,
	simplify,
	define,
	poly_condense,
	poly_divide,
	poly_factor,
	close,
	help
};

int main() {
	string s;
	while (getline(cin, s)) {
		if (s.empty())
			continue;
		try {
			switch (int i = getcmd(s)) {
			case simplify:
				cout << expression_simplify(s) << endl;
				break;
			case define:
				cout << variable_define(s) << endl;
				break;
			case poly_condense:
				cout << polynomial_condense(s) << endl;
				break;
			case poly_divide:
				cout << polynomial_divide(s) << endl;
				break;
			case poly_factor:
				cout << polynomial_factor(s) << endl;
				break;
			case close:
				return 0;
				break;
			case help:
				cout << "Avalible commands: \nsimplify [expression]\ndefine [letter] [number]" << endl;
				break;
			case invalid:
				cout << "Invalid command." << endl;
			}
		}
		catch (exception err){
			cout << err.what() << endl;
		};
	}
}

int getcmd(string& s) {
	string::iterator iter = s.begin();
	string sub("");
	int count = 0;
	//Make the entire string lowercase
	for (string::iterator i = iter; i != s.end(); i++)
		tolower(*i);
	//Find the command
	for (; iter != s.end() && !isspace(*iter); ++iter) {
		sub += *iter;
	}
	//Don't include the space in the rest
	if (iter != s.end())
		++iter;
	//Find the rest
	string temp("");
	for (; iter != s.end(); ++iter) {
		temp += *iter;
	}
	//Pass only the arguments to the working functions
	s = temp;
	if (sub == "simplify") return simplify;
	else if (sub == "define") return define;
	else if (sub == "poly_condense") return poly_condense;
	else if (sub == "poly_divide") return poly_divide;
	else if (sub == "poly_factor") return poly_factor;
	else if (sub == "exit") return close;
	else if (sub == "help") return help;
	else return invalid;
}

string expression_simplify(string s) {
	cout << "Simplify command has been executed" << endl;
	return s;
}

string variable_define(string s) {
	cout << "Define command has been executed" << endl;
	return s;
}

string polynomial_condense(string s) {
	cout << "Condense Polynomial command has been executed" << endl;
	Polynomial p(s);
	return p.get();
}

string polynomial_divide(string s) {
	cout << "Divide Polynomials command has been executed" << endl;
	string dividend(""), divisor("");
	string::iterator iter = s.begin();
	if (iter == s.end()) throw exception("No arguments provided to polynomial_divide!");
	if (*iter == '/') throw exception("Dividend not provided to polynomial_divide!");
	while (iter != s.end() && *iter != '/') {
		dividend += *iter;
		iter++;
	}
	++iter;
	while (iter != s.end()) {
		divisor += *iter;
		iter++;
	}
	Polynomial poly_dividend(dividend), poly_divisor(divisor), answer("0"), temp("0");

	int exp = 0;
	double co = 0;
	string remainder;
	//Perhaps later this will become an overloaded operator
	while (poly_divisor.getDegree() <= poly_dividend.getDegree()) {
		//Step 1: Find how to multiply the first term of the divisor to get the first term of the dividend
		//We find the exponent of the first term of the answer by subtracting the degrees of the two polynomials
		exp = poly_dividend.getDegree() - poly_divisor.getDegree();
		//We then find the coefficient by finding what we multiply the divisor by to get the dividend
		//We find this by dividing the dividend by the divisor
		//If we end up dividing by zero it's because the user specified the degree to be zero. Should throw a logic_error exception
		co = poly_dividend[poly_dividend.getDegree()] / poly_divisor[poly_divisor.getDegree()];

		answer += make_pair(exp, co);

#ifndef DEBUG
		cout << "Answer is now " << answer.get() << endl;
#endif
		
		//Step 2: Multiply the newfound answer by all terms of divisor
		//Use overloaded * operator that takes polynomial and a pair<int,double> and returns a polynomial

		temp = (poly_divisor * make_pair(exp, co));
#ifndef DEBUG
		cout << "Temp is now " << temp.get() << endl;
#endif

		//Step 3: Subtract the polynomial from temp
		//Since we don't care about saving the dividend we'll just edit it

		poly_dividend -= temp;
#ifndef DEBUG
		cout << "Poly_Dividend is now " << poly_dividend.get() << endl;
#endif

		//Step 4: repeat until the degree of the divsor is less than the degree of the dividend
	}
	//Now whatever is left in dividend is the remainder
	remainder = poly_dividend.get();
	return answer.get() + " R " + remainder;
}

string polynomial_factor(string s) {
	cout << "Factor Polynomials has been executed" << endl;
	Polynomial p(s);
	return p.get();
}

