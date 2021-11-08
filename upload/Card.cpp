#include "Card.h"

Card::Card(string cardNum, string name, double balance)
{
	this->cardNum = cardNum;
	this->name = name;
	this->balance = balance;
}

double Card::get_balance()
{
	return balance;
}

double Card::get_discount()
{
	return 1.0;
}


MonthCard::MonthCard(string cardNum, string name, double balance):Card(cardNum,name,balance)
{
	
}

double MonthCard::get_discount()
{
	return 0.8;
}

YearCard::YearCard(string cardNum, string name, double balance):Card(cardNum,name,balance)
{
}

double YearCard::get_discount()
{
	return 0.7;
}

/*
#include<iostream>
using namespace std;
int main()
{
	Card* card1 = new Card("card001", "xiaobing", 100);
	Card* monthcard1 = new MonthCard("monthcard001", "xiaohong", 50);
	Card* yearcard1 = new YearCard("yearcard001", "xiaoming", 80);
	cout << card1->get_balance() << endl;
	cout << monthcard1->get_balance() << endl;
	cout << yearcard1->get_balance() << endl;
	cout << card1->get_discount() << endl;
	cout << monthcard1->get_discount() << endl;
	cout << yearcard1->get_discount() << endl;

}*/
