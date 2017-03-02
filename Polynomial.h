#pragma once
#include <string>
#include <map>
#include <iostream>
//#include <cstdlib>
#define DEBUG

struct Polynomial {
	Polynomial():degree(0) {
		poly[0] = 0;
	};
	//Do not use default constructor. For some fucking reason it doesn't go very well
	Polynomial(std::string s);
	std::string get();
	std::string get() const;
	int getDegree() {
		return degree;
	}
	int getDegree() const {
		return degree;
	}
	//Overrided operator to get coefficient from exponent
	double operator[](const int &i) {
		//Returns a right-hand operand
		return poly[i];
	}
	double operator[](const int &i) const {
		//Returns a right-hand operand
		std::map<int, double>::const_iterator j = poly.find(i);
		return (*j).second;
	}
	//Overrided operator to add a polynomials
	void operator+=(Polynomial &rhs) {
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
	//Overloaded operator to add a term
	void operator+=(std::pair<int, double> &rhs) {
#ifndef DEBUG
		std::cout << "Adding term " << rhs.second << "x^" << rhs.first << " to " << get() << std::endl;
#endif
		poly[rhs.first] += rhs.second;
		updateDegree();
#ifndef DEBUG
		std::cout << "Result is " << get() << std::endl;
#endif
	}
	//Overloaded operator to remove polynomials
	void operator-=(Polynomial &rhs) {
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
protected:
	//Key is the exponent, value is the coefficient
	std::map<int, double> poly;
	int degree;
	void updateDegree() {
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
};