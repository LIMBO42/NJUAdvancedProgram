#include "hashmap.hpp"
// command: g++ -std=c++17 test.cpp


using namespace std;

#include <map>
#include <vector>
#include <utility>
#include <algorithm>
#include <sstream>
#include <set>
#include <iomanip>
#include <chrono>
using clock_type = std::chrono::high_resolution_clock;
using ns = std::chrono::nanoseconds;

const std::vector<std::pair<std::string, int> > vec {
    {"A", 3}, {"B", 2}, {"C", 1}, {"A", -5}, {"B", 3}, {"A", 5}, {"C", 1}
};

const std::vector<std::string> keys {"A", "B", "C", "Not found"};
template <typename Map1, typename Map2> bool check_map_equal(Map1& map, Map2& answer) {
    if (answer.empty() != map.empty() || answer.size() != map.size()) return false;

    for (const auto& [key, mapped] : answer) {
        if(map.contains(key) == false || map.at(key) != mapped) return false;
    }
    return true;
}

// Runtime assertion check
// Equivalent to CHECK_TRUE

struct VerifyTrueAssertionFailure {
    int line;
};

void VERIFY_TRUE(bool condition, int line) {
    if (!condition) {
        throw VerifyTrueAssertionFailure{line};
    }
    std::cout<<"pass"<<std::endl;
}


void A_iterator_for_each_basic() {
    /* Tests whether iterators are supported via a simple for-each loop
     * Uses begin() and end() of your HashMap, in addition to
     * the ctor and operators =, !=, and ++ of your iterator.
     */
    std::set<std::pair<int, int> > questions {
        {1, 1}, {2, 2}, {30, 30}, {140, 140}, {21, 21}
    };

    HashMap<int, int> map10;            // can your iterator traverse normal use case?
    for (const auto& pair : questions) {
        map10.insert(pair);
    }
    std::set<std::pair<int, int> > answers10;
    for (const auto& pair : map10) VERIFY_TRUE(answers10.insert(pair).second == true, __LINE__);

    VERIFY_TRUE(questions == answers10, __LINE__);
}

void B_iterator_for_each_edge() {
    /* Tests a few edge cases for your iterator, such as checking the bounds */
    std::set<std::pair<int, int> > questions {
        {0, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 4}
    };

    HashMap<int, int> map1(1);      // one bucket with all the elements
    HashMap<int, int> map5(5);      // exactly one per bucket
    HashMap<int, int> map10(100);   // a lot of empty buckets
    HashMap<int, int> empty;        // won't add anything to this one

    for (const auto& pair : questions) {
        map1.insert(pair);
        map5.insert(pair);
        map10.insert(pair);
    }
    std::set<std::pair<int, int> > answers1, answers5, answers10;
    for (const auto& pair : map1) VERIFY_TRUE(answers1.insert(pair).second == true, __LINE__);
    for (const auto& pair : map5) VERIFY_TRUE(answers5.insert(pair).second == true, __LINE__);
    for (const auto& pair : map10) VERIFY_TRUE(answers10.insert(pair).second == true, __LINE__);
    for (const auto& pair __attribute__((unused)) : empty) VERIFY_TRUE(false, __LINE__); // this should not run!

    VERIFY_TRUE(questions == answers1, __LINE__);
    VERIFY_TRUE(questions == answers5, __LINE__);
    VERIFY_TRUE(questions == answers10, __LINE__);
}

