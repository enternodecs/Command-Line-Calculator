#pragma once
#include <string>
#include <map>
//#include <cstdlib>

struct Polynomial {
	Polynomial(std::string s);
	std::string get();
protected:
	//Key is the exponent, double is the coefficient
	std::map<int, double> poly;
	int degree;
};