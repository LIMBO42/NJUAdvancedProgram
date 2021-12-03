#include "Complex.h"

Complex Complex::operator+(const Complex& c)
{
	int realSum = real + c.real;
	int imagSum = imag + c.imag;
	return Complex(realSum, imagSum);
}

Complex Complex::operator-(const Complex& c)
{
	
	int realSum = real - c.real;
	int imagSum = imag - c.imag;
	return Complex(realSum, imagSum);
}



Complex Complex::operator*(const Complex& c)
{
	
	int realSum = real * c.real - (imag * c.imag);
	int imagSum = real * c.imag + imag * c.real;

	return Complex(realSum,imagSum);
}



Complex Complex::operator/(const Complex& c)
{
	//ac+bd
	//a+bi
	//c+di
	int realx = real * c.real + imag * c.imag;
	int y = c.real * c.real + c.imag * c.imag;
	
	//bc-ad
	int realy = imag * c.real - real * c.imag;
	
	int realSum = realx / y;
	int imagSum = realy / y;

	return Complex(realSum, imagSum);
}

ostream& operator<<(ostream& out, const Complex& c)
{
	//虚部大于等于0
	if (c.imag >= 0) out << c.real << "+" << c.imag << "i";
	else out << c.real << "-" << -c.imag << "i";
	return out;
}

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

	c.imag = stoi(imag_part);
	
	if(str[pos]=='-')	c.imag = -c.imag;
	return in;

}
