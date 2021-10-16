#pragma once

#include "token.hpp"
#include <stdexcept>

namespace token_to_string {

    std::string identifier(const char* name) noexcept {
        return "Id(" + std::string(name) + ")";
    }

    std::string integer(int integer) noexcept {
        return "Int(" + std::to_string(integer) + ")";
    }

    std::string parenthesized_tokens(const std::vector<std::string>& vec) noexcept {
        std::string ret = "Paren{ ";
        bool first = true;
        for(auto& str: vec) {
            ret += str + " ";
        }
        ret += "}";
        return ret;
    }

    std::string to_string(Token * ptr);
    
    std::string to_string(const std::vector<Token *>& ptrs ) {
        std::string ret;
        bool first = true;
        for(auto& ptr: ptrs) {
            if(first) { first = false; }
            else { ret += " ";}
            ret += to_string(ptr);
        }
        return ret;
    }
}