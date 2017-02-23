#include "Polynomial.h"
#include <iostream>
#include <string>

using namespace std;

string handle_input(string s, int i);

enum Commands {
	simplify,
	define,
	poly_condense,
	poly_divide,
	poly_factor
};

int main() {
	string s;
	while (getline(cin, s)) {
		//determine command, then pass arguments
		int i = 0;
		cout << handle_input(s, i) << endl;
	}
	return 0;
}

string handle_input(string s, int i) {
	return "It works!";
}