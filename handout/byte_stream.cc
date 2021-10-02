#include "byte_stream.hh"

#include <iostream>
using namespace std;

ByteStream::ByteStream(const size_t capacity) {  }

size_t ByteStream::write(const string &data) {
    
    return {};
}

string ByteStream::peek_output(const size_t len) const {
    
    return {};
}

void ByteStream::pop_output(const size_t len) {  }


std::string ByteStream::read(const size_t len) {
    
    return {};
}

void ByteStream::end_input() {}

bool ByteStream::input_ended() const { return {}; }

size_t ByteStream::buffer_size() const { return {}; }

bool ByteStream::buffer_empty() const { return {}; }

bool ByteStream::eof() const { return false; }

size_t ByteStream::bytes_written() const { return {}; }

size_t ByteStream::bytes_read() const { return {}; }

size_t ByteStream::remaining_capacity() const { return {}; }