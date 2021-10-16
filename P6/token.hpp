#pragma once


#include <string>
#include <vector>
#include "listlike.hpp"
#include <memory>

/*
 * This file describe a token datastructure which may be used in some programming language. 
 * 
 * Token: simple unit like a word in one sentince, like: abc, 123, "alpha".
 *      Identifier: non-numeric word.
 *      Integer: a integer number like 123.
 *      ParenthesizedTokens: a sequence of token inside a Parenthesis '( 123 plus 456 minus 123 )'
 * 
 * Note: Rust compiler has a similar structure like this.
 */ 
class Token;
    class Integer;
    class Identifier;
    class ParenthesizedTokens;

class Token {
protected:
    Token(){}
public:
    virtual Integer* as_integer_or_null();
    virtual Identifier* as_identifier_or_null();
    virtual ParenthesizedTokens* as_parenthesized_tokens_or_null();

    template<typename T>
    T* Token::rtti_cast() { return dynamic_cast<T*>(this); }
    const char* Token::rtti_name() { return typeid(*this).name(); }

    virtual ~Token() {}
};

class Integer: public Token {
    int _integer;
public:
    Integer(int i) noexcept: _integer(i) {}

    virtual Integer* as_integer_or_null();
    int integer() const noexcept { return _integer; }
};

class Identifier: std::string, public Token {
public:
    explicit Identifier(const std::string& name) noexcept: std::string(name) {}
    explicit Identifier(std::string&& name) noexcept: std::string(name) {}

    virtual Identifier* as_identifier_or_null();
    const char * name() const noexcept;
};

class ParenthesizedTokens: public Token, public ListLike<Token *> {
    std::vector<Token *> vec;
public:
    explicit ParenthesizedTokens(std::initializer_list<Token *> list) noexcept;
    std::size_t size() const noexcept override;
    Token* operator[](std::size_t index) const noexcept override;

    virtual ParenthesizedTokens* as_parenthesized_tokens_or_null();

    ~ParenthesizedTokens();
};

namespace token_factory {
    template<typename... Args>
    inline Token * Id(Args... args) noexcept {
        return dynamic_cast<Token *>(new Identifier(args...));
    }
    template<typename... Args>
    inline Token * Int(Args... args) noexcept {
        return dynamic_cast<Token *>(new Integer(args...));
    }
    inline Token * Paren(std::initializer_list<Token *> list) noexcept {
        return dynamic_cast<Token *>(new ParenthesizedTokens(list));
    }
    inline std::unique_ptr<Token> Own(Token * tok) noexcept {
        return std::unique_ptr<Token>(tok);
    }
}