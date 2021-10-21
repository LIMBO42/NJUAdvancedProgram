// please learn to reuse your code, especially some basic functions, that's to say if you have implemented == operator, 
// you can just use == to implement != and some other cases. Please be careful about memory allocation.
// you need only need to implement the functions labled with to do.
// copy this file directy to .hpp file(remove the line : #include "hashmap.hpp") if you are using ide like visual studio, otherwise your code will not compile.
// still you don't need to worry about concurrency.
// you can directly submit this file to oj and you can pass the compile phase.


// you may copy a lot of code from copy construtor


#include "hashmap.hpp"

// In fact these functions are for you, but a lot of people are stuck here, so I implement it for you.

template <typename K, typename M, typename H>
HashMap<K, M, H>::HashMap() : HashMap(kDefaultBuckets) { }

template <typename K, typename M, typename H>
HashMap<K, M, H>::HashMap(size_t bucket_count, const H& hash) :
    _size(0),
    _hash_function(hash),
    _buckets_array(bucket_count, nullptr) {}

template <typename K, typename M, typename H>
HashMap<K, M, H>::~HashMap() {
    clear();
}

template <typename K, typename M, typename H>
inline size_t HashMap<K, M, H>::size() const noexcept {
    return _size;
}

template <typename K, typename M, typename H>
inline bool HashMap<K, M, H>::empty() const noexcept {
    return _size == 0;
}

template <typename K, typename M, typename H>
inline float HashMap<K, M, H>::load_factor() const noexcept {
    return static_cast<float>(size())/bucket_count();
};

template <typename K, typename M, typename H>
size_t HashMap<K, M, H>::bucket_count() const noexcept {
    return _buckets_array.size();
};

template <typename K, typename M, typename H>
bool HashMap<K, M, H>::contains(const K& key) const noexcept {
    return find_node(key).second != nullptr;
}

template <typename K, typename M, typename H>
M& HashMap<K, M, H>::at(const K& key)const {
    auto [prev, node_found] = find_node(key);
    if (node_found == nullptr) {
        throw std::out_of_range("HashMap<K, M, H>::at: key not found");
    }
    return node_found->value.second;
}

template <typename K, typename M, typename H>
HashMap<K, M, H>::HashMap(HashMap const& other) {
    this->_hash_function = other._hash_function;
    this->_buckets_array = std::vector<node*>(other.bucket_count(), nullptr);
    this->_size = 0;
    for (size_t i = 0; i < other.bucket_count(); ++i) {
        auto curr = other._buckets_array[i];
        while (curr != nullptr) {
            auto value = curr->value;
            auto node = std::make_pair(value.first,value.second);
            insert(node);
            curr = curr->next;
        }
    }
}


template <typename K, typename M, typename H>
void HashMap<K, M, H>::debug() const {
    std::cout << std::setw(30) << std::setfill('-') << '\n' << std::setfill(' ')
        << "Printing debug information for your HashMap implementation\n"
        << "Size: " << size() << std::setw(15) << std::right
        << "Buckets: " << bucket_count() << std::setw(20) << std::right
        << "(load factor: " << std::setprecision(2) << load_factor() << ") \n\n";

    for (size_t i = 0; i < bucket_count(); ++i) {
        std::cout << "[" << std::setw(3) << i << "]:";
        auto curr = _buckets_array[i];
        while (curr != nullptr) {
            const auto& [key, mapped] = curr->value;
            // next line will not compile if << not supported for K or M
            std::cout << " -> " << key << ":" << mapped;
            curr = curr->next;
        }
        std::cout << " /" << '\n';
    }
    std::cout << std::setw(30) << std::setfill('-') << '\n';
}

template <typename K, typename M, typename H>
M& HashMap<K, M, H>::operator[](const K& key) {
    if(!contains(key)) {
        auto res = new value_type(key, M());
        insert(*res);
    }
    return at(key);
}

template <typename K, typename M, typename H>
std::ostream& operator<<(std::ostream& os, const HashMap<K, M, H>& map){
    os<<"{";
    std::string str = "";
    for (size_t i = 0; i < map.bucket_count(); ++i) {
        auto curr = map._buckets_array[i];
        while (curr != nullptr) {
            auto node = curr;
            auto value = node->value;
            os<<str<<value.first<<":"<<value.second;
            str = ", ";
            curr = curr->next;
        }
    }
    os<<"}";
    return os;
}



template <typename K, typename M, typename H>
void HashMap<K, M, H>::clear() noexcept {
    //to do
  
}

template <typename K, typename M, typename H>
std::pair<typename HashMap<K, M, H>::value_type*, bool>
HashMap<K, M, H>::insert(const value_type& value) {
    //to do
    return { new value_type{ },true };
}


template <typename K, typename M, typename H>
bool HashMap<K, M, H>::erase(const K& key) {
    //to do
    return true;
}


template <typename K, typename M, typename H>
typename HashMap<K, M, H>::node_pair HashMap<K, M, H>::find_node(const K& key) const {
    //to do
    return { nullptr,nullptr };
}

template <typename K, typename M, typename H>
void HashMap<K, M, H>::rehash(size_t new_bucket_count) {
    //to do
}




template <typename K, typename M, typename H>
bool operator==(const HashMap<K, M, H>& lhs,
    const HashMap<K,M,H>& rhs)
{
    //to do
    return true;
}

template <typename K, typename M, typename H>
bool operator!=(const HashMap<K, M, H>& lhs,
    const HashMap<K, M, H>& rhs) {
    //to do
    return true;
}


// copy some codes above
template<typename K, typename M, typename H>
HashMap<K, M, H>& HashMap<K, M, H>::operator=(const HashMap& other) {
    //to do
    return *this;
}