void C_iterator_operators() {
    /* Tests the more advanced operators, that are required
     * since the iterator can be a forward iterator */
    std::set<std::pair<int, int> > questions {
        {1, 1}, {2, 2}, {3, 3}
    };
    // Note to reader: yes, I spent so much time writing these awesome test cases
    // and then decided to make this part optional. What a great use of my spring break.
    // It's not like I have anything else to do, right?


    HashMap<int, int> map;            // can your iterator traverse normal use case?
    for (const auto& pair : questions) {
        map.insert(pair);
    }

    // note: we make no assumptions about which specifc element is in which order!
    auto iter = map.begin();                    // iter->0th element
    VERIFY_TRUE((*iter).first == (*iter).second, __LINE__);   // behavior of * operator
    VERIFY_TRUE(iter->first == iter->second, __LINE__);       // behavior of -> operator
    VERIFY_TRUE(iter == iter, __LINE__);                      // behavior of == operator
    VERIFY_TRUE(!(iter != iter), __LINE__);                   // behavior of != operator

    (*iter).second = -1;                        // behavior of * operator as an l-value
    VERIFY_TRUE((*iter).second == -1, __LINE__);    // behavior of * operator as an r-value
    iter->second = -2;                          // behavior of -> operator as an l-value
    VERIFY_TRUE(iter->second == -2, __LINE__);      // behavior of -> operator as an r-value

    // verify correct prefix/postfix behavior (this was very tedious)
    HashMap<int, int>::iterator iter0 = iter; // just to prove why type aliases are helpful
    auto iter1 = ++iter;                      // though auto usually works as well
    auto iter2 = ++iter;
    auto iter3 = ++iter;
    VERIFY_TRUE(iter == map.end(), __LINE__);
    iter = iter0;                       // iter->0
    auto& iter_ref = ++iter;            // iter/iter_ref->1
    VERIFY_TRUE(iter_ref == iter1, __LINE__);
    auto iter_ref_copy = ++iter_ref;    // iter_ref_copy->2, iter/iter_ref->2
    VERIFY_TRUE(iter_ref_copy == iter2, __LINE__);
    VERIFY_TRUE(iter_ref == iter2, __LINE__);

    auto iter_post = iter++;            // iter/iter_ref->3, iter_post->2
    VERIFY_TRUE(iter_post == iter2, __LINE__);
    VERIFY_TRUE(iter == iter3, __LINE__);
    iter_ref = map.begin();             // iter/iter_ref->0
    VERIFY_TRUE(iter == iter0, __LINE__);

    // Big LOL - see if you can actually trace the ++++++ operator.
    auto iter_chain_pre = ++++++iter;   // iter_chain_pre->3, iter/iter_ref->3
    VERIFY_TRUE(iter == iter3, __LINE__);
    VERIFY_TRUE(iter_chain_pre == iter3, __LINE__);
    iter_ref = map.begin();             // iter/iter_ref->0
    auto iter_chain_post = iter++++++;  // iter/iter_ref->1, iter_chain_post->0
    VERIFY_TRUE(iter == iter1, __LINE__);
    VERIFY_TRUE(iter_chain_post == iter0, __LINE__);
    // presumably if you pass the above ones, you probably have it working
    // so I'm not gonna think about what ++iter++++ would be
}

void D_iterator_algorithm() {
    /* Fully stresses your iterators by using an STL algorithm on them */
    HashMap<int, int> map;
    std::map<int, int> answer;

    for (int i = -17; i < 10; ++i) {
        map.insert({i, i*i});
    }

    std::copy(map.begin(), map.end(), std::inserter(answer, answer.begin()));
    VERIFY_TRUE(check_map_equal(map, answer), __LINE__);
    answer.clear();

    const auto& c_map = map;
    std::copy(c_map.begin(), c_map.end(), std::inserter(answer, answer.begin()));
    VERIFY_TRUE(check_map_equal(map, answer), __LINE__);
}

void E_const_iterator() {
    /* Tests the const-correctness of your iterator class by asking for const_iterators */
    std::set<std::pair<int, int> > questions {
        {1, 1}, {2, 2}, {3, 3}
    };

    /* testing const_iterator (iterator to const std::pair) */
    HashMap<int, int> map;
    for (const auto& pair : questions) map.insert(pair);
    const auto& const_map = map;
    std::set<std::pair<int, int> > answers;
    for (const auto& pair : const_map) VERIFY_TRUE(answers.insert(pair).second == true, __LINE__);
    VERIFY_TRUE(questions == answers, __LINE__);

    HashMap<int, int>::const_iterator iter = const_map.begin();

    VERIFY_TRUE((*iter).first == (*iter).second, __LINE__);   // behavior of * operator
    VERIFY_TRUE(iter->first == iter->second, __LINE__);       // behavior of -> operator
    VERIFY_TRUE(iter == iter, __LINE__);                      // behavior of == operator
    VERIFY_TRUE(!(iter != iter), __LINE__);                   // behavior of != operator

    VERIFY_TRUE(iter->second == (*iter).second, __LINE__);
    auto iter1 = ++iter;
    auto iter2 = ++iter;
    auto iter3 = iter++;
    VERIFY_TRUE(iter == const_map.end(), __LINE__);
    VERIFY_TRUE(iter3 == iter2, __LINE__);
    VERIFY_TRUE(iter1 != iter2, __LINE__);

    /* We could have the entire operator from 1C here, though that feels unnecessary */
}

