#include "hashmap.hpp"
// command: g++ -std=c++17 test.cpp

// 0: not pass,

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


void VERIFY_TRUE(bool condition, int line) {
    if (!condition) {
        std::cout<<"0"<<std::endl; 
        // std::cout<< "not pass the test in line " << line << std::endl;
        // throw VerifyTrueAssertionFailure{line};
    }else{
        std::cout<<"1"<<std::endl;
    }
}


// ----------------------------------------------------------------------------------------------
/* Starter Code Test Cases (DO NOT EDIT) */

void A_basic() {
    /*
    * Verifies basic operations by comparing behavior with std::map
    *      - default ctor
    *      - size, empty, bucket_count
    *      - contains, at (used as an r-value)
    *
    * Mainly checking that check_map_equal compiles correctly.
    */
    std::map<std::string, int> answer;
    HashMap<std::string, int> map;
    VERIFY_TRUE(check_map_equal(map, answer), __LINE__);
    VERIFY_TRUE(map.bucket_count() == 10, __LINE__);
}
void B_insert() {
    /*
    * Verifies functionality of insert.
    */
    std::map<std::string, int> answer;
    HashMap<std::string, int> map;
    VERIFY_TRUE(check_map_equal(map, answer), __LINE__);
    VERIFY_TRUE(map.bucket_count() == 10, __LINE__);

    for (const auto& kv_pair : vec) {
        answer.insert(kv_pair);
        map.insert(kv_pair);
        VERIFY_TRUE(check_map_equal(map, answer), __LINE__);
    }

    VERIFY_TRUE(map.bucket_count() == 10, __LINE__);
}

void C_clear() {
    /*
    * Tests clear operations, and ensure map is in valid
    * state after a call to clear.
    */
    std::map<std::string, int> answer;
    HashMap<std::string, int> map;

    for (size_t j = 0; j < 3; ++j) {
       for (const auto& kv_pair : vec) {
           answer.insert(kv_pair);
           map.insert(kv_pair);
       }

       answer.clear();
       map.clear();

       VERIFY_TRUE(check_map_equal(map, answer), __LINE__);
    }
}
void D_at() {
    /*
    * Tests whether at correctly returns a reference.
    */
    std::map<std::string, int> answer;
    HashMap<std::string, int> map;
    answer.insert({"A", 42});
    answer.insert({"B", 137});
    answer.insert({"C", -1});

    // at returns a reference, so assigning their return value on the left-hand value should
    // change the contents of the map.
    answer.at("A") = 42;
    answer.at("B") = 137;
    answer.at("A") = -42;
    answer.at("C") = answer.at("A");
    VERIFY_TRUE(answer.at("A") == -42, __LINE__);
    VERIFY_TRUE(answer.at("B") == 137, __LINE__);
    VERIFY_TRUE(answer.at("C") == -42, __LINE__);

    // verify that we can save the reference returned by at.
    auto copy = answer.at("A");
    auto& ref = answer.at("B");
    copy = 0;
    ref = 0;
    VERIFY_TRUE(answer.at("A") == -42, __LINE__);
    VERIFY_TRUE(answer.at("B") == 0, __LINE__);

    // verify that correct exceptions are thrown
    HashMap<std::string, int> map2;
    bool correct_exception = false;
    try {
        map2.at("Exists") = 5;
    } catch (const std::out_of_range& e) {
        correct_exception = true;
    }
    VERIFY_TRUE(correct_exception, __LINE__);
    map2.insert({"Exists", 4});
    VERIFY_TRUE(map2.contains("Exists"), __LINE__);
    VERIFY_TRUE(!map2.contains("Does not exist"), __LINE__);
    correct_exception = true;
    try {
        map2.at("Does not exist") = 5;
    } catch (const std::out_of_range& e) {
        correct_exception = true;
    }
    VERIFY_TRUE(correct_exception, __LINE__);
}

void E_custom_bucket_count() {
    /*
    * Tests ctor taking in num_buckets, while hash function
    * still uses the default. Also tests correct function of load_factor.
    */
    HashMap<int, int> many_buckets(10000);
    HashMap<int, int> one_bucket(1);
    std::map<int, int> answer;

    for (int i = 0; i < 100; ++i) {
       many_buckets.insert({i, -i});
       one_bucket.insert({i, -i});
       answer.insert({i, -i});
    }

    VERIFY_TRUE(check_map_equal(many_buckets, answer), __LINE__);
    VERIFY_TRUE(check_map_equal(one_bucket, answer), __LINE__);

    VERIFY_TRUE(many_buckets.bucket_count() == 10000, __LINE__);
    VERIFY_TRUE(one_bucket.bucket_count() == 1, __LINE__);

    float epsilon = 0.001;
    VERIFY_TRUE(many_buckets.load_factor() - 0.01 < epsilon, __LINE__);
    VERIFY_TRUE(one_bucket.load_factor() - 100 < epsilon, __LINE__);
}
void F_custom_hash_function() {
    /*
    * Tests ctor taking in a num_buckets and hash function.
    * We use a hash function that distributes similar inputs
    * more randomly across the buckets.
    */
    using K = int;
    using V = char;
    auto identity_shifted = [](const K& key) {
       return (key * 43037 + 52081) % 79229;
    };

    // hey, didn't you use this from assignment 1?
    // now you know what the priority queue decltype comes from!
    HashMap<K, V, decltype(identity_shifted)> map(75, identity_shifted);
    std::map<K, V> answer;

    for (int i = 0; i < 50; ++i) {
       map.insert({i, 'a' + i});
       answer.insert({i, 'a' + i});
       VERIFY_TRUE(check_map_equal(map, answer), __LINE__);
    }
}

void G_erase() {
    /*
    * Tests erase operation in combination with basic operations.
    */
    std::map<std::string, int> answer;
    HashMap<std::string, int> map;

    for (const auto& kv_pair : vec) {
        answer.insert(kv_pair);
        map.insert(kv_pair);
    }

    // remove one and insert two back at a time
    for (size_t i = 0; i < vec.size(); ++i) {
        auto& [key1, mapped1] = vec[i];
        auto& pair2 = vec[(i+3) % vec.size()];
        answer.erase(key1);
        map.erase(key1);
        VERIFY_TRUE(check_map_equal(map, answer), __LINE__);

        answer.erase("Not a key");
        map.erase("Not a key");
        VERIFY_TRUE(check_map_equal(map, answer), __LINE__);

        answer.insert(pair2);
        map.insert(pair2);
    }

    // remove one at a time, until map is empty
    for (size_t i = 0; i < vec.size(); ++i) {
        auto& [key1, mapped1] = vec[(i+3) % vec.size()];
        answer.erase(key1);
        map.erase(key1);

        VERIFY_TRUE(check_map_equal(map, answer), __LINE__);
    }
}


int main(){
    A_basic();
    B_insert();
    C_clear();
    D_at();
    E_custom_bucket_count();
    F_custom_hash_function();
    G_erase();
}
