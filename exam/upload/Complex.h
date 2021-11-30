#ifndef COMPLEX_H
#define COMPLEX_H
#include <string>
#include <vector>
#include "MyException.h"
#include <iostream>
#include <sstream>
#include <climits> 
#include <fstream>
using namespace std;
class Complex
{
private:
    int real; // 实部
    int imag; // 虚部
public:
    Complex() = default;
    Complex(int real, int imag) {
        this->real = real;
        this->imag = imag;
    }
    int getReal(){
        return real;
    }
    int getImag(){
        return imag;
    }
    // TODO 重载+, 实现复数的相加
    Complex operator+(const Complex& c);
    
    // TODO 重载-, 实现复数的相减
    Complex operator-(const Complex& c);

    // TODO 重载*, 实现负数的相乘
    Complex operator*(const Complex& c);

    // TODO 重载/, 实现复数的相除
    Complex operator/(const Complex& c);

    // 重载<<, 输出格式为a+bi，a和b分别是复数的实部和虚部,没有空格，不需要输出回车
    // 注意:a或b为复数的输出示例，-1-3i
    friend ostream & operator << (ostream & out, const Complex &c);
    // 重载>>, 读取a+bi格式的输入，格式同上。
    friend istream & operator >> (istream & in, Complex & c);
};
#endif