#ifndef PARKSYSTEM_H
#define PARKSYSTEM_H
#include "Card.h"
#include "Vehicle.h"
#include<vector>
#include<unordered_map>
class ParkSystem{
private:
	vector<Card*> cards;
	vector<Vehicle*> vehicles;
	unordered_map<string, Card*> mapCard;
	unordered_map<string, vector<Vehicle*>> mapVehicle;
	unordered_map<Vehicle*, int> mapArrive;
	double sum = 0;
public:
	void add_card(Card* card);
	string vehicle_arrive(Vehicle* vehicle, int time);
	string vehicle_depart(Vehicle* vehicle, int time);
	string print_status();
	//void print_people();

};
#endif // !PARKSYSTEM_H