void F_iterator_const_correctness() {
    /* Test the distinction between const iterator and const_iterator */
    std::set<std::pair<int, int> > questions {
        {1, 1}, {2, 2}, {3, 3}
    };

    HashMap<int, int> map;
    for (const auto& pair : questions) map.insert(pair);

    /* test behavior of const iterator */
    HashMap<int, int>::iterator iter = map.begin();
    const HashMap<int, int>::iterator c_iter = map.begin();
    const HashMap<int, int>::iterator& copy = iter;
    const HashMap<int, int>::iterator& copy_next = ++iter;

    VERIFY_TRUE(map.begin() == c_iter, __LINE__);
    VERIFY_TRUE(copy == iter, __LINE__);
    VERIFY_TRUE(copy_next == iter, __LINE__);
    VERIFY_TRUE(c_iter != iter, __LINE__);

    // the iterator is const, but the stuff the iterator points to is not const.
    (*c_iter).second = -1;                                   // behavior of * operator as an l-value
    VERIFY_TRUE((*c_iter).second == -1, __LINE__);              // behavior of * operator as an r-value
    c_iter->second = -2;                                     // behavior of -> operator as an l-value
    VERIFY_TRUE(c_iter->second == -2, __LINE__);                // behavior of -> operator as an r-value

    // these should not compile:
    // *iter = {0, 0};  // *iter is a std::pair<const K, M>, since K is const, = is deleted
    // ++c_iter;        // ++ is non-const

    VERIFY_TRUE(++++iter == map.end(), __LINE__);

    /* test behavior of const const_iterator */
    const auto& const_map = map;
    HashMap<int, int>::const_iterator const_iter = const_map.begin();
    const HashMap<int, int>::const_iterator c_const_iter_next = ++const_map.begin();
    const HashMap<int, int>::const_iterator c_const_iter = const_map.begin();

    // the key here is that these should compile.
    ++const_iter;
    VERIFY_TRUE((*c_const_iter).second == -2, __LINE__);
    VERIFY_TRUE(c_const_iter->second == -2, __LINE__);
    VERIFY_TRUE(const_iter == c_const_iter_next, __LINE__);
    VERIFY_TRUE(c_const_iter == const_map.begin(), __LINE__);

    // these should not compile:
    // ++c_const_iter;
    // c_const_iter->second = 2;
    // const_iter->second = 2;
}

void A_initializer_list_ctor() {
    /* Tests initializer_list via a simple example */
    std::map<std::string, int> answer {
        {"A", 3}, {"B", 2}, {"C", 1}, {"A", -5}, {"B", 3}, {"A", 5}, {"C", 1}
    };

    HashMap<std::string, int> map {
        {"A", 3}, {"B", 2}, {"C", 1}, {"A", -5}, {"B", 3}, {"A", 5}, {"C", 1}
    };

    VERIFY_TRUE(check_map_equal(map, answer), __LINE__);

}



void B_range_ctor() {
    /* Simple test of the range ctor taking in two iterators to another collection */
    std::vector<std::pair<std::string, int>> values {
        {"Ignore me", 100}, {"A", 3}, {"B", 2}, {"C", 1}, {"A", -5}, {"B", 3}, {"A", 5}, {"C", 1}
    };
    std::map<std::string, int> answer {values.begin()++, values.end()};
    HashMap<std::string, int> map {values.begin()++, values.end()};

    VERIFY_TRUE(check_map_equal(map, answer), __LINE__);
}






