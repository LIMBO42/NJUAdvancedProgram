#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool is_empty_file(std::ifstream& pFile)
{
    return pFile.peek() == std::ifstream::traits_type::eof();
}
int main(int argc, char const *argv[])
{
 
	ifstream test_in(argv[1]);    /* This stream reads from test's input file   */
	ifstream test_out(argv[2]);   /* This stream reads from test's output file  */
	ifstream user_out(argv[3]);   /* This stream reads from user's output file  */
    
	/* Your code here */
	/* If user's output is correct, return 0, otherwise return 1       */
	/* e.g.: Here the problem is: read n numbers and print their sum:  */
    
	string user_output,real_output;
    
    while(user_out >> user_output && test_out >> real_output){
    if(user_output != real_output){
      return 1;
    }
  }


  
    if(!test_out.eof() || !user_out.eof()){
         return 1;
    }
    return 0;
 
}