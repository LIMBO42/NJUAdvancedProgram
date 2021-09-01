  
#include"List.h"
#include<iostream>
using namespace std;
int main()
{
	//part1
	List head = init();
	cout << insert(head, 0, 8) << endl;
	cout << insert(head, 0, 9) << endl;
	cout << insert(head, 1, 10) << endl;
	cout << insert(head, 10, 1) << endl;
	show(head);
	cout << erase(head, 0) << endl;
	cout << erase(head, 10) << endl;
	show(head);
	clear(head);
	cout << insert(head, 0, 8) << endl;
	cout << erase(head, 0) << endl;

	// //part2
	// Queue q;
	// init(q);
	// push(q, 1);
	// push(q, 2);
	// push(q, 3);
	// cout << front(q) << endl;
	// cout << back(q) << endl;
	// pop(q);
	// cout << front(q) << endl;
	// show(q);
	// return 0;
}