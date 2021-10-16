#pragma once
#include "print_token.hpp"
#include <cassert>

/*************************************************
 *                    TASK 1                     *
 *************************************************/

/*
 * This `Range` class represent the interval [_begin, _end).
 * Complete this `Range` class. Implement all method needed by `ListLike<std::size_t>`.
 */
class Range: public ListLike<std::size_t> {
public:
    std::size_t _begin, _end;
    Range(std::size_t begin, std::size_t end) : _begin(begin), _end(end) {}

    // TODO: Implement all method needed by ListLike<std::size_t>. 
    // Following test function can help you check your correctness.
    std::size_t size() const noexcept override { return _end - _begin; }
    std::size_t operator[](std::size_t index) const noexcept override { return _begin + index; }

    static void check() {
        std::size_t sum = 0;
        for(auto i: Range(0, 10)) {
            sum += i;
        }
        assert(sum == 45);
    }
};

/*************************************************
 *                    TASK 2                     *
 *************************************************/


// Token
Integer* Token::as_integer_or_null() { return nullptr; }
Identifier* Token::as_identifier_or_null() { return nullptr; }
ParenthesizedTokens* Token::as_parenthesized_tokens_or_null() { return nullptr; }

// Integer
Integer* Integer::as_integer_or_null() { return this; }

// Identifier
Identifier* Identifier::as_identifier_or_null() { return this; }
const char * Identifier::name() const noexcept { return c_str(); }

// ParenthesizedTokens
ParenthesizedTokens::ParenthesizedTokens(std::initializer_list<Token *> list) noexcept {
    for(auto&& ptr : list) { vec.push_back(std::move(ptr)); }
}
std::size_t ParenthesizedTokens::size() const noexcept { return vec.size(); }
Token* ParenthesizedTokens::operator[](std::size_t index) const noexcept { return vec[index]; }
ParenthesizedTokens* ParenthesizedTokens::as_parenthesized_tokens_or_null() { return this; }
ParenthesizedTokens::~ParenthesizedTokens() { for(auto ptr: vec) { delete ptr;} }

/*************************************************
 *                    TASK 3                     *
 *************************************************/

/*
 * Please use these 3 function: token_to_string::identifier, token_to_string::integer, and token_to_string::parenthesized_tokens
 * to convert a Token * pointer to string.
 */ 
std::string token_to_string::to_string(Token * ptr) {
    // TODO: convert a Token to string.
    if(auto id = ptr->as_identifier_or_null()) {
        return identifier(id->name());
    } else if(auto i = ptr->as_integer_or_null()) {
        return integer(i->integer());
    } else if(auto paren = ptr->as_parenthesized_tokens_or_null()) {
        std::vector<std::string> vec;
        for(auto ptr: *paren) {
            vec.push_back(to_string(ptr));
        }
        return parenthesized_tokens(vec);
    } else {
        throw std::runtime_error("Unknown Token.");
    }
}

/*************************************************
 *                    TASK 4                     *
 *************************************************/

/*
 * Let's write a function to create the following token.
 *   ( 100 plus 34 minus ( pi div 4 ) )
 */
Token* token_create() {
    using namespace token_factory;
    return Paren({ Int(100), Id("plus"), Int(34), Id("minus"), Paren({ Id("pi"), Id("div"), Int(4) }) });
}