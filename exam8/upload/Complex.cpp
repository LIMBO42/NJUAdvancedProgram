#include "Complex.h"
bool judgeAdd(int x, int y) {
	int sum = x + y;
	if (x > 0 && y > 0 && sum < 0) return false;
	if (x < 0 && y < 0 && sum > 0) return false;
	return true;
}
Complex Complex::operator+(const Complex& c)
{
	
	if (!judgeAdd(real,c.real)) {
		throw  OverFlow("Complex add overflow!\n");
	}
	if (!judgeAdd(imag, c.imag)) {
		throw  OverFlow("Complex add overflow!\n");
	}
	int realSum = real + c.real;
	int imagSum = imag + c.imag;
	return Complex(realSum, imagSum);
}

bool judgeMinus(int x, int y) {
	if (y == INT_MIN) {
		if (x >= 0) return false;
		else return true;
	}
	return judgeAdd(x, -y);
}

Complex Complex::operator-(const Complex& c)
{
	
	if (!judgeMinus(real, c.real)) {
		throw OverFlow("Complex minus overflow!\n");
	}
	if (!judgeMinus(imag, c.imag)) {
		throw OverFlow("Complex minus overflow!\n");
	}
	int realSum = real - c.real;
	int imagSum = imag - c.imag;
	return Complex(realSum, imagSum);
}

bool judgeMul(int x,int y) {
	if (y == 0) return true;
	long long mul = x * y;
	if (mul / y != x) return false;
	return true;
}

Complex Complex::operator*(const Complex& c)
{
	if (!judgeMul(real,c.real) || !judgeMul(imag,c.imag) || !judgeMul(real, c.imag) || !judgeMul(imag, c.real)) {
		throw  OverFlow("Complex multiply overflow!\n");
	}
	int realSum = real * c.real - (imag * c.imag);
	int imagSum = real * c.imag + imag * c.real;

	return Complex(realSum,imagSum);
}

bool judgeDivide(int x, int y) {
	if (y == 0) return false;
	if (x == INT_MIN && y == -1) return false;
	return true;
}

Complex Complex::operator/(const Complex& c)
{
	//ac+bd
	//a+bi
	//c+di
	int realx = real * c.real + imag * c.imag;
	int y = c.real * c.real + c.imag * c.imag;
	if (y == 0) throw ArithmeticError("ArithmeticError!\n");
	if (!judgeMul(real, c.real) || !judgeMul(imag, c.imag) || !judgeMul(c.real, c.real) || !judgeMul(c.imag, c.imag)) {
		throw  OverFlow("Complex multiply overflow!\n");
	}
	if(!judgeAdd(real * c.real,imag * c.imag)||!judgeAdd(c.real * c.real,c.imag * c.imag)){
		throw  OverFlow("Complex add overflow!\n");
	}
	if(!judgeMinus(imag * c.real,real * c.imag)){
		throw OverFlow("Complex minus overflow!\n");
	}
	//bc-ad
	int realy = imag * c.real - real * c.imag;
	if (!judgeDivide(realx, y) || !judgeDivide(realy, y)) {
		throw OverFlow("Complex divide overflow!\n");
	}
	int realSum = realx / y;
	int imagSum = realy / y;

	return Complex(realSum, imagSum);
}

ostream& operator<<(ostream& out, const Complex& c)
{
	// TODO: 在此处插入 return 语句
	//虚部大于等于0
	if (c.imag >= 0) out << c.real << "+" << c.imag << "i";
	else out << c.real << "-" << -c.imag << "i";
	return out;
}
/*
vector<string> split(const string& str, const string& pattern) {
	vector<string> res;
	if (str == "") return res;
	string strs = str + pattern[0];
	size_t pos = strs.find_first_of(pattern);
	while (pos != strs.npos) {
		string temp = strs.substr(0, pos);
		res.push_back(temp);
		//
		strs = strs.substr(pos + 1, strs.size());
		pos = strs.find_first_of(pattern);
	}
	return res;
}
*/
istream& operator>>(istream& in, Complex& c)
{

	//只考虑 虚数
	string str="";
	in >> str;
	size_t pos = str.find_last_of("+-");
	//实部
	string real_part = str.substr(0, pos);
	
	//虚部
	string imag_part = str.substr(pos + 1, str.size());

	c.real = stoi(real_part);


	imag_part = imag_part.substr(0,imag_part.size() - 1);

	//注意处理-INT_MIN的情况
	if (imag_part == "2147483648" && str[pos] == '-') { 
		c.imag = INT_MIN;
		return in; 
	}
	
	c.imag = stoi(imag_part);
	
	if(str[pos]=='-')	c.imag = -c.imag;
	return in;

}
