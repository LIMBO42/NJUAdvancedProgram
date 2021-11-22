#include "Vehicle.h"

Vehicle::Vehicle(string vehicleNum, string ownerName)
{
	this->vehicleNum = vehicleNum;
	this->ownerName = ownerName;
}

double Vehicle::get_charge(int arrive_time, int depart_time)
{
	
	
	return 0.0;
}

Car::Car(string vehicleNum, string ownerName, int people):Vehicle(vehicleNum,ownerName)
{
	this->people = people;
}

double Car::get_charge(int arrive_time, int depart_time)
{
	int time = depart_time - arrive_time;
	if (people <= 5) return time * 5;
	return time * 10;
}

Bicycle::Bicycle(string vehicleNum, string ownerName):Vehicle(vehicleNum,ownerName)
{
	
}

double Bicycle::get_charge(int arrive_time, int depart_time)
{
	int time = depart_time - arrive_time;
	if (time < 2) return 0.0;
	return time - 2;
}
/*
#include<iostream>
using namespace std;
int main() {
	Vehicle* car1 = new Car("suA8888", "xiaoming", 5);
	Vehicle* car2 = new Car("suA9999", "xiaohong", 7);
	Vehicle* bicycle1 = new Bike("ofo001", "xiaoming");
	Vehicle* bicycle2 = new Bike("ofo002", "xiaohong");
	Vehicle* bicycle3 = new Bike("ofo003", "xiaogang");
	cout << car1->get_charge(8, 10) << endl;
	cout << car2->get_charge(8, 10) << endl;
	cout << bicycle1->get_charge(8, 9) << endl;
	cout << bicycle2->get_charge(8, 10) << endl;
	cout << bicycle3->get_charge(8, 11) << endl;

}*/