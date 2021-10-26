#include "hashmap.hpp"


template <typename K, typename M, typename H >
using value_type = std::pair<const K, M>;

template <typename K, typename M, typename H >
class HashMap<K,M,H>::iterator:public std::iterator<std::input_iterator_tag,value_type> {
    private:
        const HashMap*hashMap;
        bool is_end = true;
        int index = 0;
        node*curr_node= nullptr;
    public:
        iterator(const HashMap*mp,bool end);
        iterator(const iterator&it);
        friend bool operator==(const iterator& lhs,const iterator& rhs);
        friend bool operator!=(const iterator& lhs,const iterator& rhs);
        value_type& operator*()const;
        iterator&operator++();
        iterator operator++(int);
        iterator&operator=(iterator&other);
        iterator&operator=(const iterator&other);
        value_type*operator->() const;
        bool key_equal(const K&key);
    };


