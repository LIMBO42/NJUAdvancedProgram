#ifndef MATHUTILS_H
#define MATHUTILS_H
#include "Complex.h"
class MathUtils {
public:
    // 接受一个表达式字符串并返回计算结果。例如:calculator("(1+2i)+(2+3i)")的结果为3+5i
    static Complex calculator(string s);
    // 使用函数calculator处理文本文件，输入文件名为 inputFileName, 输出文件名为 outputFileName。
    // 每一行为一个表达式，为了简单起见，我们假定这里的表达式不会触发任何异常
    //static void processTextFile(string inputFilename, string outputFilename);
};

#endif