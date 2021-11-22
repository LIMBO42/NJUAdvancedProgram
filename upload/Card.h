#ifndef CARD_H
#define CARD_H
#include<string>
using namespace std;
class Card {
private:
	string cardNum;
	string name;
	double balance;
public:
	Card(string cardNum, string name, double balance);
	double get_balance();
	virtual double get_discount();
	string getName() {
		return name;
	}
	string getcardNum(){
		return cardNum;
	}
	void min_balance(double num) {
		balance -= num;
	}
};

class MonthCard :public Card {
public:
	MonthCard(string cardNum, string name, double balance);
	virtual double get_discount();

};

class YearCard :public Card {
public:
	YearCard(string cardNum, string name, double balance);
	virtual double get_discount();

};
#endif // !CARD_H

