#include"List.h"
#include<iostream>
using namespace std;
int main()
{
	List head = init();
	cout << insert(head, 0, 8) << endl;
	cout << insert(head, 0, 9) << endl;
	cout << insert(head, 1, 10) << endl;
	cout << insert(head, 10, 1) << endl;
	cout << insert(head, 3, 11) << endl;
	show(head);
	cout << erase(head, 0) << endl;
	cout << erase(head, 10) << endl;
	show(head);
	clear(head);
	cout << insert(head, 0, 8) << endl;
	cout << erase(head, 0) << endl;
	return 0;
}
 