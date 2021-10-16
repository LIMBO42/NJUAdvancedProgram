

/*
 * ListLike: an example of pure virtual functions.
 * This resembles all indexable data structure with limited size.
 */
template<class T>
class ListLike {
protected:
    ListLike() {}
public:
    /*
     * Pure virtual functions which you need to implement by yourself.
     */
    virtual std::size_t size() const noexcept = 0;
    virtual T operator[](std::size_t index) const noexcept = 0;

    /*
     * Utility functions that dose NOT need to implement. (But you can implement your optimized version)
     */
    virtual T front() const noexcept { return operator[](0); }
    virtual T back() const noexcept { return operator[](size() - 1); }

    /*
     * A Simple Iterator for ListLike Structure
     * Now, you can use `for(auto elem: {ListLike Instance} )` syntax.
     */
    class ListLikeIter {
        ListLike& _listlike;
        std::size_t _index;
    public:
        ListLikeIter(ListLike& listlike, std::size_t index) : _listlike(listlike), _index(index) {}

        ListLikeIter& operator++() { _index++; return *this;}
        ListLikeIter operator++(int) {auto retval = *this; _index++; return retval;}
        bool operator==(const ListLikeIter& other) const {return _index == other._index;}
        bool operator!=(const ListLikeIter& other) const {return !(*this == other);}
        T operator*() const {return _listlike[_index];}
    };

    using iterator = ListLikeIter;

    iterator begin() { return ListLikeIter(*this, 0); }
    iterator end() { return ListLikeIter(*this, size()); }

    /*
     * Do you know why using virtual destructor is a good practice?
     */
    virtual ~ListLike() {}
};

