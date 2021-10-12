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
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "matrix.hpp"
#include "Matrix.hpp"

// command ::g++ main.cpp -lgtest -lpthread


// 1:pass 0: not pass

using std::exception;
static bool ThrowsException(const std::function<void()> &function) {
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

static bool ThrowsNoException(const std::function<void()> &function) {
  bool expected_no_exception_thrown = true;
  try {
    function();
  } catch (const std::exception &e){
    expected_no_exception_thrown = false;
  }
  std::cout << expected_no_exception_thrown << std::endl;
  return expected_no_exception_thrown;
}

template <typename T>
static bool EXPECTEQUAL(const RowMatrix<T> * user,const Rowmatrix<T> * real) {
  bool equal = true;
  if(user->GetRowCount() != real->GetRowCount()||
      user->GetColumnCount() != real->GetColumnCount()){
    equal = false;
  }
  for(int i=0;i<user->GetRowCount();++i){
    for(int j=0;i<user->GetColumnCount();++j){
      if(user->GetElement(i,j)!=real->GetElement(i,j)){
        equal = false;
      }
    }
  }
  std::cout << equal << std::endl;
  return equal;
}

template <typename T>
static bool EXPECTNOEQUAL(const RowMatrix<T> * user,const Rowmatrix<T> * real) {
  bool notequal = !EXPECTEQUAL(user,real);
  return notequal;
}

void test1(){
    auto matrix = std::make_unique<RowMatrix<int>>(2, 2);
    // Source contains too few elements
    std::vector<int> source0(3);
    std::iota(source0.begin(), source0.end(), 0);
    ThrowsException([&]() { matrix->FillFrom(source0);});
}

void test2(){
    auto matrix = std::make_unique<RowMatrix<int>>(2, 2);
    // Source contains too many elements
    std::vector<int> source0(5);
    std::iota(source0.begin(), source0.end(), 0);
    ThrowsException([&]() { matrix->FillFrom(source0);});
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
  ThrowsException([&]() { matrix->GetElement(0, -1); });
  ThrowsException([&]() { matrix->GetElement(-1, 0); });
  ThrowsException([&]() { matrix->GetElement(0, 2); });
  ThrowsException([&]() { matrix->GetElement(2, 0); });
}

void test4(int line ,int col){
  srand (time(NULL));
  auto user_matrix1 = std::make_unique<RowMatrix<int>>(line, col);
  auto real_matrix1 = std::make_unique<Rowmatrix<int>>(line, col);
  auto user_matrix2 = std::make_unique<RowMatrix<int>>(line, col);
  auto real_matrix2 = std::make_unique<Rowmatrix<int>>(line, col);

  std::vector<int> vec1;
  std::vector<int> vec2;
  for(int i=0;i<line;++i){
    for(int j=0;j<col;++j){
      vec1.push_back(rand() % 100 - 50);
      vec2.push_back(rand() % 100 - 50);
    }
  }
  ThrowsNoException([&]() { user_matrix1->FillFrom(vec1);});
  ThrowsNoException([&]() { real_matrix2->FillFrom(vec1);});
  auto user_add = RowMatrixOperations<int>::Add(user_matrix1.get(), user_matrix2.get());
  auto real_add = RowmatrixOperations<int>::Add(real_matrix1.get(), real_matrix2.get());
  EXPECTEQUAL(user_add.get(),real_add.get());
}



int main(int argc, char*argv[]){
    test1();
}