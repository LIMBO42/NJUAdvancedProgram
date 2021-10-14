#include "hashmap.hpp"





template <typename K, typename M, typename H>
HashMap<K, M, H>::~HashMap() {

}

template <typename K, typename M, typename H>
inline size_t HashMap<K, M, H>::size() const noexcept {

}

template <typename K, typename M, typename H>
inline bool HashMap<K, M, H>::empty() const noexcept {

}

template <typename K, typename M, typename H>
inline float HashMap<K, M, H>::load_factor() const noexcept {

};

template <typename K, typename M, typename H>
size_t HashMap<K, M, H>::bucket_count() const noexcept {

};

template <typename K, typename M, typename H>
bool HashMap<K, M, H>::contains(const K& key) const noexcept {
    
}

template <typename K, typename M, typename H>
void HashMap<K, M, H>::clear() noexcept {
    
}

template <typename K, typename M, typename H>
std::pair<typename HashMap<K, M, H>::value_type*, bool>
HashMap<K, M, H>::insert(const value_type& value) {
    
}


template <typename K, typename M, typename H>
bool HashMap<K, M, H>::erase(const K& key) {
    
}

template <typename K, typename M, typename H>
M& HashMap<K, M, H>::at(const K& key)const{
    
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
            std::cout <<  " -> " << key << ":" << mapped;
            curr = curr->next;
        }
        std::cout <<  " /" <<  '\n';
    }
    std::cout << std::setw(30) << std::setfill('-') << '\n';
}



template <typename K, typename M, typename H>
typename HashMap<K, M, H>::node_pair HashMap<K, M, H>::find_node(const K& key) const {
    
}




template <typename K, typename M, typename H>
void HashMap<K, M, H>::rehash(size_t new_bucket_count) {
    
}


template <typename K, typename M, typename H>
M& HashMap<K, M, H>::operator[](const K& key){
    
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
bool operator==(const HashMap<K, M, H>& lhs,
                const HashMap<K, M, H>& rhs){
    
}

template <typename K, typename M, typename H>
bool operator!=(const HashMap<K, M, H>& lhs,
                const HashMap<K, M, H>& rhs){
    
}

template <typename K, typename M, typename H>
HashMap<K, M, H>::HashMap(HashMap const &other){
    
}

template <typename K, typename M, typename H>
HashMap<K, M, H>::HashMap(HashMap &&other){
   
}


template<typename K, typename M, typename H>
HashMap<K,M,H> &HashMap<K, M, H>::operator=(const HashMap &other) {
   
}

template<typename K, typename M, typename H>
HashMap<K,M,H> &HashMap<K, M, H>::operator=(HashMap &&other) {
    
}

template<typename K, typename M, typename H>
HashMap<K, M, H>::HashMap(std::initializer_list<std::pair<K, M>>list) {
    
}
