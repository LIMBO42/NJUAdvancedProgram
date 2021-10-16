#pragma once

#include <stdexcept>

/* 
 * An exception class for optional<T>.
 */
class bad_optional_access : public std::exception {
public:
    virtual const char* what() const noexcept override {
        return "Bad Optional Access";
    }
};

/* 
 * optional<T>: A value that can be null.
 * 
 * This class is used to denote that this value can be null.
 * 
 * Note: This class resembles c++17 `std::optional`. Many static languages have this class (Java, Scala, C#, Rust ...)
 */
template<class T>
class optional {
    T* _data;
    void free() noexcept { if(_data) delete _data; }
public:
    optional() { _data = nullptr; }

    optional(std::nullptr_t null_ptr) noexcept { _data = nullptr; }
    optional(const T& data) noexcept { _data = new T(data); }
    optional(T&& data) noexcept { _data = new T(std::move(data)); }
    optional(const optional<T>& opt) noexcept { if(opt._data) { _data = new T(*opt._data); } else { _data = nullptr; } }
    optional(optional<T>&& opt) noexcept { _data = opt._data; opt._data = nullptr; }

    optional<T>& operator=(std::nullptr_t null_ptr) noexcept { free(); _data = null_ptr; return *this;}
    optional<T>& operator=(const T& data) noexcept { free(); _data = new T(data); return *this;}
    optional<T>& operator=(const T&& data) noexcept { free(); _data = new T(std::move(data)); return *this;}
    optional<T>& operator=(const optional<T>& opt) noexcept { free(); if(opt._data) { _data = new T(*opt._data); } else { _data = nullptr; } return *this;}
    optional<T>& operator=(optional<T>&& opt) noexcept { free(); _data = opt._data; opt._data = nullptr; return *this;}

    ~optional() { free(); }

    inline T* get();
    inline const T* get() const;

    T& operator*() { return *get(); }
    const T& operator*() const { return *get(); }

    T* operator->()  { return get(); }
    const T* operator->() const { return get(); }

    operator bool() const noexcept { return _data; }

    T* data() { return _data; }
};