#include <iostream>
#include "byte_stream.hh"
#include <assert.h>     /* assert */

using namespace std;

// command: g++ test.cc byte_stream.cc


// test for 
void test_capacity(){
    ByteStream stream(2);
    assert(2 == stream.write("cat"));
    assert(false == stream.eof());
    assert(0 == stream.bytes_read());
    assert(2 == stream.bytes_written());
    assert(0 == stream.remaining_capacity());
    assert(2 == stream.buffer_size());
    assert("ca" == stream.peek_output(2));
    assert(0 == stream.write("t"));
    assert(false == stream.input_ended());
    assert(false == stream.buffer_empty());
    assert(false == stream.eof());
    assert(0 == stream.bytes_read());
    assert(2 == stream.bytes_written());
    assert(0 == stream.remaining_capacity());
    assert(2 == stream.buffer_size());
    assert("ca" == stream.peek_output(2));
}


void test_write_once(){
    ByteStream stream(15);
    stream.write("cat");
    assert(false == stream.input_ended());
    assert(false == stream.buffer_empty());
    assert(false == stream.eof());
    assert(0 == stream.bytes_read());
    assert(3 == stream.bytes_written());
    assert(12 == stream.remaining_capacity());
    assert(3 == stream.buffer_size());
    assert("cat" == stream.peek_output(3));
    
    stream.end_input();
    assert(true == stream.input_ended());
    assert(false == stream.eof());
    assert(0 == stream.bytes_read());
    assert(3 == stream.bytes_written());
    assert(12 == stream.remaining_capacity());
    assert(3 == stream.buffer_size());
    assert("cat" == stream.peek_output(3));

    stream.pop_output(3);

    assert(true == stream.input_ended());
    assert(true == stream.buffer_empty());
    assert(true == stream.eof());
    assert(3 == stream.bytes_read());
    assert(3 == stream.bytes_written());
    assert(15 == stream.remaining_capacity());
    assert(0 == stream.buffer_size());

}

void test_write_twice(){
    ByteStream stream(15);


    stream.write("cat");
    assert(false == stream.input_ended());
    assert(false == stream.buffer_empty());
    assert(false == stream.eof());
    assert(0 == stream.bytes_read());
    assert(3 == stream.bytes_written());
    assert(12 == stream.remaining_capacity());
    assert(3 == stream.buffer_size());
    assert("cat" == stream.peek_output(3));
    
    stream.write("tac");
    assert(false == stream.input_ended());
    assert(false == stream.buffer_empty());
    assert(false == stream.eof());
    assert(0 == stream.bytes_read());
    assert(6 == stream.bytes_written());
    assert(9 == stream.remaining_capacity());
    assert(6 == stream.buffer_size());
    assert("cattac" == stream.peek_output(6));
    
    stream.end_input();
    assert(true == stream.input_ended());
    assert(false == stream.buffer_empty());
    assert(false == stream.eof());
    assert(0 == stream.bytes_read());
    assert(6 == stream.bytes_written());
    assert(9 == stream.remaining_capacity());
    assert(6 == stream.buffer_size());
    assert("cattac" == stream.peek_output(6));    

    stream.pop_output(2);
    assert(true == stream.input_ended());
    assert(false == stream.buffer_empty());
    assert(false == stream.eof());
    assert(2 == stream.bytes_read());
    assert(6 == stream.bytes_written());
    assert(11 == stream.remaining_capacity());
    assert(4 == stream.buffer_size());
    assert("ttac" == stream.peek_output(6));    

    stream.pop_output(4);
    assert(true == stream.input_ended());
    assert(true == stream.buffer_empty());
    assert(true == stream.eof());
    assert(6 == stream.bytes_read());
    assert(6 == stream.bytes_written());
    assert(15 == stream.remaining_capacity());
    assert(0 == stream.buffer_size()); 
}

int main(int argc,char*argv[]){
    test_capacity();
    test_write_once();
    test_write_twice();
}