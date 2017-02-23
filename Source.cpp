#include "Polynomial.h"
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int getcmd(const string& s);

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
	poly_factor
};

int main() {
	string s;
	while (getline(cin, s)) {
		if (s.empty())
			continue;
		switch (int i = getcmd(s)) {
		case simplify:
			//
			break;
		}

	}
	return 0;
}

int getcmd(const string& s) {
	char c = s[0];
	string sub("");
	int count = 0;
	while (!isspace(c)) {
		sub += c;
		count++;
		c = s[count];
	}
	if (sub == "simplify") return simplify;
	else if (sub == "define") return define;
	else if (sub == "poly_condense") return poly_condense;
	else if (sub == "poly_divide") return poly_divide;
	else if (sub == "poly_factor") return poly_factor;
	else return invalid;
}