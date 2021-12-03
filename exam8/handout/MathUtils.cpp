#include "MathUtils.h"

Complex MathUtils::calculator(string s)
{
	//只支持两个复数的计算
	int first_end = s.find_first_of(")");
	string first_complex = s.substr(1, first_end-1);
	char ch = s[first_end + 1];
	string second_complex = s.substr(first_end + 3, s.size()-first_end-4);

	istringstream iss_first(first_complex);
	Complex c1;
	iss_first >> c1;

	istringstream iss_second(second_complex);
	Complex c2;
	iss_second >> c2;
	
	if (ch == '+') {
		return c1 + c2;
	}
	else if (ch == '-') {
		return c1 - c2;
	}
	else if (ch == '*') {
		return c1 * c2;
	}
	else if (ch == '/') {
		return c1 / c2;
	}
	
	return Complex(0,0);
}

void MathUtils::processTextFile(string inputFilename, string outputFilename)
{
	
}


/*
int main()
{
	try {
		cout << MathUtils::calculator("(5+4i)/(1+2i)");
	}
	catch (ArithmeticError& e) {
		cout << e.what();
	}
	catch (...) {
		cout << "ERROR" << endl;
	}
	
	try {
		MathUtils::processTextFile("input1.txt", "output.txt"); // "input.txt"不存在
	}
	catch (FileNotFound& e) {
		cout << e.what();
	}
	catch (...) {
		cout << "ERROR" << endl;
	}
	try {
		MathUtils::processTextFile("input.txt", "output.txt"); // "input2.txt"存在
		cout << "True" << endl;
	}
	catch (FileNotFound& e) {
		cout << e.what();
	}
	catch (...) {
		cout << "ERROR" << endl;
	}
	
	return 0;
}*/