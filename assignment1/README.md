### 1. 链表（80分）

#### 题目描述

实现链表，在List.h文件中，接口定义如下：

```c++
#ifndef LIST_H
#define LIST_H

//节点类型
typedef struct Node {
	int val;
	Node* next;
};

//链表定义
typedef struct Node* List;

//初始化
List init();

//插入节点，在链表第i个位置插入值为val的节点，成功返回true，失败返回false
bool insert(List& head, int i, int val);
//删除节点，删除链表第i个位置的元素,成功返回true，失败返回false
bool erase(List& head, int i);
//打印所有节点的数据，每个节点以空格分隔，最后一个元素接换行
void show(List& head);
//删除所有元素，注意内存泄漏
void clear(List& head);

#endif // !LIST_H

```

调用示例：

```c++
List head = init();
cout << insert(head, 0, 8) << endl;
cout << insert(head, 0, 9) << endl;
cout << insert(head, 1, 10) << endl;
cout << insert(head, 10, 1) << endl;
cout << insert(head, 3, 11) << endl;
show(head);
cout << erase(head, 0) << endl;
cout << erase(head, 10) << endl;
show(head);
clear(head);
cout << insert(head, 0, 8) << endl;
cout << erase(head, 0) << endl;
```

输出结果：

```c++
1
1
1
0
1
9 10 8 11
1
0
10 8 11
0
0
```

#### 提交要求

- 提交一个源码文件List.cpp，实现给定的接口，直接打包成zip格式的压缩包。**不要添加其他任何目录,压缩包中只包含这一个文件!**

- 文件的编码格式只支持utf-8。

- 请严格按照给定的接口进行编码,否则无法调用测试用例。

- **提交的源码文件中不需要包含main函数,否则无法通过编译。**

  

### 2.队列

#### 题目描述

基于第一问中实现的链表，实现一个FIFO(Fist In First Out)的队列。在Queue.h文件中，接口定义如下：

```c++

#ifndef QUEUE_H
#define QUEUE_H
#include "List.h"

//FIFO
typedef struct Queue {
	int size;
	List head;
	List tail;
};

//初始化
void init(Queue& q);

//入队，在队列末尾插入值为val的节点
void push(Queue& q, int val);

//出队列
bool pop(Queue& q);

//判断是否为空
bool empty(Queue& q);

//打印队列
void show(Queue& q);

//返回队首元素值，如果队列为空，返回-1
int front(Queue& q);

//返回队尾元素值，如果队列为空，返回-1
int back(Queue& q);

#endif // !QUEUE_H

```

调用示例：

```c++
Queue q;
init(q);
push(q, 1);
push(q, 2);
push(q, 3);
cout << front(q) << endl;
cout << back(q) << endl;
pop(q);
cout << front(q) << endl;
show(q);
```

输出结果：

```C++
1
3
2
2 3
```

- 提交两个个源码文件，包括List.cpp (直接沿用第一题)和Queue.cpp (实现Queue.h中声明的接口) ,直接打包成zip格式的压缩包。**不要添加其他任何目录，压缩包中只包含这两个个文件!**
- 文件的编码格式只支持utf-8。
- 请严格按照给定的接口进行编码,否则无法调用测试用例。
- **提交的源码文件中不需要包含main函数,否则无法通过编译。**