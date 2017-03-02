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

