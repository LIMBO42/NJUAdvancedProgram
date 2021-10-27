
#### 题目描述

要访问顺序容器和关联容器中的元素，需要通过“迭代器（iterator）”进行。迭代器是一个变量，相当于容器和操纵容器的算法之间的中介。迭代器可以指向容器中的某个元素，通过迭代器就可以读写它指向的元素。从这一点上看，迭代器和指针类似。
​

本次上机分为两部分，第一部分是非`const`的迭代器实现，作为**本次上机的主体部分**，占90分；剩下一部分是`const`的实现，作为`bonus`，占10分。



如果你理解了实验内容的话，**这次实验的主体部分应该比较容易。**



###  Why we use iterators?——迭代器的介绍

之前的迭代器遍历：

```C++
for(std::vector<T>::iterator it = vec.begin(); it != vec.end(); ++it) {
    std::cout << *it << '\n';
}
```

C++11 中新的遍历方式：

```c++
for(const auto & elem : vec) {
    std::cout << elem << '\n';
}
```

可以减少出错的机会：不用重新输入一遍容器的类型；当容器类型发生改变时，不需要改代码。

迭代器遍历与容器无关的特性，简化了函数的实现，比如排序`sort`。

```C++
template< class RandomIt >
void sort( RandomIt first, RandomIt last );
```
`sort`可以作用于任何`random access iterators`（随机访问迭代器:

* `C arrays`

* `std::array`

* `std::vector`

* `std::deque`

* `std::string (which can be treated as a container of char)`

* 流行第三方库：`boost::ptr_vector`, `boost::ptr_deque`, etc.

* 甚至你自己的容器

所以说，本次实验希望大家了解一下迭代器的实现，增加一下对它的了解。




#### 上机内容介绍

迭代器的逻辑可以视作与下面这段代码类似，上次上机我们实现的`hashmap`：`key value`对经过`hash`，散列到`buckets`中，每个`bucket`都是一个链表。

那这次我们想要实现的迭代器，就是将`hashmap`底层的一段一段链表在遍历的时候看做是**逻辑上的一整条链表**：`begin()`获得`hashmap`中的第一个`key value`对，`iterator++`获得下一个`key value `对，直到`end()`。

![image-20211027151909730](https://typora-1306385380.cos.ap-nanjing.myqcloud.com/img/image-20211027151909730.png)

```c++
for(int i=0;i<hashMap->bucket_count();++i){
    auto curr_node = hashMap->_buckets_array[i];
    //对应于上图buckets[0]=nullptr
    while(curr_node != nullptr){
        ...
        curr_node = curr_node -> next;
    }
}

```


|接口|说明|
|-|-|
|`iterator(const HashMap*mp,bool end)`|constructor, you need to initlize private menbers in this function|
|`iterator(const iterator&it)`|constructor, useful for you implementation in `iterator operator++(int)`|
|`iterator&operator++()`|let curr_node point to the next node and return curr_node|
|`iterator operator++(int)`|return the curr_node and let curr_node point to the next node|
|`iterator&operator=(iterator&other)`|I think this does the same as constructor|
|`iterator&operator=(const iterator&other)`|above|
|`==,!=`|judge whether two iterators are the same. If they both point to the end postion or the same node,they are the same.|
|`value_type& operator*()`|return value stored in curr_node|
|`value_type*operator->()`|return address of value stored in curr_node|
|`bool key_equal(const K&_key)`|judge whether key of curr_node is _key|

#### Tips：

- 构造函数的`end`的作用：

  ![image-20211027154027943](https://typora-1306385380.cos.ap-nanjing.myqcloud.com/img/image-20211027154027943.png)

  **构造函数需要保证`cur_node`指向它应该指向的位置**，而`cur_node`保存的其实是迭代器应该指向的`node`。

  注意需要考虑如果`hashmap`所有`buckets`全空的情况，这个时候`is_end`和`cur_node`应该怎么变化？

  





#### 提交要求

- 提交源码文件：`hashmap.cpp` ,直接打包成zip格式的压缩包。**不要添加其他任何目录**
- 文件的编码格式只支持utf-8。
- 请严格按照给定的接口进行编码,否则无法调用测试用例。
- **提交的源码文件中不需要包含main函数,否则无法通过编译。**



