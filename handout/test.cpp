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
#include <time.h>       /* time */
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
        std::cout<<"not pass in line "<<line<<std::endl;
    }
    
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
}

void E_constuctor() {
    HashMap<int, int> map;
    for (int i = 0; i < 100; ++i) {
        map.insert({i, i*i});
    }
    srand (time(NULL));
    auto iter = map.begin();
    auto num = rand() % 20  + 10;
    while(num--) {
        iter++;
    }
    auto iter_cp(iter);
    while(iter != map.end()) {
        VERIFY_TRUE(iter == iter_cp,__LINE__);
        iter++;
        iter_cp++;
    }
}

void F_equal() {
    HashMap<int, int> map;
    for (int i = 0; i < 100; ++i) {
        map.insert({i, i*i});
    }

    auto iter1 = map.begin();
    auto iter2 = map.begin();
    while(iter2 != map.end()){
        VERIFY_TRUE(iter1 == iter2,__LINE__);
        ++iter1;
        ++iter2;
    }
    VERIFY_TRUE(iter1 == iter2,__LINE__);
}


void G_notequal() {
    HashMap<int, int> map;
    for (int i = 0; i < 100; ++i) {
        map.insert({i, i*i});
    }
    auto iter1 = map.begin();
    auto iter2 = map.begin();
    iter2++;
    while(iter2 != map.end()){
        VERIFY_TRUE(iter1 != iter2,__LINE__);
        ++iter1;
        ++iter2;
    }
    iter1++;
    VERIFY_TRUE(iter1 == iter2,__LINE__);
}

void H_star(){
    HashMap<int, int> map;
    std::map<int, int> answer;
    srand (time(NULL));
    for (int i = 0; i < 1000; ++i) {
        auto key = rand()%1000;
        map.insert({i, key});
        answer.insert({i, key});
    }
    auto iter = map.begin();
    while(iter != map.end()){
        auto value = *iter;
        VERIFY_TRUE(value.second == answer.at(value.first),__LINE__);
        iter++;
    }
}



void I_(){
    HashMap<int, int> map;
    std::map<int, int> answer;
    srand (time(NULL));
    std::vector<int> keys;
    for (int i = 0; i < 1000; ++i) {
        auto key = rand()%10000;
        while(std::find(keys.begin(),keys.end(),key)!=keys.end()){
            key = rand()%10000;
        }
        map.insert({i, key});
        answer.insert({i, key});
    }
    
    auto iter = map.begin();
    while(iter != map.end()){
        VERIFY_TRUE(iter->second == answer.at(iter->first),__LINE__);
        iter++;
    }
}
void J_(){
    HashMap<int, int> map;
    std::map<int, int> answer;
    std::vector<int> keys;
    srand (time(NULL));
    for (int i = 0; i < 1000; ++i) {
        auto key = rand()%10000;
         while(std::find(keys.begin(),keys.end(),key)!=keys.end()){
            key = rand()%10000;
        }
        map.insert({i, key});
    }
    auto iter1 = map.begin();
    auto iter2 = iter1++; 
    while(iter1 != map.end()){
        VERIFY_TRUE(iter1.key_equal(iter2->second) == false,__LINE__);
        iter2++;
        iter1++;
    }
}

void K_(){
    HashMap<int, int> map;
    std::map<int, int> answer;
    std::vector<int> keys;
    srand (time(NULL));
    for (int i = 0; i < 1000; ++i) {
        auto key = rand()%10000;
         while(std::find(keys.begin(),keys.end(),key)!=keys.end()){
            key = rand()%10000;
        }
        map.insert({i, key});
    }
    auto iter = map.begin();
    auto sz = map.size();
    while(sz--){
        VERIFY_TRUE(iter != map.end(),__LINE__);
        iter++;
    }
    VERIFY_TRUE(iter == map.end(),__LINE__);
}

int main(){
    A_iterator_for_each_basic();
    B_iterator_for_each_edge();
    C_iterator_operators();
    D_iterator_algorithm();
    E_constuctor();
    F_equal();
    G_notequal();
    H_star();
    I_();
    J_();
    K_();
}
