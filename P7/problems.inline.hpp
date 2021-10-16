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
    // TODO
}


template<class T>
inline const T* optional<T>::get() const {
    // TODO
}

/*
 * TASK 2: exception_iter
 * 
 * Implement class `StopIteration`, `Range::next() and `sum(ExceptIter<std::size_t>)`
 */

class StopIteration: public std::exception {
    // TODO
};

std::size_t Range::next() {
    // TODO
}

std::size_t sum(ExceptIter<std::size_t>& it) {
    // TODO
}

/*
 * TASK 3: argparse
 * 
 * add code to throw exceptions in the following function.
 */

template<>
int argparser::parse_from<int>(const std::string& str) throw(ParsingError) {
    // TODO: add exception here
    return std::stoi(str);
}

template<typename T>
void argparser::Argument<T>::parse(const std::string& input) throw(ArgumentError) {
    // TODO: add exception here
    _result = parse_from<T>(input);
}

template<typename T>
T argparser::Argument<T>::get() throw(ArgumentError)  {
    // TODO: add exception here
    if(!_result && _default) {
        return *_default;
    }
    return *_result;
}

void argparser::ArgParser::parse(int argc, const char ** argv) throw(ArgumentError, UnrecongizedInput) {
    // TODO: add exception here
    for(int i = 1; i < argc; i++) {
        for(auto arg: _args) {
            // when using short tag, the space between tag and additional argument can be ignored.
            // for example: `gcc -I <directory>` and `gcc -I<directory>` are both acceptable.
            if( arg->is_short_tag(argv[i]) && argv[i][2] != 0) {
                arg->parse(std::string(argv[i] + 2));
                break;
            } else if( arg->is_short_tag(argv[i]) || arg->is_tag(argv[i]) ) {
                if(!arg->need_argument()) {
                    // when additional argument is not needed.
                    arg->parse(std::string(""));
                    break;
                } else if(i + 1 < argc && argv[i + 1][0] != '-') {
                    // when additional argument is found.
                    i++;
                    arg->parse(std::string(argv[i]));
                    break;
                }
            }
        }
    }
}

template<typename T>
T argparser::ArgParser::get(const std::string& name) throw(ArgumentNotFound, ArgumentWrongType, ArgumentError) {
    // TODO: add exception here
    // Note: ArgumentError is throwed in get().
    for(auto arg: _args) {
        if(arg->name() == name) {
            if(auto arg_T = dynamic_cast<Argument<T> *>(arg)) {
                return arg_T->get();
            }
        }
    }
}