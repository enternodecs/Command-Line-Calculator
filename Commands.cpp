#include "Polynomial.h"
#include <iostream>
#include <string>
#include <cctype>
#include <utility>

using namespace std;

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
	//Read the two polynomials
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

	//Declare polynomials
	Polynomial poly_dividend(dividend), poly_divisor(divisor);

	pair<Polynomial, Polynomial> pop = poly_dividend / poly_divisor;

	return pop.first.get() + " R " + (pop.second.get());
}

string polynomial_factor(string s) {
	cout << "Factor Polynomials has been executed" << endl;
	Polynomial p(s);
	return p.get();
}
