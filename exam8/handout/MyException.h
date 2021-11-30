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

/*
test1 input
(2147483646-1i)+(-2+1i)
(0-2i)+(2147483647+2i)
(-2147483647-1073741824i)+(-2-1i)
(-2147483648+0i)/(0+0i)
(-2147483648-2i)*(2147483647-1i)
(-2147483648+1i)+(0+1073741823i)
(2147483646-1i)*(-1+1073741823i)
(2147483646+2i)*(1073741823-2147483647i)
(0+1i)+(2+1i)
(0-1i)*(-2+0i)
(-2147483648+2147483647i)*(2-2i)
(-2147483648-2i)+(3+2i)


test2 input
(2147483646+3i)+(-2147483648+2i)
(-2147483647+2147483647i)-(1073741823+3i)
(2147483646+0i)+(2147483647+3i)
(-1-2147483648i)/(1+2i)
(2147483646+2147483646i)-(3+0i)
(-2147483647+0i)*(-2147483648-2147483647i)
(-2147483647+0i)+(2+2147483646i)
(2147483647+2147483646i)+(0-2i)
(-2147483647-2i)/(0+2147483646i)
(-2147483648-2i)/(2+3i)
(2147483646+3i)+(2147483646+1073741823i)
(2147483646+3i)-(-1+0i)
*/
#endif