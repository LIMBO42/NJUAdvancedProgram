#include<iostream>
#include<fstream>
#include<string>
#include"fibonacci.h"
using namespace std;
int main(int argc,char*argv[]){
    std::ifstream test_in(argv[1]);    /* This stream reads from test's input file   */
    if(!test_in.is_open()){
        std::cout << "Error opening file " << argv[1] << std::endl;
        return -1;
    }
    int n;
    test_in >> n;
    std::cout << fibonacci(n) << std::endl; 
}