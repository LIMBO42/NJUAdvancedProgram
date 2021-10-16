#pragma once

#include <stdexcept>

/*
 * A Python style Iterator
 * 
 * You have learned how to write c++ iterators. However, different languages have different styles of iterator.
 * In python, you use `next(iter)` to get the next value in a iterator, and you will get a `StopIteration`
 * exception at end of a iterator. Let's try it in c++.
 * 
 * Note: 1. More info about python iterator: https://www.w3schools.com/python/python_iterators.asp
 *       2. This is in deed a bad practive in c++, if you care about exception safety. 
 */

// Exception class 
class StopIteration;

// Abstract Itertor class.
template<typename T>
class ExceptIter {
protected:
    ExceptIter() {}
public:
    virtual T next() = 0; // throw StopIteration in the end
    virtual ~ExceptIter() {}
};

// A Range class represent [begin, end)
class Range: public ExceptIter<std::size_t> {
public:
    std::size_t _begin;
    std::size_t _end;
    Range(std::size_t begin, std::size_t end): _begin(begin), _end(end) {}

    // _begin++ and throw StopIteration at _end
    std::size_t next() override;
};

// Get sum of an ExceptIter
std::size_t sum(ExceptIter<std::size_t>& it);
