#include "Queue.h"

#include<iostream>
#include<string>
using namespace std;
int main(int argc,char*argv[]){
    Queue q;
    init(q);
    push(q, 1);
    push(q, 2);
    push(q, 3);
    cout << front(q) << endl;
    cout << back(q) << endl;
    pop(q);
    cout << front(q) << endl;
    show(q);
}