#pragma once
#ifndef MYSTRING_H
#define MYSTRING_H
#include "string.h"
class myString {
private:
	//�ַ�������
	char* str_;
	//�ѷ���ռ�Ĵ�С
	int capacity_;
	//�ַ�����С��������'\0'
	int size_;
public:
	//Ĭ�Ϲ��캯��
	//Ĭ�Ϲ���ռ��СΪ8���ֽ�
	myString();
	myString(const char* str = nullptr);
	//�������캯��
	myString(const myString& str);
	//��������
	~myString();
	//��������
	myString& operator=(myString& str);
	//�ַ���
	myString& operator+=(char ch);
	//�ַ�����
	myString& operator+=(const char* str);
	//myString��
	myString& operator+=(const myString& str);
	//�Ƚ����������
	bool operator<(const myString& str);
	bool operator==(const myString& str);
	//����,ÿ����������һ��
	void Resize();
	int get_size() const;
	int get_capacity() const;
	//��ӡ�ַ���
	void printStr();

};


#endif // MYSTRING_H
