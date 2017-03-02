#include "Polynomial.h"
#include <string>
#include <cstdlib>
#include <iostream>

//Disables debug when defined
#define DEBUG

using namespace std;

//Constructors

Polynomial::Polynomial(string s) {
#ifndef DEBUG
	cout << "Constructing polynomial " << s << endl;
#endif
	string::iterator iter = s.begin();
	string coetemp("");
	string exptemp("");
	double d;
	int i;
	int deg = 0;
	//Read string
	while (iter != s.end()) {
		//If a number, assume coefficient
		if (isdigit(*iter) || *iter == '.' || *iter == '-') {
			coetemp += *iter;
			iter++;
		}
		//If not, see if it's the end of one
		else if (*iter == 'x') {
			//If x has no coefficient
			if (coetemp == "")
				coetemp = "1.0";
			//Parse coefficient into double
			d = atof(coetemp.c_str());
			//Incriment into the exponent
			if (iter != s.end())
				++iter;
			//Just in case they decided to use a carrot to denote exponent
			if (iter != s.end() && *iter == '^')
				++iter;
			//Read exponent into int
			while (iter != s.end() && isdigit(*iter)) {
				exptemp += *iter;
				++iter;
			}
			//If X has no exponent, assume one
			if (exptemp == "")
				exptemp = "1";
			i = atoi(exptemp.c_str());
			//Test for degree to be used as a convenience variable later
			if (i > deg)
				deg = i;
			//Shove it into the map
			poly[i] = d;
			//Reset values
			i = 0;
			d = 0.0;
			coetemp = "";
			exptemp = "";
		}
		//We don't need to bother with plus signs
		else if (*iter == '+') iter++;
		else throw exception("Unknown char" + *iter);
	}
	//The constant should still not have been written but have been read into the temp string
	d = atof(coetemp.c_str());
	poly[0] = d;
	i = 0;
	d = 0.0;
	coetemp = "";
	exptemp = "";
	//Initialize empty map elements
	for (int j = deg; j >= 1; j--)
		poly[j];
	//The constant is garunteed to be initialized
	poly[0];
	//Initialize member variables
	degree = deg;
}

//Member Functions

string Polynomial::get() {
	string ret("");
	for (int i = degree; i > 0; i--) {
		if (i >= 2) {
			if (abs(poly[i]) > 1e-7)
				ret += ('+' + to_string(poly[i]) + "x^" + to_string(i));
		}
		else if (i == 1) {
			if (abs(poly[i]) > 1e-7)
				ret += ('+' + to_string(poly[i]) + "x");
		}
	}
	if (abs(poly[0]) > 1e-7)
		ret += ('+' + to_string(poly[0]));
	if (ret == "")
		ret = "0";
	return ret;
}

string Polynomial::get() const {
	string ret("");
	for (int i = degree; i > 0; i--) {
		if (i >= 2) {
			if (abs((*this)[i]) > 1e-7)
				ret += ('+' + to_string((*this)[i]) + "x^" + to_string(i));
		}
		else if (i == 1) {
			if (abs((*this)[i]) > 1e-7)
				ret += ('+' + to_string((*this)[i]) + "x");
		}
	}
	if (abs((*this)[0]) > 1e-7)
		ret += ('+' + to_string((*this)[0]));
	if (ret == "")
		ret = "0";
	return ret;
}

void Polynomial::updateDegree() {
	double zero = 0.000000;
	degree = 0;
	for (unsigned int i = 0; i < poly.size(); i++) {
		if (abs(poly[i] - 0.0) >= 1e-7) {
			degree = i;
		}
	}
#ifndef DEBUG
	std::cout << "The degree of " << get() << " is now " << degree << std::endl;
#endif
}


//Overloaded Operators

