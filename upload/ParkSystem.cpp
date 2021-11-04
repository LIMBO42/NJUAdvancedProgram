#include "ParkSystem.h"
#include <iostream>

void ParkSystem::add_card(Card* card)
{
	cards.push_back(card);
	mapCard.insert({ card->getName(),card });
}

void ParkSystem::vehicle_arrive(Vehicle* vehicle, int time)
{
	vehicles.push_back(vehicle);
	mapArrive.insert({ vehicle,time });
	//如果能找到
	if (mapVehicle.find(vehicle->getName()) != mapVehicle.end()) {
		mapVehicle[vehicle->getName()].push_back(vehicle);
	}
	else {
		mapVehicle.insert({ vehicle->getName(),vector<Vehicle*>{vehicle} });
	}
	std::cout << "Successfully Arranged\n";
}

void ParkSystem::vehicle_depart(Vehicle* vehicle, int time)
{
	string ownerName = vehicle->getName();
	if (mapVehicle.find(ownerName) != mapVehicle.end()) {
		
		auto& vec = mapVehicle[ownerName];
		auto it = vec.begin();
		for (; it != vec.end(); it++) {
			//同一辆车
			if ((*it)->getVehicle() == vehicle->getVehicle()) {
				int arrive = mapArrive[vehicle];
				double pay=(*it)->get_charge(arrive, time);
				double discount = mapCard[ownerName]->get_discount();
				mapCard[ownerName]->min_balance(discount * pay);
				cout << vehicle->getVehicle() << ":" << (double)discount * pay << "\n";
				sum += (double)discount * pay;
				break;
			}
			
		}
		vec.erase(it);
		mapArrive.erase(vehicle);
	}
	else {
		cerr << "error!\n";
	}

}

void ParkSystem::print_status()
{
	std::cout << "ParkSystem:\n";
	for (auto it = mapCard.begin(); it != mapCard.end(); it++) {
		//name
		string name = (*it).first;
		std::cout << name << ":\n";
		std::cout << "card:"<<(*it).second->getcardNum() << "\n";
		for (auto& v : mapVehicle) {
			if (v.first == name) {
				auto& vec = v.second;
				if (vec.size() > 0) {
					for (auto p : vec) {
						std::cout << p->getVehicle() << " ";
					}
					std::cout << "\n";
				}
			}
		}
	}
	
	std::cout << mapCard.size() << " " << mapArrive.size() << " " << sum << "\n";
}




int main()
{
	ParkSystem* park_system = new ParkSystem();
	Card* monthcard1 = new MonthCard("monthcard001", "xiaohong", 50);
	Card* yearcard1 = new YearCard("yearcard001", "xiaoming", 80);
	Card* card1 = new Card("card1", "xiaoli", 60);
	Vehicle* car1 = new Car("suA8888", "xiaohong", 5);
	Vehicle* bicycle2 = new Bicycle("ofo002", "xiaoming");
	Vehicle* car2 = new Car("suA9999", "xiaoming", 6);
	park_system->add_card(monthcard1);
	park_system->add_card(yearcard1);
	park_system->add_card(card1);
	park_system->print_status();
	park_system->vehicle_arrive(car1, 8);
	park_system->print_status();
	park_system->vehicle_arrive(bicycle2, 14);
	park_system->print_status();
	park_system->vehicle_depart(car1, 10);
	park_system->vehicle_depart(bicycle2, 19);
	park_system->vehicle_arrive(car2, 6);
	park_system->vehicle_arrive(bicycle2, 7);
	//park_system->vehicle_depart(car2, 9);
	park_system->print_status();

}