
#include <iostream>
#include <cassert>

#include "solution.inline.hpp"

void testA() {
    std::size_t sum = 0;
    for(auto i: Range(0, 10)) { sum += i; }
    assert(sum == 45);
}

void testB() {
    using namespace token_factory;
    assert(!Own(Int(123))->as_identifier_or_null());
    assert(Own(Int(123))->as_integer_or_null());
}

void testC() {
    using namespace token_factory;
    assert(Own(Id("abcd"))->as_identifier_or_null());
    assert(!Own(Int(123))->as_identifier_or_null());
    assert(Own(Id("abcd"))->as_identifier_or_null()->name() == std::string("abcd"));
}

void testD() {
    using namespace token_factory;

    assert(Own(Paren({}))->as_parenthesized_tokens_or_null());
    assert(!Own(Paren({}))->as_identifier_or_null());
    assert(Own(Paren({}))->as_parenthesized_tokens_or_null()->size() == 0);
    assert(Own(Paren({Int(123)}))->as_parenthesized_tokens_or_null()->size() == 1);
}

void testE() {
    using namespace token_factory;
    auto tokens = Own( Paren({Int(123)}) );
    auto& parened = *tokens->as_parenthesized_tokens_or_null();
    assert(parened[0]->as_integer_or_null()->integer() == 123);
}

void testF() {
    using namespace token_factory;
    std::vector<Token*> vec{ Id("alpha") };

    assert(token_to_string::to_string(vec) == "Id(alpha)");
    for(auto ptr: vec) { delete ptr; } 
}

void testG() {
    using namespace token_factory;
    std::vector<Token*> vec{
        Paren({Id("alpha"), Int(10)}),
        Paren({Id("beta"), Int(10)}),
    };

    assert(token_to_string::to_string(vec) == "Paren{ Id(alpha) Int(10) } Paren{ Id(beta) Int(10) }");
    for(auto ptr: vec) { delete ptr; } 
}

void testH() {
    using namespace token_factory;
    auto token = token_create();

    assert(token_to_string::to_string(token) == "Paren{ Int(100) Id(plus) Int(34) Id(minus) Paren{ Id(pi) Id(div) Int(4) } }");

    delete token;
}

int main() {
    testA();
    testB();
    testC();
    testD();
    testE();
    testF();
    testG();
    testH();
}