Polynomial Polynomial::operator*(const pair<int, double> &p) const {
#ifndef DEBUG
	cout << "Multiplying " << poly.get() << " and " << p.second << "x^" << p.first << endl;
#endif
	//Best way to construct polynomial is by using a string
	string s("");
	//Variables we do not need to destroy and remake at every iteration
	double tco;
	int texp;
	//For every term in the polynomial
	for (int i = getDegree(); i != -1; i--) {
		//Add exponents
		texp = p.first + i;
		//Multiply coefficients
		tco = p.second * (*this)[i];
		//Append string
		if (texp != 0) {
			s += to_string(tco) + "x^" + to_string(texp) + "+";
		}
		else {
			s += to_string(tco);
		}
	}
	//Return a constructed polynomial from string

	Polynomial answer(s);
#ifndef DEBUG
	cout << "Result is " << answer.get() << endl;
#endif

	return answer;
}

void Polynomial::operator+=(Polynomial &rhs) {
#ifndef DEBUG
	std::cout << "Adding polynomial " << rhs.get() << " to " << get() << std::endl;
	std::cout << "rhs has a degree of " << rhs.getDegree() << std::endl;
#endif
	//For every exponent of rhs, add coefficients
	//Guards against the right hand operand being a larger polynomial by basing the current exponent off of the rhs.
	//Does not break anything if the right hand is smaller or is empty
	for (int i = rhs.getDegree(); i != -1; i--) {
#ifndef DEBUG
		std::cout << "Loop has been run. I is " << i << " and poly[i] is " << poly[i] << " and rhs[i] is " << rhs[i] << std::endl;
#endif
		poly[i] += rhs[i];
#ifndef DEBUG
		std::cout << "poly[i] is now " << poly[i] << std::endl;
#endif
	}
	//RUN GOD DAMNIT
	this->updateDegree();
	//That's pretty much it.
#ifndef DEBUG
	std::cout << "Result is " << get() << std::endl;
#endif
}

void Polynomial::operator+=(std::pair<int, double> &rhs) {
#ifndef DEBUG
	std::cout << "Adding term " << rhs.second << "x^" << rhs.first << " to " << get() << std::endl;
#endif
	poly[rhs.first] += rhs.second;
	updateDegree();
#ifndef DEBUG
	std::cout << "Result is " << get() << std::endl;
#endif
}

void Polynomial::operator-=(Polynomial &rhs) {
#ifndef DEBUG
	std::cout << "Subtracting " << rhs.get() << " from " << get() << std::endl;
#endif
	//For every exponent of rhs, subtract coefficients
	//It does not matter if the right hand is larger, as it will simply result in a negative degree polynomial, which exist.
	//Does not break anything if the right hand is smaller or is empty
	for (int i = rhs.getDegree(); i != -1; i--) {
		poly[i] -= rhs[i];
	}
	updateDegree();
#ifndef DEBUG
	std::cout << "Result is " << get() << std::endl;
#endif
	//Done
}

//Left side is answer, right side is remainder
pair<Polynomial, Polynomial> Polynomial::operator/(const Polynomial &rhs) {

	Polynomial poly_dividend(*this), answer("0"), temp("0");
	int exp = 0;
	double co = 0;
	string remainder;
	//Perhaps later this will become an overloaded operator
	while (rhs.getDegree() <= poly_dividend.getDegree()) {
		//Step 1: Find how to multiply the first term of the divisor to get the first term of the dividend
		//We find the exponent of the first term of the answer by subtracting the degrees of the two polynomials
		exp = poly_dividend.getDegree() - rhs.getDegree();
		//We then find the coefficient by finding what we multiply the divisor by to get the dividend
		//We find this by dividing the dividend by the divisor
		//If we end up dividing by zero it's because the user specified the degree to be zero. Should throw a logic_error exception
		co = poly_dividend[poly_dividend.getDegree()] / rhs[rhs.getDegree()];

		answer += make_pair(exp, co);

#ifndef DEBUG
		cout << "Answer is now " << answer.get() << endl;
#endif

		//Step 2: Multiply the newfound answer by all terms of divisor
		//Use overloaded * operator that takes polynomial and a pair<int,double> and returns a polynomial

		temp = (rhs * make_pair(exp, co));
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
	if (remainder == "") remainder = "0";
	Polynomial poly_remainder(remainder);
	return make_pair(answer, poly_remainder);
}