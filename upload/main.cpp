#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <list>
#include <numeric>
#include <random>
#include <stdexcept>
#include <iostream>
#include <cassert>
#include <gtest/gtest.h>
#include "matrix.hpp"


// command ::g++ main.cpp -lgtest -lpthread

using std::exception;
static bool ThrowsException(const std::function<void()> &function, exception type) {
  bool expected_type_thrown = false;
  try {
    function();
  } catch (const std::out_of_range &e) {
    expected_type_thrown = true; 
  } catch (const std::exception &e){
    
  }
  std::cout << expected_type_thrown << std::endl;
  return expected_type_thrown;
}

void test1(){
    auto matrix = std::make_unique<RowMatrix<int>>(2, 2);
    // Source contains too few elements
    std::vector<int> source0(3);
    std::iota(source0.begin(), source0.end(), 0);
    EXPECT_TRUE(ThrowsException([&]() { matrix->FillFrom(source0); }, std::out_of_range("")));
}

void test2(){
    auto matrix = std::make_unique<RowMatrix<int>>(2, 2);
    // Source contains too many elements
    std::vector<int> source0(5);
    std::iota(source0.begin(), source0.end(), 0);
    ThrowsException([&]() { matrix->FillFrom(source0); }, std::out_of_range(""));
}

void test3(){
    auto matrix = std::make_unique<RowMatrix<int>>(2, 2);
    std::vector<int> source2(4);
    std::iota(source2.begin(), source2.end(), 0);
    EXPECT_NO_THROW(matrix->FillFrom(source2));
    for (int i = 0; i < matrix->GetRowCount(); i++) {
        for (int j = 0; j < matrix->GetColumnCount(); j++) {
            const int expected = (i * matrix->GetColumnCount()) + j;
            EXPECT_EQ(expected, matrix->GetElement(i, j));
        }
  }
  EXPECT_TRUE(ThrowsException([&]() { matrix->GetElement(0, -1); }, std::out_of_range("")));
  EXPECT_TRUE(ThrowsException([&]() { matrix->GetElement(-1, 0); }, std::out_of_range("")));
  EXPECT_TRUE(ThrowsException([&]() { matrix->GetElement(0, 2); }, std::out_of_range("")));
  EXPECT_TRUE(ThrowsException([&]() { matrix->GetElement(2, 0); }, std::out_of_range("")));
}



int main(int argc, char*argv[]){
    test1();
}