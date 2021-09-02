#include "Queue.h"

#include <cstdlib>
#include <ctime>
#include<iostream>
#include <fstream>
#include<stdlib.h>
#include <experimental/random>
#include"List.h"
using namespace std;
extern int sz;
int main(int argc,char*argv[])
{
	Queue q;
    init(q);

	int choice = 0;
	int index,val;
	while(std::cin >> choice){
		switch(choice){
			case 1:{
				std::cin >> val;
				push(q,val);
				break;
			}
			case 2:{
				cout<<pop(q)<<endl;
				break;
			}
			case 3:{
				cout<<empty(q)<<endl;
				break;
			}
			case 4:{
				show(q);
                break;
			}
            case 5:{
				cout<<front(q)<<endl;
                break;
			}
            case 6:{
				cout<<back(q)<<endl;
                break;
			}
		}

	}


	// //for generate testing files
	// std::srand(std::time(nullptr));
	// int cnt = atoi(argv[1]); // how many times
	// int num = atoi(argv[2]); // for choice 
	// std::string file_name(argv[3]); //for inputfile
	// ofstream file;
  	// file.open (file_name);

	// int index = 0;
	// int val = 0;
	// while(cnt--){
	// 	int choice = std::experimental::randint(1, num);
	// 	file << choice<<" ";
	// 	switch(choice){
	// 		case 1:{
	// 			val = std::rand();
	// 			push(q,val);
	// 			file<<val<<"  "<<std::endl;
    //             //cout<<endl;
	// 			break;
	// 		}
	// 		case 2:{
	// 			cout<<pop(q)<<endl;
	// 			file<<std::endl;
	// 			break;
	// 		}
	// 		case 3:{
	// 			cout<<empty(q)<<endl;
	// 			file<<std::endl;
	// 			break;
	// 		}
	// 		case 4:{
	// 			show(q);
	// 			file<<std::endl;
	// 			break;
	// 		}
    //         case 5:{
	// 			cout<<front(q)<<endl;
	// 			file<<std::endl;
	// 			break;
	// 		}
    //         case 6:{
	// 			cout<<back(q)<<endl;
	// 			file<<std::endl;
	// 			break;
	// 		}
	// 	}
	// }
	// file.close();

}