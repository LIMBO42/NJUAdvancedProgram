#pragma once

#include "optional.hpp"
#include "exception_iter.hpp"
#include "argparser.hpp"

/*
 * TASK 1: optional
 * 
 * Throw `bad_optional_access` exception in implementation of optional.
 */

template<class T>
inline T* optional<T>::get()  {
    if(_data) return _data;
    else throw bad_optional_access();
}


template<class T>
inline const T* optional<T>::get() const {
    if(_data) return _data;
    else throw bad_optional_access();
}

/*
 * TASK 2: exception_iter
 * 
 * Implement class `StopIteration`, `Range::next() and `sum(ExceptIter<std::size_t>)`
 */

class StopIteration: public std::exception {
public:
    virtual const char* what() const noexcept override {
        return "Stop Iteration Exception";
    }
};

std::size_t Range::next() {
    if(_begin < _end) { return _begin++; }
    else { throw StopIteration(); }
}

std::size_t sum(ExceptIter<std::size_t>& it) {
    std::size_t sum = 0;
    try {
        while(true) {
            sum += it.next();
        }
    } catch(StopIteration e) {}
    return sum;
}

/*
 * TASK 3: argparse
 * 
 * add code to throw exceptions in the following function.
 */

template<>
int argparser::parse_from<int>(const std::string& str) throw(ParsingError) {
    try{
        return std::stoi(str);
    } catch (const std::exception& e ) {
        throw ParsingError(str, e.what());
    }
}

template<typename T>
void argparser::Argument<T>::parse(const std::string& input) throw(ArgumentError) {
    try {
        _result = parse_from<T>(input);
    } catch (std::runtime_error& e) {
        throw ArgumentError(_name, e);
    }
}

template<typename T>
T argparser::Argument<T>::get() throw(ArgumentError)  {
    if(!_result) {
        if(_default) { return *_default; }
        throw ArgumentError(_name, MissingArgument()); 
    }
    return *_result;
}

void argparser::ArgParser::parse(int argc, const char ** argv) throw(ArgumentError, UnrecongizedInput) {
    for(int i = 1; i < argc; i++) {
        bool is_recongized = false;
        for(auto arg: _args) {
            // when using short tag, the space between tag and additional argument can be ignored.
            // for example: `gcc -I <directory>` and `gcc -I<directory>` are both acceptable.
            if( arg->is_short_tag(argv[i]) && argv[i][2] != 0) {
                arg->parse(std::string(argv[i] + 2));

                is_recongized = true; break;
            } else if( arg->is_short_tag(argv[i]) || arg->is_tag(argv[i]) ) {
                if(!arg->need_argument()) {
                    // when additional argument is not needed.
                    arg->parse(std::string(""));

                    is_recongized = true; break;
                } else if(i + 1 < argc && argv[i + 1][0] != '-') {
                    // when additional argument is found.
                    i++;
                    arg->parse(std::string(argv[i]));

                    is_recongized = true; break;
                } else {
                    throw ArgumentError(arg->name(), MissingArgument());
                }
            }
        }
        if(!is_recongized) {
            throw UnrecongizedInput();
        }
    }
}

template<typename T>
T argparser::ArgParser::get(const std::string& name) throw(ArgumentNotFound, ArgumentWrongType, ArgumentError) {
    for(auto arg: _args) {
        if(arg->name() == name) {
            if(auto arg_T = dynamic_cast<Argument<T> *>(arg)) {
                return arg_T->get();
            } else {
                throw ArgumentWrongType();
            }
        }
    }
    throw ArgumentNotFound();
}