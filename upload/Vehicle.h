#ifndef VEHICLE_H
#define VEHICLE_H
#include<string>
using std::string;
class Vehicle {
private:
	string vehicleNum;
	string ownerName;
public:
	Vehicle(string vehicleNum, string ownerName);
	virtual double get_charge(int arrive_time, int depart_time);
	string getName(){
		return ownerName;
	}
	string getVehicle() {
		return vehicleNum;
	}
};
class Car:public Vehicle {
private:
	int people;
public:
	Car(string vehicleNum, string ownerName, int people);
	virtual double get_charge(int arrive_time, int depart_time);
	
};

class Bicycle :public Vehicle {
public:
	Bicycle(string vehicleNum, string ownerName);
	virtual double get_charge(int arrive_time, int depart_time);
};
#endif // !VEHICLE_H
