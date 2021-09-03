#include <cstdlib>
#include <ctime>
#include<iostream>
#include <fstream>
#include<stdlib.h>
#include <experimental/random>
#include"List.h"
using namespace std;
int main(int argc,char*argv[])
{
	List head = init();

	int choice = 0;
	int index,val;
	while(std::cin >> choice){
		switch(choice){
			case 1:{
				std::cin >> index >> val;
				std::cout<<insert(head,index,val)<<std::endl;;
				break;
			}
			case 2:{
				std::cin >> index ;
				std::cout<<erase(head,index)<<std::endl;
				break;
			}
			case 3:{
				show(head);
				break;
			}
			case 4:{
				clear(head);
			}
		}

	}


	// for generate testing files
	// std::srand(std::time(nullptr));
	// int cnt = atoi(argv[1]); // how many times
	// int num = atoi(argv[2]); // for choice 
	// std::string file_name(argv[3]); //for inputfile
	// ofstream file;
  	// file.open (file_name);

	// int index = 0;
	// int val = 0;
	// while(cnt--){
	// 	if(sz<0){
	// 		return -1;
	// 	}
	// 	int choice = std::experimental::randint(1, num);
	// 	file << choice<<" ";
	// 	switch(choice){
	// 		case 1:{
	// 			int next_choice = std::experimental::randint(1, 2);
	// 			val = std::rand();
	// 			if(next_choice == 1){
	// 				index = std::experimental::randint(0, sz == 0? 0 : sz-1);
	// 			}else{
	// 				index = std::experimental::randint(sz,sz+100);
	// 			}
	// 			std::cout<<insert(head,index,val)<<std::endl;
	// 			file<<" "<<index<<" "<<val<<"  "<<std::endl;
	// 			break;
	// 		}
	// 		case 2:{
	// 			int next_choice = std::experimental::randint(1, 2);
	// 			if(next_choice == 1){
	// 				index = std::experimental::randint(0, sz == 0? 0 : sz-1);
	// 			}else{
	// 				index = std::experimental::randint(sz,sz+100);
	// 			}
	// 			file <<" "<<index<<" "<<std::endl;
	// 			std::cout<<erase(head,index)<<std::endl;
	// 			break;
	// 		}
	// 		case 3:{
	// 			show(head);
	// 			file<<std::endl;
	// 			break;
	// 		}
	// 		case 4:{
	// 			clear(head);
	// 			file<<std::endl;
	// 			break;
	// 		}
	// 	}
	// }
	// file.close();


	clear(head);
}