#pragma once
#ifndef LIST_H
#define LIST_H

//�ڵ�����
typedef struct Node {
	int val;
	Node* next;
};

//������
typedef struct Node* List;

//��ʼ��
List init();


//����ڵ㣬�������i��λ�ò���ֵΪval�Ľڵ㣬�ɹ�����true��ʧ�ܷ���false
bool insert(List& head, int i, int val);
//ɾ���ڵ㣬ɾ�������i��λ�õ�Ԫ��,�ɹ�����true��ʧ�ܷ���false
bool erase(List& head, int i);
//��ӡ���нڵ�����ݣ�ÿ���ڵ��Կո�ָ������һ��Ԫ�ؽӻ���
void show(List& head);
//ɾ������Ԫ�أ�ע���ڴ�й©
void clear(List& head);

#endif // !LIST_H
