#include "List.h"
#include <iostream>

List init()
{
	List head = new Node;
	head->next = nullptr;
	return head;
}

bool insert(List& head, int i, int val)
{
	if (head == nullptr) return false;
	int count = 0;
	
	//newһ���ڵ�
	List tmpNode = new Node;
	tmpNode->val = val;
	tmpNode->next = nullptr;

	List pre = head;
	for (List cur = head -> next; cur != nullptr; cur = cur->next, pre = pre->next) {
		if (count == i) {
			tmpNode->next = pre->next;
			pre->next = tmpNode;
			return true;
		}
		count++;
	}
	//����count==i �����뵽ĩβ�����
	//�Լ�����������һ��Ԫ�ص����
	if (count == i) {
		tmpNode->next = pre->next;
		pre->next = tmpNode;
		return true;
	}
	return false;
}

bool erase(List& head, int i)
{
	if (head == nullptr)return false;
	int count = 0;
	List pre = head;
	for (List cur = head->next; cur != nullptr; cur = cur->next, pre = pre->next) {
		if (count == i) {
			pre->next = cur->next;
			delete cur;
			return true;
		}
		count++;
	}
	//����count==i ��ɾ��ĩβ�����
	
	if (count == i) {
		pre->next = nullptr;
		return true;
	}
	return false;
}

void show(List& head)
{
	for (List p = head->next; p != nullptr; p = p->next) {
		std::cout << p->val << " ";
	}
	std::cout << std::endl;
}

void clear(List& head)
{
	List pre = head;
	for (List p = head->next; p != nullptr; ) {
		pre->next = p->next;
		delete p;
		p = pre->next;
	}
	head = nullptr;
}
