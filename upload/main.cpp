#include "ParkSystem.h"
#include <iostream>
#include <random>
#include <unordered_map>
#include <algorithm>
using namespace std;

vector<string> peopleName = { "A","B","C","D","E","F" };

vector<string> cardType = { "Card","Month","Year" };
vector<string> vehicleNum = { "a","b","c","d","e","f","a1","b2","c3","d4","e5","f6" };

vector<string> cardName(6, "");

void VERIFY_TRUE(bool condition, int line) {
    if (!condition) {
        std::cout << 0 << std::endl;
    }
    else {
        std::cout << 1 << std::endl;
    }
}

vector<int> random_permut(int n)
{
    vector<int> temp;
    for (int i = 0; i < n; i++)
        temp.push_back(i);
    std::random_shuffle(temp.begin(), temp.end());
    return temp;
}


class newCard {
private:
    string cardNum;
    string name;
    double balance;
public:
    
    newCard(string cardNum, string name, double balance) {
        this->cardNum = cardNum;
        this->name = name;
        this->balance = balance;
    }
    double get_balance() {
        return balance;
    }
    virtual double get_discount(){
        return 1.0;
    }
    string getName() {
        return name;
    }
    string getcardNum() {
        return cardNum;
    }
    void min_balance(double num) {
        balance -= num;
    }
};

class newMonthCard :public newCard {
public:
    newMonthCard(string cardNum, string name, double balance):newCard(cardNum, name, balance) {
        
    }
    virtual double get_discount() {
        return 0.8;
    }

};

class newYearCard :public newCard {
public:
    newYearCard(string cardNum, string name, double balance):newCard(cardNum, name, balance) {
        
    }
    virtual double get_discount() {
        return 0.7;
    }

};

class newVehicle {
private:
    string vehicleNum;
    string ownerName;
public:
    newVehicle(string vehicleNum, string ownerName) {
        this->vehicleNum = vehicleNum;
        this->ownerName = ownerName;
    }
    virtual double get_charge(int arrive_time, int depart_time) {
        return 0.0;
    }
    string getName() {
        return ownerName;
    }
    string getVehicle() {
        return vehicleNum;
    }
};
class newCar :public newVehicle {
private:
    int people;
public:
    newCar(string vehicleNum, string ownerName, int people):newVehicle(vehicleNum, ownerName) {
        this->people = people;
    }
    virtual double get_charge(int arrive_time, int depart_time) {
        int time = depart_time - arrive_time;
        if (people <= 5) return time * 5;
        return time * 10;
    }

};

class newBicycle :public newVehicle {
public:
    newBicycle(string vehicleNum, string ownerName):newVehicle(vehicleNum, ownerName) {};
    virtual double get_charge(int arrive_time, int depart_time) {
        int time = depart_time - arrive_time;
        if (time < 2) return 0.0;
        return time - 2;
    }
};

