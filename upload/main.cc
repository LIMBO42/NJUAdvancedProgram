#include "byte_stream.hh"
#include "byte_stream_test_harness.hh"

#include <exception>
#include <iostream>
#include <cstdlib> 
#include <ctime> 
using namespace std;



bool test1() {
  try {
    ByteStreamTestHarness test{"overwrite", 2};

    test.execute(Write{"cat"}.with_bytes_written(2));

    test.execute(InputEnded{false});
    test.execute(BufferEmpty{false});
    test.execute(Eof{false});
    test.execute(BytesRead{0});
    test.execute(BytesWritten{2});
    test.execute(RemainingCapacity{0});
    test.execute(BufferSize{2});
    test.execute(Peek{"ca"});

    test.execute(Write{"t"}.with_bytes_written(0));

    test.execute(InputEnded{false});
    test.execute(BufferEmpty{false});
    test.execute(Eof{false});
    test.execute(BytesRead{0});
    test.execute(BytesWritten{2});
    test.execute(RemainingCapacity{0});
    test.execute(BufferSize{2});
    test.execute(Peek{"ca"});
  } catch (const exception &e) {
    cerr << "Exception: " << e.what() << endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

bool test2() {
  try {
    ByteStreamTestHarness test{"overwrite-clear-overwrite", 2};

    test.execute(Write{"cat"}.with_bytes_written(2));
    test.execute(Pop{2});
    test.execute(Write{"tac"}.with_bytes_written(2));

    test.execute(InputEnded{false});
    test.execute(BufferEmpty{false});
    test.execute(Eof{false});
    test.execute(BytesRead{2});
    test.execute(BytesWritten{4});
    test.execute(RemainingCapacity{0});
    test.execute(BufferSize{2});
    test.execute(Peek{"ta"});
  } catch (const exception &e) {
    cerr << "Exception: " << e.what() << endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

bool test3() {
  try {
    ByteStreamTestHarness test{"overwrite-pop-overwrite", 2};

    test.execute(Write{"cat"}.with_bytes_written(2));
    test.execute(Pop{1});
    test.execute(Write{"tac"}.with_bytes_written(1));

    test.execute(InputEnded{false});
    test.execute(BufferEmpty{false});
    test.execute(Eof{false});
    test.execute(BytesRead{1});
    test.execute(BytesWritten{3});
    test.execute(RemainingCapacity{0});
    test.execute(BufferSize{2});
    test.execute(Peek{"at"});
  } catch (const exception &e) {
    cerr << "Exception: " << e.what() << endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
bool test4() {
  try {
    ByteStreamTestHarness test{"long-stream", 3};

    test.execute(Write{"abcdef"}.with_bytes_written(3));
    test.execute(Peek{"abc"});
    test.execute(Pop{1});

    for (unsigned int i = 0; i < 99997; i++) {
      test.execute(RemainingCapacity{1});
      test.execute(BufferSize{2});
      test.execute(Write{"abc"}.with_bytes_written(1));
      test.execute(RemainingCapacity{0});
      test.execute(Peek{"bca"});
      test.execute(Pop{1});

      test.execute(RemainingCapacity{1});
      test.execute(BufferSize{2});
      test.execute(Write{"bca"}.with_bytes_written(1));
      test.execute(RemainingCapacity{0});
      test.execute(Peek{"cab"});
      test.execute(Pop{1});

      test.execute(RemainingCapacity{1});
      test.execute(BufferSize{2});
      test.execute(Write{"cab"}.with_bytes_written(1));
      test.execute(RemainingCapacity{0});
      test.execute(Peek{"abc"});
      test.execute(Pop{1});
    }

    test.execute(EndInput{});
    test.execute(Peek{"bc"});
    test.execute(Pop{2});
    test.execute(Eof{true});
  } catch (const exception &e) {
    cerr << "Exception: " << e.what() << endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
bool test5() {
  try {
    ByteStreamTestHarness test{"construction", 15};
    test.execute(InputEnded{false});
    test.execute(BufferEmpty{true});
    test.execute(Eof{false});
    test.execute(BytesRead{0});
    test.execute(BytesWritten{0});
    test.execute(RemainingCapacity{15});
    test.execute(BufferSize{0});
  } catch (const exception &e) {
    cerr << "Exception: " << e.what() << endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
bool test6() {
  try {
    ByteStreamTestHarness test{"construction-end", 15};
    test.execute(EndInput{});
    test.execute(InputEnded{true});
    test.execute(BufferEmpty{true});
    test.execute(Eof{true});
    test.execute(BytesRead{0});
    test.execute(BytesWritten{0});
    test.execute(RemainingCapacity{15});
    test.execute(BufferSize{0});
  } catch (const exception &e) {
    cerr << "Exception: " << e.what() << endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
bool test7() {
  try {
    ByteStreamTestHarness test{"write-end-pop", 15};

    test.execute(Write{"cat"});

    test.execute(InputEnded{false});
    test.execute(BufferEmpty{false});
    test.execute(Eof{false});
    test.execute(BytesRead{0});
    test.execute(BytesWritten{3});
    test.execute(RemainingCapacity{12});
    test.execute(BufferSize{3});
    test.execute(Peek{"cat"});

    test.execute(EndInput{});

    test.execute(InputEnded{true});
    test.execute(BufferEmpty{false});
    test.execute(Eof{false});
    test.execute(BytesRead{0});
    test.execute(BytesWritten{3});
    test.execute(RemainingCapacity{12});
    test.execute(BufferSize{3});
    test.execute(Peek{"cat"});

    test.execute(Pop{3});

    test.execute(InputEnded{true});
    test.execute(BufferEmpty{true});
    test.execute(Eof{true});
    test.execute(BytesRead{3});
    test.execute(BytesWritten{3});
    test.execute(RemainingCapacity{15});
    test.execute(BufferSize{0});
  } catch (const exception &e) {
    cerr << "Exception: " << e.what() << endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
bool test8() {
  try {
    ByteStreamTestHarness test{"write-pop-end", 15};

    test.execute(Write{"cat"});

    test.execute(InputEnded{false});
    test.execute(BufferEmpty{false});
    test.execute(Eof{false});
    test.execute(BytesRead{0});
    test.execute(BytesWritten{3});
    test.execute(RemainingCapacity{12});
    test.execute(BufferSize{3});
    test.execute(Peek{"cat"});

    test.execute(Pop{3});

    test.execute(InputEnded{false});
    test.execute(BufferEmpty{true});
    test.execute(Eof{false});
    test.execute(BytesRead{3});
    test.execute(BytesWritten{3});
    test.execute(RemainingCapacity{15});
    test.execute(BufferSize{0});

    test.execute(EndInput{});

    test.execute(InputEnded{true});
    test.execute(BufferEmpty{true});
    test.execute(Eof{true});
    test.execute(BytesRead{3});
    test.execute(BytesWritten{3});
    test.execute(RemainingCapacity{15});
    test.execute(BufferSize{0});
  } catch (const exception &e) {
    cerr << "Exception: " << e.what() << endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
bool test9() {
  try {
    ByteStreamTestHarness test{"write-pop2-end", 15};

    test.execute(Write{"cat"});

    test.execute(InputEnded{false});
    test.execute(BufferEmpty{false});
    test.execute(Eof{false});
    test.execute(BytesRead{0});
    test.execute(BytesWritten{3});
    test.execute(RemainingCapacity{12});
    test.execute(BufferSize{3});
    test.execute(Peek{"cat"});

    test.execute(Pop{1});

    test.execute(InputEnded{false});
    test.execute(BufferEmpty{false});
    test.execute(Eof{false});
    test.execute(BytesRead{1});
    test.execute(BytesWritten{3});
    test.execute(RemainingCapacity{13});
    test.execute(BufferSize{2});
    test.execute(Peek{"at"});

    test.execute(Pop{2});

    test.execute(InputEnded{false});
    test.execute(BufferEmpty{true});
    test.execute(Eof{false});
    test.execute(BytesRead{3});
    test.execute(BytesWritten{3});
    test.execute(RemainingCapacity{15});
    test.execute(BufferSize{0});

    test.execute(EndInput{});

    test.execute(InputEnded{true});
    test.execute(BufferEmpty{true});
    test.execute(Eof{true});
    test.execute(BytesRead{3});
    test.execute(BytesWritten{3});
    test.execute(RemainingCapacity{15});
    test.execute(BufferSize{0});
  } catch (const exception &e) {
    cerr << "Exception: " << e.what() << endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

bool test10() {
  try {
    ByteStreamTestHarness test{"write-write-end-pop-pop", 15};

    test.execute(Write{"cat"});

    test.execute(InputEnded{false});
    test.execute(BufferEmpty{false});
    test.execute(Eof{false});
    test.execute(BytesRead{0});
    test.execute(BytesWritten{3});
    test.execute(RemainingCapacity{12});
    test.execute(BufferSize{3});
    test.execute(Peek{"cat"});

    test.execute(Write{"tac"});

    test.execute(InputEnded{false});
    test.execute(BufferEmpty{false});
    test.execute(Eof{false});
    test.execute(BytesRead{0});
    test.execute(BytesWritten{6});
    test.execute(RemainingCapacity{9});
    test.execute(BufferSize{6});
    test.execute(Peek{"cattac"});

    test.execute(EndInput{});

    test.execute(InputEnded{true});
    test.execute(BufferEmpty{false});
    test.execute(Eof{false});
    test.execute(BytesRead{0});
    test.execute(BytesWritten{6});
    test.execute(RemainingCapacity{9});
    test.execute(BufferSize{6});
    test.execute(Peek{"cattac"});

    test.execute(Pop{2});

    test.execute(InputEnded{true});
    test.execute(BufferEmpty{false});
    test.execute(Eof{false});
    test.execute(BytesRead{2});
    test.execute(BytesWritten{6});
    test.execute(RemainingCapacity{11});
    test.execute(BufferSize{4});
    test.execute(Peek{"ttac"});

    test.execute(Pop{4});

    test.execute(InputEnded{true});
    test.execute(BufferEmpty{true});
    test.execute(Eof{true});
    test.execute(BytesRead{6});
    test.execute(BytesWritten{6});
    test.execute(RemainingCapacity{15});
    test.execute(BufferSize{0});
  } catch (const exception &e) {
    cerr << "Exception: " << e.what() << endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

bool test11() {
  try {
    ByteStreamTestHarness test{"write-pop-write-end-pop", 15};

    test.execute(Write{"cat"});

    test.execute(InputEnded{false});
    test.execute(BufferEmpty{false});
    test.execute(Eof{false});
    test.execute(BytesRead{0});
    test.execute(BytesWritten{3});
    test.execute(RemainingCapacity{12});
    test.execute(BufferSize{3});
    test.execute(Peek{"cat"});

    test.execute(Pop{2});

    test.execute(InputEnded{false});
    test.execute(BufferEmpty{false});
    test.execute(Eof{false});
    test.execute(BytesRead{2});
    test.execute(BytesWritten{3});
    test.execute(RemainingCapacity{14});
    test.execute(BufferSize{1});
    test.execute(Peek{"t"});

    test.execute(Write{"tac"});

    test.execute(InputEnded{false});
    test.execute(BufferEmpty{false});
    test.execute(Eof{false});
    test.execute(BytesRead{2});
    test.execute(BytesWritten{6});
    test.execute(RemainingCapacity{11});
    test.execute(BufferSize{4});
    test.execute(Peek{"ttac"});

    test.execute(EndInput{});

    test.execute(InputEnded{true});
    test.execute(BufferEmpty{false});
    test.execute(Eof{false});
    test.execute(BytesRead{2});
    test.execute(BytesWritten{6});
    test.execute(RemainingCapacity{11});
    test.execute(BufferSize{4});
    test.execute(Peek{"ttac"});

    test.execute(Pop{4});

    test.execute(InputEnded{true});
    test.execute(BufferEmpty{true});
    test.execute(Eof{true});
    test.execute(BytesRead{6});
    test.execute(BytesWritten{6});
    test.execute(RemainingCapacity{15});
    test.execute(BufferSize{0});
  } catch (const exception &e) {
    cerr << "Exception: " << e.what() << endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

bool test12() {
  try {
    srand((unsigned)time(0)); 
    auto rd = rand();
    const size_t NREPS = 1000;
    const size_t MIN_WRITE = 10;
    const size_t MAX_WRITE = 200;
    const size_t CAPACITY = MAX_WRITE * NREPS;

    {
      ByteStreamTestHarness test{"many writes", CAPACITY};

      size_t acc = 0;
      for (size_t i = 0; i < NREPS; ++i) {
        rd = rand();
        const size_t size = MIN_WRITE + (rd % (MAX_WRITE - MIN_WRITE));
        string d(size, 0);
        rd = rand();
        generate(d.begin(), d.end(), [&] { return 'a' + (rd % 26); });

        test.execute(Write{d}.with_bytes_written(size));
        acc += size;

        test.execute(InputEnded{false});
        test.execute(BufferEmpty{false});
        test.execute(Eof{false});
        test.execute(BytesRead{0});
        test.execute(BytesWritten{acc});
        test.execute(RemainingCapacity{CAPACITY - acc});
        test.execute(BufferSize{acc});
      }
    }
  } catch (const exception &e) {
    cerr << "Exception: " << e.what() << endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
  test1();
  test2();
  test3();
  test4();
  test5();
  test6();
  test7();
  test8();
  test9();
  test10();
  test11();
  test12();
}