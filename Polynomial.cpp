#include "Polynomial.h"
#include <string>
#include <cstdlib>

using namespace std;

Polynomial::Polynomial(string s) {
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
	}
	//The coefficient should still not have been written but have been read into the temp string
	d = atof(coetemp.c_str());
	poly[0] = d;
	i = 0;
	d = 0.0;
	coetemp = "";
	exptemp = "";
	//Initialize empty map elements
	for (int j = deg; j >= 0; j--)
		poly[j];
	//Initialize member variables
	degree = deg;
}

string Polynomial::get() {
	string ret("");
	for (int i = degree; i > 0; i--)
		ret += (to_string(poly[i]) + "x^" + to_string(i) + '+');
	ret += (to_string(poly[0]));
	return ret;
}
