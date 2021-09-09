#include<iostream>
#include"myString.h"
using namespace std;
int main()
{
	myString str1("hello world");
	str1.printStr();
	cout << str1.get_capacity() << " " << str1.get_size() << endl;

	myString str2(str1);
	str2.printStr();
	cout << str2.get_capacity() << " " << str2.get_size() << endl;

	str2 += '!';
	str2.printStr();
	cout << str2.get_capacity() << " " << str2.get_size() << endl;

	str2 += " This is my implement of sring!";
	str2.printStr();
	cout << str2.get_capacity() << " " << str2.get_size() << endl;

	str2 += str1;
	str2.printStr();
	cout << str2.get_capacity() << " " << str2.get_size() << endl;

	str1 = str2;
	str1.printStr();
	cout << str1.get_capacity() << " " << str1.get_size() << endl;

	myString str3("AAAAAAAAAA");
	myString str4("BBBBBBBBBB");
	cout << (str3 < str4) << endl;

	return 0;
}