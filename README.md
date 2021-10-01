### 第三次上机

#### 题目描述

​	如果您对TCP有所了解的话，您可能会知道可靠的字节流在网络通信上的起到的作用，但是如果您不了解也没关系。本次上机将会实现一个简易的ByteStream：(您可以默认输入的是char类型)

​	为了更好的模拟真实世界的情况，我们假定开辟了一块容量为capacity的内存空间，您可以认为输入流，输出流是无限的，直到输入流到达EOF(EOF表示输入流的末尾)。

​	但是由于内存空间的限制，如果输入流占满了空间，就会被阻塞，相对应的如果内存空间为空，输出流就会被阻塞。如下图所示，ByteStream一端读，一端写，writer从输入流写入数据，reader从输出流读出数据：

​	![image-20211001200249862](https://typora-1306385380.cos.ap-nanjing.myqcloud.com/img/image-20211001200249862.png)

```c++

#ifndef BYTE_STREAM_H
#define BYTE_STREAM_H
#include <string>
#include <deque>
using namespace std;

class ByteStream {
private:
    
    //一端读 一端写，先进先出
    //您可能需要自己添加一些私有变量来实现上述的效果。
    //容器：
    //这里我们推荐您使用deque双端队列作为容器，尽管可能ByteStream行为上
    //更类似于queue队列(他们都是先进先出)，但是可惜的是为了实现可靠性(读出一些数据却不会丢失数据，也就是peek_output接口)，
    //我们需要能够对容器进行迭代(queue并不具有迭代器)。
    //如果您不了解deque的用法，您也可以使用char数组和两个指针来表示队列的头和尾

    //一些必要的变量：用来表示内存容量，已经写入的字节数，已经读出的字节数，输入流是否结束，输出流是否结束
    //size_t用来表示无符号整型，您的整型变量的类型均可设为size_t
    bool _error{};  //表明stream是否出现了error的flag，不用在意
    

    //需要您格外注意：输入流和输出流结束的判断，输入流结束的时候会调用end_input()通知，
    //在输入流结束且容器中全部都读出之后，输出流结束
public:
    //构造函数
    ByteStream(const size_t capacity);
    
    //将string类型的data写入stream中，返回写入的字节数
    size_t write(const std::string& data);

    //返回remaining_capicity
    size_t remaining_capacity() const;

    //输入流发出信号 表明到达输入流结尾
    void end_input();

    //! stream出错 不用实现
    void set_error() { _error = true; }

    //获取stream输出流的一部分
    std::string peek_output(const size_t len) const;

    //对输出流pop
    void pop_output(const size_t len);

    //read len的数据
    std::string read(const size_t len);

    //返回bool变量
    bool input_ended() const;

    //stream出错 不用实现
    bool error() const { return _error; }

    //返回当前容器的size
    size_t buffer_size() const;

    //如果容器为空返回true
    bool buffer_empty() const;

    //如果输入流到达EOF，返回true
    bool eof() const;

    //返回总共写入的字节数
    size_t bytes_written() const;

    //返回总共读出的字节数
    size_t bytes_read() const;

};

#endif  // SPONGE_LIBSPONGE_BYTE_STREAM_H
```

#### 调用示例

```c++
#include <iostream>
#include "byte_stream.hh"
#include <assert.h>     /* assert */

using namespace std;

// command: g++ test.cc byte_stream.cc

// test for 
void test_capacity(){
    ByteStream stream(2);
    assert(2 == stream.write("cat"));
    assert(false == stream.eof());
    assert(0 == stream.bytes_read());
    assert(2 == stream.bytes_written());
    assert(0 == stream.remaining_capacity());
    assert(2 == stream.buffer_size());
    assert("ca" == stream.peek_output(2));
    assert(0 == stream.write("t"));
    assert(false == stream.input_ended());
    assert(false == stream.buffer_empty());
    assert(false == stream.eof());
    assert(0 == stream.bytes_read());
    assert(2 == stream.bytes_written());
    assert(0 == stream.remaining_capacity());
    assert(2 == stream.buffer_size());
    assert("ca" == stream.peek_output(2));
}


void test_write_once(){
    ByteStream stream(15);
    stream.write("cat");
    assert(false == stream.input_ended());
    assert(false == stream.buffer_empty());
    assert(false == stream.eof());
    assert(0 == stream.bytes_read());
    assert(3 == stream.bytes_written());
    assert(12 == stream.remaining_capacity());
    assert(3 == stream.buffer_size());
    assert("cat" == stream.peek_output(3));
    
    stream.end_input();
    assert(true == stream.input_ended());
    assert(false == stream.eof());
    assert(0 == stream.bytes_read());
    assert(3 == stream.bytes_written());
    assert(12 == stream.remaining_capacity());
    assert(3 == stream.buffer_size());
    assert("cat" == stream.peek_output(3));

    stream.pop_output(3);

    assert(true == stream.input_ended());
    assert(true == stream.buffer_empty());
    assert(true == stream.eof());
    assert(3 == stream.bytes_read());
    assert(3 == stream.bytes_written());
    assert(15 == stream.remaining_capacity());
    assert(0 == stream.buffer_size());

}

void test_write_twice(){
    ByteStream stream(15);


    stream.write("cat");
    assert(false == stream.input_ended());
    assert(false == stream.buffer_empty());
    assert(false == stream.eof());
    assert(0 == stream.bytes_read());
    assert(3 == stream.bytes_written());
    assert(12 == stream.remaining_capacity());
    assert(3 == stream.buffer_size());
    assert("cat" == stream.peek_output(3));
    
    stream.write("tac");
    assert(false == stream.input_ended());
    assert(false == stream.buffer_empty());
    assert(false == stream.eof());
    assert(0 == stream.bytes_read());
    assert(6 == stream.bytes_written());
    assert(9 == stream.remaining_capacity());
    assert(6 == stream.buffer_size());
    assert("cattac" == stream.peek_output(6));
    
    stream.end_input();
    assert(true == stream.input_ended());
    assert(false == stream.buffer_empty());
    assert(false == stream.eof());
    assert(0 == stream.bytes_read());
    assert(6 == stream.bytes_written());
    assert(9 == stream.remaining_capacity());
    assert(6 == stream.buffer_size());
    assert("cattac" == stream.peek_output(6));    

    stream.pop_output(2);
    assert(true == stream.input_ended());
    assert(false == stream.buffer_empty());
    assert(false == stream.eof());
    assert(2 == stream.bytes_read());
    assert(6 == stream.bytes_written());
    assert(11 == stream.remaining_capacity());
    assert(4 == stream.buffer_size());
    assert("ttac" == stream.peek_output(6));    

    stream.pop_output(4);
    assert(true == stream.input_ended());
    assert(true == stream.buffer_empty());
    assert(true == stream.eof());
    assert(6 == stream.bytes_read());
    assert(6 == stream.bytes_written());
    assert(15 == stream.remaining_capacity());
    assert(0 == stream.buffer_size()); 
}

int main(int argc,char*argv[]){
    test_capacity();
    test_write_once();
    test_write_twice();
}
```

#### 提交要求

- 只需提交一个源码文件：byte_stream.cpp (实现byte_stream.h中声明的接口) ,直接打包成zip格式的压缩包。**不要添加其他任何目录，压缩包中只包含这两个个文件!**
- 文件的编码格式只支持utf-8。
- 请严格按照给定的接口进行编码,否则无法调用测试用例。
- **提交的源码文件中不需要包含main函数,否则无法通过编译。**

#### 附录

![image-20211001200912477](https://typora-1306385380.cos.ap-nanjing.myqcloud.com/img/image-20211001200912477.png)

迭代器的使用：

```C++
for (auto it = vec_.begin(); it != vec_.end(); it++) {
	//这里用*it来获得对应位置的元素
}
```

