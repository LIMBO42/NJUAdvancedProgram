#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H
#include <string>
class MyException {
public:
    MyException(std::string s) { eMsg = s; }
    void seteMsg(std::string s) { eMsg = s; }
    std::string what() { return eMsg; }
private:
    std::string eMsg;
};

//找不到文件异常
class FileNotFound : public MyException {
public:
    FileNotFound(std::string s) : MyException(s) {}
};

//溢出异常
class OverFlow : public MyException {
public:
    OverFlow(std::string s) : MyException(s) {}
};

//算数运算错误异常
class ArithmeticError : public MyException {
public:
    ArithmeticError(std::string s) : MyException(s) {}
};


//非法表达式异常
/*
class InvalidExpression : public MyException {
public:
    InvalidExpression(std::string s) : MyException(s) {}
};
*/

#endif