void B_move_ctor_assignment() {
    /* Checks correctness of move ctor and move assignment operator */
    HashMap<std::string, int> map1;
    HashMap<std::string, int> map2;
    HashMap<std::string, int> map_copy;

    for (const auto& kv_pair : vec) {
        map1.insert(kv_pair);
        map2.insert(kv_pair);
        map_copy.insert(kv_pair);
    }
    VERIFY_TRUE(map1 == map_copy, __LINE__);
    VERIFY_TRUE(std::move(map1) == map_copy, __LINE__);
    HashMap<std::string, int> move_constructed{std::move(map1)};
    HashMap<std::string, int> move_assigned;

    move_assigned = std::move(map2);
    VERIFY_TRUE(map_copy == move_constructed, __LINE__);
    VERIFY_TRUE(map_copy == move_assigned, __LINE__);
    map1 = move_constructed;
    VERIFY_TRUE(map1 == move_constructed, __LINE__);


    // let's start doing weird things to our map
    map1 = std::move(map1);
    (map1 = std::move(map1)) = map1 = std::move(map1 = map1 = std::move(map1));
    VERIFY_TRUE(map1 == move_constructed, __LINE__);

    // edge case with empty map
    HashMap<std::string, int> empty1;
    HashMap<std::string, int> empty2;
    empty1 = std::move(empty1);
    VERIFY_TRUE(empty1 == empty2, __LINE__);
    empty2 = std::move(map1);
    VERIFY_TRUE(empty2 == move_constructed, __LINE__);

    // verify that moved containers can still be reassigned
    map1 = std::move(move_assigned);
    empty1 = std::move(map1);
    VERIFY_TRUE(empty1 == map_copy, __LINE__);
    #pragma GCC diagnostic pop

    }

void C_move_time() {
    /* Checks the efficiency of the move operations (must be much faster than copy) */

    struct FunctorZero {
        size_t operator()(const int& v) const {
            (void) v;
            return 0;
        }
    };
    FunctorZero zero;
    HashMap<int, int, decltype(zero)> map1(2, zero);
    HashMap<int, int, decltype(zero)> map2(2, zero);
    HashMap<int, int, decltype(zero)> map_copy(2, zero);
    std::map<int, int> answer;

    for (size_t i = 0; i < 2000; ++i) {
        map1.insert({i, i*i});
        map2.insert({i, i*i});
        answer.insert({i, i*i});
    }

    // call each of the four constructors/assignment, measure their times
    ns copy_ctor, move_ctor, copy_assign, move_assign;
    {
        auto start = clock_type::now();
        HashMap<int, int, decltype(zero)> copy_constructed = map1;
        auto end = clock_type::now();
        copy_ctor = std::chrono::duration_cast<ns>(end - start);
        VERIFY_TRUE(check_map_equal(copy_constructed,answer), __LINE__);
    }

    {
        auto start = clock_type::now();
        HashMap<int, int, decltype(zero)> move_constructed = std::move(map1);
        auto end = clock_type::now();
        move_ctor = std::chrono::duration_cast<ns>(end - start);
        VERIFY_TRUE(check_map_equal(move_constructed,answer), __LINE__);
    }

    {
        auto start = clock_type::now();
        HashMap<int, int, decltype(zero)> copy_assigned;
        copy_assigned = map2;
        auto end = clock_type::now();
        copy_assign = std::chrono::duration_cast<ns>(end - start);
        VERIFY_TRUE(check_map_equal(copy_assigned,answer), __LINE__);
    }

    {
        auto start = clock_type::now();
        HashMap<int, int, decltype(zero)> move_assigned;
        move_assigned = std::move(map2);
        auto end = clock_type::now();
        move_assign = std::chrono::duration_cast<ns>(end - start);
        VERIFY_TRUE(check_map_equal(move_assigned,answer), __LINE__);
    }
    std::cout << "HashMap with 2000 elements (ns)" << std::endl;
    std::cout << "Copy ctor: " << copy_ctor.count() << setw(15) << "Move ctor: " << move_ctor.count() << std::endl;
    std::cout << "Copy assign: " << copy_assign.count() << setw(15) << "Move assign: " << move_assign.count() << std::endl;

    // verify that move operations are much faster than their copy counterparts
    // you should be able to easily beat this benchmark
    VERIFY_TRUE(100*move_ctor.count() < copy_ctor.count(), __LINE__);
    VERIFY_TRUE(100*move_assign.count() < copy_assign.count(), __LINE__);
}


int main(){
    A_initializer_list_ctor();
    A_iterator_for_each_basic();
    B_iterator_for_each_edge();
    B_range_ctor();
    C_iterator_operators();
    D_iterator_algorithm();
    E_const_iterator();
    F_iterator_const_correctness();
    B_move_ctor_assignment();
    C_move_time();
}
