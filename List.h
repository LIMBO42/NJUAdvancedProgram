#pragma once
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

//i从1开始计数
//插入节点，在链表第i个位置插入值为val的节点，成功返回true，失败返回false
bool insert(List& head, int i, int val);
//删除节点，删除链表第i个位置的元素,成功返回true，失败返回false
bool erase(List& head, int i);
//打印所有节点的数据，每个节点以空格分隔，最后一个元素接换行
void show(List& head);
//删除所有元素，注意内存泄漏
void clear(List& head);

#endif // !LIST_H
