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
	try{
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
	}
	catch (ArithmeticError& e) {
		//cout << e.what();
		throw e;
	}
	catch (OverFlow& e) {
		//cout << e.what();
		throw e;
	}
	catch (...) {
		cout << "ERROR"<<endl;
	}

	return Complex(0,0);
}

void MathUtils::processTextFile(string inputFilename, string outputFilename)
{
	ifstream in(inputFilename);
	if (!in) throw FileNotFound("Cannot open " + inputFilename + "\n");
	ofstream out(outputFilename);
	if(!out) throw FileNotFound("Cannot open " + outputFilename + "\n");
	string str;
	while (in >> str) {
		Complex c = calculator(str);
		out << c << endl;
	}
	in.close();
	out.close();
}

/*
* 
* 
(2147483646-1i)+(-2+1i)
(0-2i)+(2147483647+2i)
(-2147483647-1073741824i)+(-2-1i)
(-2147483648+0i)/(0+0i)
(-2147483648-2i)*(2147483647-1i)
(-2147483648+1i)+(0+1073741823i)
(2147483646-1i)*(-1+1073741823i)
(2147483646+2i)*(1073741823-2147483647i)
(0+1i)+(2+1i)
(0-1i)*(-2+0i)
(-2147483648+2147483647i)*(2-2i)
(-2147483648-2i)+(3+2i)

(2147483646+3i)+(-2147483648+2i)
(-2147483647+2147483647i)-(1073741823+3i)
(2147483646+0i)+(2147483647+3i)
(-1-2147483648i)/(1+2i)
(2147483646+2147483646i)-(3+0i)
(-2147483647+0i)*(-2147483648-2147483647i)
(-2147483647+0i)+(2+2147483646i)
(2147483647+2147483646i)+(0-2i)
(-2147483647-2i)/(0+2147483646i)
(-2147483648-2i)/(2+3i)
(2147483646+3i)+(2147483646+1073741823i)
(2147483646+3i)-(-1+0i)
*/

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