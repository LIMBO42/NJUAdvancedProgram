#include "hashmap.hpp"

template <typename K, typename M, typename H>
HashMap<K, M, H>::HashMap() : HashMap(kDefaultBuckets) { }

template <typename K, typename M, typename H>
HashMap<K, M, H>::HashMap(size_t bucket_count, const H& hash ) { }

template <typename K, typename M, typename H>
HashMap<K, M, H>::~HashMap() {}

template <typename K, typename M, typename H>
inline size_t HashMap<K, M, H>::size() const noexcept {return {};}

template <typename K, typename M, typename H>
inline bool HashMap<K, M, H>::empty() const noexcept {return {};}

template <typename K, typename M, typename H>
inline float HashMap<K, M, H>::load_factor() const noexcept {return {};};

template <typename K, typename M, typename H>
size_t HashMap<K, M, H>::bucket_count() const noexcept {return {};};

template <typename K, typename M, typename H>
bool HashMap<K, M, H>::contains(const K& key) const noexcept {return {};}

template <typename K, typename M, typename H>
void HashMap<K, M, H>::clear() noexcept {return {};}

template <typename K, typename M, typename H>
std::pair<typename HashMap<K, M, H>::value_type*, bool>
HashMap<K, M, H>::insert(const value_type& value) {return {};}


template <typename K, typename M, typename H>
bool HashMap<K, M, H>::erase(const K& key) {return {};}

template <typename K, typename M, typename H>
M& HashMap<K, M, H>::at(const K& key)const{return {};}

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
typename HashMap<K, M, H>::node_pair HashMap<K, M, H>::find_node(const K& key) const {return {};}

template <typename K, typename M, typename H>
void HashMap<K, M, H>::rehash(size_t new_bucket_count) {return {};}

template <typename K, typename M, typename H>
M& HashMap<K, M, H>::operator[](const K& key){return {};}

template <typename K, typename M, typename H>
std::ostream& operator<<(std::ostream& os, const HashMap<K, M, H>& map){return {};}

template <typename K, typename M, typename H>
bool operator==(const HashMap<K, M, H>& lhs,
                const HashMap<K, M, H>& rhs){return {};}

template <typename K, typename M, typename H>
bool operator!=(const HashMap<K, M, H>& lhs,
                const HashMap<K, M, H>& rhs){return {};}

template <typename K, typename M, typename H>
HashMap<K, M, H>::HashMap(HashMap const &other){return {};}


template<typename K, typename M, typename H>
HashMap<K,M,H> &HashMap<K, M, H>::operator=(const HashMap &other) {return {};}