class newParkSystem {
private:
    vector<newCard*> cards;
    vector<newVehicle*> vehicles;
    unordered_map<string, newCard*> mapCard;
    unordered_map<string, vector<newVehicle*>> mapVehicle;
    unordered_map<newVehicle*, int> mapArrive;
    double sum = 0;
public:
    void add_card(newCard* card) {
        cards.push_back(card);
        mapCard.insert({ card->getName(),card });
    }
    string vehicle_arrive(newVehicle* vehicle, int time) {
        string str = "";
        vehicles.push_back(vehicle);
        mapArrive.insert({ vehicle,time });
        //如果能找到
        if (mapVehicle.find(vehicle->getName()) != mapVehicle.end()) {
            mapVehicle[vehicle->getName()].push_back(vehicle);
        }
        else {
            mapVehicle.insert({ vehicle->getName(),vector<newVehicle*>{vehicle} });
        }
        str+= "Successfully Arranged\n";
        return str;
    }
    string vehicle_depart(newVehicle* vehicle, int time) {
        string ownerName = vehicle->getName();
        string str = "";
        if (mapVehicle.find(ownerName) != mapVehicle.end()) {

            auto& vec = mapVehicle[ownerName];
            auto it = vec.begin();
            for (; it != vec.end(); it++) {
                //同一辆车
                if ((*it)->getVehicle() == vehicle->getVehicle()) {
                    int arrive = mapArrive[vehicle];
                    double pay = (*it)->get_charge(arrive, time);
                    double discount = mapCard[ownerName]->get_discount();
                    mapCard[ownerName]->min_balance(discount * pay);
                    str += vehicle->getVehicle() + ":" + to_string((double)discount * pay) + "\n";
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
        return str;
    }
    string print_status() {
        string str = "";
        str+= "ParkSystem:\n";
        for (auto it = mapCard.begin(); it != mapCard.end(); it++) {
            //name
            string name = (*it).first;
            // std::cout << name << ":\n";
            //std::cout << "card:" << (*it).second->getcardNum() << "\n";

            str += name + "\n";
            str+= "card:" + (*it).second->getcardNum() + "\n";

            for (auto& v : mapVehicle) {
                if (v.first == name) {
                    auto& vec = v.second;
                    if (vec.size() > 0) {
                        for (auto p : vec) {
                            str += p->getVehicle() + "\n";
                            //std::cout << p->getVehicle() << " ";
                        }
                        //std::cout << "\n";
                        //str += "\n";
                    }
                }
            }
        }

        //std::cout << mapCard.size() << " " << mapArrive.size() << " " << sum << "\n";
        str += to_string(mapCard.size()) + " " + to_string(mapArrive.size()) + " " + to_string(sum) + "\n";
        return str;
    }
    //void print_people();
};


void A() {
    Card* card1 = new Card("card001", "xiaobing", 100);
    Card* monthcard1 = new MonthCard("monthcard001", "xiaohong", 50);
    Card* yearcard1 = new YearCard("yearcard001", "xiaoming", 80);
    string str = "";
    str += to_string(card1->get_balance()) + "\n";
    str += to_string(monthcard1->get_balance()) + "\n";
    str += to_string(yearcard1->get_balance()) + "\n";
    str += to_string(card1->get_discount()) + "\n";
    str += to_string(monthcard1->get_discount()) + "\n";
    str += to_string(yearcard1->get_discount()) + "\n";
    

    newCard* newcard1 = new newCard("card001", "xiaobing", 100);
    newCard* newmonthcard1 = new newMonthCard("monthcard001", "xiaohong", 50);
    newCard* newyearcard1 = new newYearCard("yearcard001", "xiaoming", 80);
    string newstr = "";
    newstr += to_string(newcard1->get_balance()) + "\n";
    newstr += to_string(newmonthcard1->get_balance()) + "\n";
    newstr += to_string(newyearcard1->get_balance()) + "\n";
    newstr += to_string(newcard1->get_discount()) + "\n";
    newstr += to_string(newmonthcard1->get_discount()) + "\n";
    newstr += to_string(newyearcard1->get_discount()) + "\n";

    VERIFY_TRUE(newstr == str, 73);
}


void B() {
    Vehicle* car1 = new Car("suA8888", "xiaoming", 5);
    Vehicle* car2 = new Car("suA9999", "xiaohong", 7);
    Vehicle* bicycle1 = new Bicycle("ofo001", "xiaoming");
    Vehicle* bicycle2 = new Bicycle("ofo002", "xiaohong");
    Vehicle* bicycle3 = new Bicycle("ofo003", "xiaogang");
    string str = "";
    
    str += to_string(car1->get_charge(8, 10)) + "\n";
    str += to_string(car2->get_charge(8, 9)) + "\n";
    str += to_string(bicycle1->get_charge(8, 9)) + "\n";
    str += to_string(bicycle2->get_charge(8, 10)) + "\n";
    str += to_string(bicycle3->get_charge(8, 11)) + "\n";


    newVehicle* newcar1 = new newCar("suA8888", "xiaoming", 5);
    newVehicle* newcar2 = new newCar("suA9999", "xiaohong", 7);
    newVehicle* newbicycle1 = new newBicycle("ofo001", "xiaoming");
    newVehicle* newbicycle2 = new newBicycle("ofo002", "xiaohong");
    newVehicle* newbicycle3 = new newBicycle("ofo003", "xiaogang");
    string newstr = "";

    newstr += to_string(newcar1->get_charge(8, 10)) + "\n";
    newstr += to_string(newcar2->get_charge(8, 9)) + "\n";
    newstr += to_string(newbicycle1->get_charge(8, 9)) + "\n";
    newstr += to_string(newbicycle2->get_charge(8, 10)) + "\n";
    newstr += to_string(newbicycle3->get_charge(8, 11)) + "\n";
    
    VERIFY_TRUE(str == newstr, 144);

}

void C() {

    ParkSystem* park_system = new ParkSystem();
    Card* monthcard1 = new MonthCard("monthcard001", "xiaohong", 50);
    Card* yearcard1 = new YearCard("yearcard001", "xiaoming", 80);
    Card* card1 = new Card("card1", "xiaoli", 60);
    Vehicle* car1 = new Car("suA8888", "xiaohong", 5);
    Vehicle* bicycle2 = new Bicycle("ofo002", "xiaoming");
    Vehicle* car2 = new Car("suA9999", "xiaoming", 6);
    string str = "";
    park_system->add_card(monthcard1);
    park_system->add_card(yearcard1);
    park_system->add_card(card1);
    str += park_system->print_status();
    str += park_system->vehicle_arrive(car1, 8);
    str += park_system->print_status();
    str += park_system->vehicle_arrive(bicycle2, 14);
    str += park_system->print_status();
    str += park_system->vehicle_depart(car1, 10);
    str += park_system->vehicle_depart(bicycle2, 19);
    str += park_system->vehicle_arrive(car2, 6);
    str += park_system->vehicle_arrive(bicycle2, 7);
    str += park_system->print_status();
    

    newParkSystem* newpark_system = new newParkSystem();
    newCard* newmonthcard1 = new newMonthCard("monthcard001", "xiaohong", 50);
    newCard* newyearcard1 = new newYearCard("yearcard001", "xiaoming", 80);
    newCard* newcard1 = new newCard("card1", "xiaoli", 60);
    newVehicle* newcar1 = new newCar("suA8888", "xiaohong", 5);
    newVehicle* newbicycle2 = new newBicycle("ofo002", "xiaoming");
    newVehicle* newcar2 = new newCar("suA9999", "xiaoming", 6);
    string newstr = "";
    newpark_system->add_card(newmonthcard1);
    newpark_system->add_card(newyearcard1);
    newpark_system->add_card(newcard1);
    newstr += newpark_system->print_status();
    newstr += newpark_system->vehicle_arrive(newcar1, 8);
    newstr += newpark_system->print_status();
    newstr += newpark_system->vehicle_arrive(newbicycle2, 14);
    newstr += newpark_system->print_status();
    newstr += newpark_system->vehicle_depart(newcar1, 10);
    newstr += newpark_system->vehicle_depart(newbicycle2, 19);
    newstr += newpark_system->vehicle_arrive(newcar2, 6);
    newstr += newpark_system->vehicle_arrive(newbicycle2, 7);
    newstr += newpark_system->print_status();

    VERIFY_TRUE(newstr == str, 266);

}


void D() {
    //获得cardName
    ParkSystem* park_system = new ParkSystem();
    newParkSystem* newpark_system = new newParkSystem();

    string str = "";
    string newstr = "";

    vector<int> randNum = random_permut(6);
    for (unsigned i = 0; i < 6; ++i) {
        cardName[i] = cardType[i % 3] + to_string(randNum[i]);
    }
    //对应的是6个人 peopleName
    vector<Card*> cards(6);
    vector<newCard*> newcards(6);
    
    for (unsigned i = 0; i < 6; ++i) {
        if (i % 3 == 0) {
            cards[i] = new Card(cardName[i], peopleName[i], 1000);
            newcards[i] = new newCard(cardName[i], peopleName[i], 1000);
        }
        else if (i % 3 == 1) {
            cards[i] = new MonthCard(cardName[i], peopleName[i], 1000);
            newcards[i] = new newMonthCard(cardName[i], peopleName[i], 1000);
        }
        else if (i % 3 == 2) {
            cards[i] = new YearCard(cardName[i], peopleName[i], 1000);
            newcards[i] = new newYearCard(cardName[i], peopleName[i], 1000);
        }
        park_system->add_card(cards[i]);
        newpark_system->add_card(newcards[i]);
    }

    //12辆车
    //随机选人
    vector<Vehicle*> vehicles(12);
    vector<newVehicle*> newvehicles(12);
    srand((int)time(0));
    for (unsigned i = 0; i < 12; ++i) {
        int num = rand() % 6;
        int type = rand() % 2;
        if (type % 2 == 0) {
            int tmp = rand() % 10;
            vehicles[i] = new Car(vehicleNum[i], peopleName[num], tmp);
            newvehicles[i] = new newCar(vehicleNum[i], peopleName[num], tmp);
        }
        else {
            vehicles[i] = new Bicycle(vehicleNum[i], peopleName[num]);
            newvehicles[i] = new newBicycle(vehicleNum[i], peopleName[num]);
        }
    }
    for (unsigned i = 0; i < 24; i++) {
        int tmpTime = rand() % 10;
        str += park_system->vehicle_arrive(vehicles[i % 12], tmpTime);
        newstr += newpark_system->vehicle_arrive(newvehicles[i % 12], tmpTime);
        if (rand() % 3 == 0) {
            str += park_system->print_status();
            newstr += newpark_system->print_status();
        }
        int departTime = tmpTime + (rand() % 10);
        str += park_system->vehicle_depart(vehicles[i % 12], departTime);
        newstr += newpark_system->vehicle_depart(newvehicles[i % 12], departTime);
        if (rand() % 3 == 1) {
            str += park_system->print_status();
            newstr += newpark_system->print_status();
        }
    }
    VERIFY_TRUE(str == newstr, 318);


}

void E() {
    D();
}

void F() {
    D();
}

void G() {
    D();
}

void H() {
    D();
}

void I() {
    D();
}

void J() {
    D();
}



int main()
{
    int num;
    std::cin >> num;
    

    switch (num) {
    case 1: try { A(); }
          catch (std::exception e) { std::cout << 0 << std::endl; }break;
    case 2: try { B(); }
          catch (std::exception e) { std::cout << 0 << std::endl; }break;
    case 3: try { C(); }
          catch (std::exception e) { std::cout << 0 << std::endl; }break;
    case 4: try { D(); }
          catch (std::exception e) { std::cout << 0 << std::endl; }break;
    case 5: try { E(); }
          catch (std::exception e) { std::cout << 0 << std::endl; }break;
    case 6: try { F(); }
          catch (std::exception e) { std::cout << 0 << std::endl; }break;
    case 7: try { G(); }
          catch (std::exception e) { std::cout << 0 << std::endl; }break;
    case 8: try { H(); }
          catch (std::exception e) { std::cout << 0 << std::endl; }break;
    case 9: try { I(); }
          catch (std::exception e) { std::cout << 0 << std::endl; }break;
    case 10: try { J(); }
           catch (std::exception e) { std::cout << 0 << std::endl; }break;
    default: break;
    }
}
