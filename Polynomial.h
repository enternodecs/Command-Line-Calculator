#pragma once
#include <string>
#include <map>

struct Polynomial {
	Polynomial(std::string s);
protected:
	std::map<int, long double> m;
};