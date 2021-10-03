#ifndef __MYMATRIX_H__
#define __MYMATRIX_H__

#include<iostream>

template<typename __T>
class myMatrix
{
private:
	int row;
	int col;
	__T **num;
public:
	myMatrix(const int,const int);
	myMatrix(const myMatrix<__T>&);
	~myMatrix();
	myMatrix  operator+ (const myMatrix<__T>&);
	myMatrix  operator- (const myMatrix<__T>&);
	myMatrix  operator* (const myMatrix<__T>&);
	myMatrix& operator= (const myMatrix<__T>&);
	__T*    operator[](const int);
	myMatrix  Hadamard  (const myMatrix<__T>&);
	myMatrix  Transpose ();
	template<typename T> friend std::ostream& operator<<(std::ostream&,const myMatrix<T>&);
	template<typename T> friend std::istream& operator>>(std::istream&,const myMatrix<T>&);
};

template<typename __T>
myMatrix<__T>::myMatrix(const int __row,const int __col)
{
	row=__row;
	col=__col;
	if(row>0 && col>0)
	{
		num=new __T* [row];
		for(int i=0;i<row;++i)
			num[i]=new __T[col];
	}
	else
	{
		row=0;
		col=0;
		num=NULL;
	}
	return;
}

template<typename __T>
myMatrix<__T>::myMatrix(const myMatrix<__T>& __temp)
{
	row=__temp.row;
	col=__temp.col;
	if(row>0 && col>0)
	{
		num=new __T* [row];
		for(int i=0;i<row;++i)
			num[i]=new __T[col];
		for(int i=0;i<row;++i)
			for(int j=0;j<col;++j)
				num[i][j]=__temp.num[i][j];
	}
	else
	{
		row=0;
		col=0;
		num=NULL;
	}
	return;
}

template<typename __T>
myMatrix<__T>::~myMatrix()
{
	if(num)
	{
		for(int i=0;i<row;++i)
			delete[] num[i];
		delete[] num;
	}
	return;
}

template<typename __T>
myMatrix<__T> myMatrix<__T>::operator+(const myMatrix<__T>& B)
{
	if(this->row==B.row&&this->col==B.col)
	{
		for(int i=0;i<row;++i)
			for(int j=0;j<col;++j)
				this->num[i][j]+=B.num[i][j];
		return *this;
	}
	else
	{
		myMatrix<__T> NullMatrix(0,0);
		std::string WarningInformation="No matching matrix";
		throw WarningInformation;
		return NullMatrix;
	}
}

template<typename __T>
myMatrix<__T> myMatrix<__T>::operator-(const myMatrix<__T>& B)
{
	if(this->row==B.row&&this->col==B.col)
	{
		for(int i=0;i<row;++i)
			for(int j=0;j<col;++j)
				this->num[i][j]-=B.num[i][j];
		return *this;
	}
	else
	{
		myMatrix<__T> NullMatrix(0,0);
		std::string WarningInformation="No matching matrix";
		throw WarningInformation;
		return NullMatrix;
	}
}

template<typename __T>
myMatrix<__T> myMatrix<__T>::operator*(const myMatrix<__T>& B)
{
	myMatrix<__T> NullMatrix(0,0);
	if(!this->row || !this->col|| !B.row|| !B.col)
	{
		std::string WarningInformation="No matching matrix";
		throw WarningInformation;
	}
	else if(this->col!=B.row)
	{
		std::string WarningInformation="No matching matrix";
		throw WarningInformation;
	}
	else
	{
		myMatrix<__T> Temp(this->row,B.col);
		__T trans;
		for(int i=0;i<Temp.row;++i)
			for(int j=0;j<Temp.col;++j)
			{
				trans=0;
				for(int k=0;k<this->col;++k)
					trans+=this->num[i][k]*B.num[k][j];
				Temp.num[i][j]=trans;
			}
		return Temp;
	}
	return NullMatrix;
}

template<typename __T>
myMatrix<__T>& myMatrix<__T>::operator=(const myMatrix<__T>& B)
{
	if(num)
	{
		for(int i=0;i<row;++i)
			delete[] num[i];
		delete num;
	}
	row=B.row;
	col=B.col;
	if(row>0 && col>0)
	{
		num=new __T* [row];
		for(int i=0;i<row;++i)
			num[i]=new __T[col];
		for(int i=0;i<row;++i)
			for(int j=0;j<col;++j)
				num[i][j]=B.num[i][j];
	}
	else
	{
		row=0;
		col=0;
		num=NULL;
	}
	return *this;
}

template<typename __T>
__T* myMatrix<__T>::operator[](const int addr)
{
	return addr>=this->row? NULL:this->num[addr];
}

template<typename __T>
myMatrix<__T> myMatrix<__T>::Hadamard(const myMatrix<__T>& B)
{
	myMatrix<__T> NullMatrix(0,0);
	if(!this->row || !this->col || !B.row || !B.col)
	{
		std::string WarningInformation="No matching matrix";
		throw WarningInformation;
	}
	else if(this->row!=B.row || this->col!=B.col)
	{
		std::string WarningInformation="No matching matrix";
		throw WarningInformation;
	}
	else
	{
		myMatrix<__T> temp(this->row,this->col);
		for(int i=0;i<this->row;++i)
			for(int j=0;j<this->col;++j)
				temp.num[i][j]=this->num[i][j]*B.num[i][j];
		return temp;
	}
	return NullMatrix;
}

template<typename __T>
myMatrix<__T> myMatrix<__T>::Transpose()
{
	myMatrix<__T> temp(this->col,this->row);
	for(int i=0;i<this->row;++i)
		for(int j=0;j<this->col;++j)
			temp.num[j][i]=this->num[i][j];
	return temp;
}

template<typename T>
std::ostream& operator<<(std::ostream& strm,const myMatrix<T>& aim)
{
	for(int i=0;i<aim.row;++i)
	{
		for(int j=0;j<aim.col;++j)
			strm<<aim.num[i][j]<<((char)(j==aim.col-1)? '\n':' ');
	}
	return strm;
}

template<typename T>
std::istream& operator>>(std::istream& strm,const myMatrix<T>& aim)
{
	for(int i=0;i<aim.row;++i)
		for(int j=0;j<aim.col;++j)
			strm>>aim.num[i][j];
	return strm;
}
#endif