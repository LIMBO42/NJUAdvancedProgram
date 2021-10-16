#include "solution.inline.hpp"
#include <iostream>
#include <cassert>

#define ASSERT_NO_ERROR(stat) {                            \
        bool has_except = false;                                \
        try{ stat } catch(std::exception& e) { has_except = true; }     \
        assert(!has_except);                                     \
    }                                                           \

#define ASSERT_ERROR(except, stat) {                            \
        bool has_except = false;                                \
        try{ stat } catch(except& e) { has_except = true; }     \
        assert(has_except);                                     \
    }                                                           \

#define ASSERT_ERROR_HANDLE(except, stat, handle) {                             \
        bool has_except = false;                                         \
        try{ stat } catch(except& e) { has_except = true; {handle} }     \
        assert(has_except);                                              \
    }                                                                    \


void test_optional() {
    optional<int> ptr0 = 1;
    assert(ptr0 && *ptr0 == 1);

    optional<int> ptr1 = nullptr;
    assert(!ptr1);

    ASSERT_ERROR(bad_optional_access,{
        optional<int> ptr;
        *ptr;
    })
    ASSERT_ERROR(bad_optional_access,{
        optional<int> ptr = nullptr;
        *ptr;
    })
}

void test_exception_iter_0() {
    auto r = Range(23, 132);
    assert(sum(r) == 8393);
}

void test_exception_iter_1() {
    auto r = Range(92184, 198234);
    assert(sum(r) == 15399361425);
}

void test_exception_iter_2() {
    auto r = Range(0, 5);
    assert(r.next() == 0);
    assert(r.next() == 1);
    assert(r.next() == 2);
    assert(r.next() == 3);
    assert(r.next() == 4);
    ASSERT_ERROR(StopIteration, r.next(); )
}

void test_exception_iter_3() {
    auto r = Range(10, 13);
    assert(r.next() == 10);
    assert(r.next() == 11);
    assert(r.next() == 12);
    ASSERT_ERROR(StopIteration, r.next(); )
}

void test_exception_iter_4() {
    auto r = Range(10, 13);
    assert(r.next() == 10);
    assert(r.next() == 11);
    assert(r.next() == 12);
    ASSERT_ERROR_HANDLE(StopIteration,
        r.next(); ,
        e.what(); )
}

argparser::ArgParser get_example_parser() {
    argparser::ArgParser parser("test");

    parser.argument<int>("int")
          .in_short('i');
    parser.argument<std::string>("str")
          .in_short('s')
          .set_default("beta");
    parser.argument<bool>("bool")
          .in_short('b');

    return parser;
}

void test_argparse_0() {
    std::vector<const char *> vec {"test", "-i", "100"};

    auto parser = get_example_parser();

    ASSERT_NO_ERROR( parser.parse(vec.size(), vec.data()); );

    assert(parser.get<int>("int") == 100);
    assert(parser.get<std::string>("str") == "beta");
    assert(parser.get<bool>("bool") == false);

    ASSERT_NO_ERROR( parser.get<int>("int"); )
    ASSERT_ERROR(argparser::ArgumentNotFound,
        parser.get<int>("asdfasdf"); )
    ASSERT_ERROR(argparser::ArgumentWrongType,
        parser.get<int>("str"); )
    ASSERT_ERROR(argparser::ArgumentWrongType,
        parser.get<float>("str"); )
}

void test_argparse_1() {
    std::vector<const char *> vec {"test", "-i", "not-a-integer"};

    auto parser = get_example_parser();

    ASSERT_ERROR_HANDLE(argparser::ArgumentError,
        parser.parse(vec.size(), vec.data());, 
        assert( e.what() == std::string("failed to parse argument 'int' : invalid argument 'not-a-integer' (stoi)") );
    );
}

void test_argparse_2() {
    std::vector<const char *> vec {"test", "-i", "-beta"};

    auto parser = get_example_parser();

    ASSERT_ERROR_HANDLE(argparser::ArgumentError,
        parser.parse(vec.size(), vec.data()); ,
        assert( e.what() == std::string("failed to parse argument 'int' : missing argument") );
    );
}

void test_argparse_3() {
    std::vector<const char *> vec {"test", "-i"};

    auto parser = get_example_parser();

    ASSERT_ERROR_HANDLE(argparser::ArgumentError,
        parser.parse(vec.size(), vec.data()); ,
        assert( e.what() == std::string("failed to parse argument 'int' : missing argument") );
    );
}

void test_argparse_4() {
    std::vector<const char *> vec {"test", "alpha", "-i", "100"};

    auto parser = get_example_parser();

    ASSERT_ERROR(argparser::UnrecongizedInput,
        parser.parse(vec.size(), vec.data()););
}

void test_argparse_5() {
    std::vector<const char *> vec {"test"};

    auto parser = get_example_parser();

    ASSERT_NO_ERROR( parser.parse(vec.size(), vec.data()); );

    ASSERT_ERROR(argparser::ArgumentError,
        parser.get<int>("int");
        // assert( e.what() == std::string("failed to parse argument 'int' : missing argument") );
    );
}

void test_argparse_6() {
    std::vector<const char *> vec {"test", "-i100", "--bool", "--str", "alpha"};

    auto parser = get_example_parser();

    ASSERT_NO_ERROR( parser.parse(vec.size(), vec.data()); );

    assert(parser.get<int>("int") == 100);
    assert(parser.get<std::string>("str") == "alpha");
    assert(parser.get<bool>("bool") == true);
}


int main(int argc, char* argv[]) {
    test_optional();
    test_exception_iter_0();
    test_exception_iter_1();
    test_exception_iter_2();
    test_exception_iter_3();
    test_exception_iter_4();
    test_argparse_0();
    test_argparse_1();
    test_argparse_2();
    test_argparse_3();
    test_argparse_4();
    test_argparse_5();
    test_argparse_6();
}