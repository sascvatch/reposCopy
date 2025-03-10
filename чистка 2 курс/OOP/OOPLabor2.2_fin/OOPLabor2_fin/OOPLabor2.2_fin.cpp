// OOPLabor2_fin.cpp : Defines the entry point for the console application.
//
/*Занятие 2 Использование динамических структур
данных (список, стек, очередь)

Задание 2 Написать программу, которая визуально демонстрирует работу стека и очереди.
Длина стека и очереди ограничена 10 элементами.*/

#include "stdafx.h"


#include <stdio.h>
#include <stdlib.h>

struct item {//implemented many times
	item *next;
	int data;
};

struct queue {//implemented only once
	item *head;
	item *tail;
};

struct stack {//implemented only once
	item *head;
	int count = 0;
};

void addToStack(stack &s, int data) {
	s.count++;
	item *it = new item;
	it->data = data;
	it->next = s.head;//access to the head field of stack struct// it now points at the same field, as stack's field head(the last(previous) element)
	s.head = it;//stack's field head now points at the new item
}

void addToQueue(queue &q, int data) {//tail points to the last(newest) added element
	item *it = new item;//head points to the first(oldest) added
	it->data = data;
	it->next = NULL;
	if (q.tail) {
		q.tail->next = it;//q's tail's (item's)(last) next points to the new item
		q.tail = it;//q points to the new item as "tail"
	}//eventually we can go through, starting with head only
	else {
		q.head = q.tail = it;
	}
}

void deleteFromStack(stack &s, int cnt) {
	item *tmp = s.head;
	while (cnt > 0) {
		tmp = tmp->next;
		cnt--;
	}
	tmp = tmp->next->next;
}

void deleteList(item *head) {
	while (head) {
		item *t = head->next;
		delete head;
		head = t;
	}
}

void startStackDemo() {
	stack s;
	s.head = NULL;
	int count = 0;

	while (true) {
		system("cls");
		printf("\n(HEAD)");
		for (item *p = s.head; p; p = p->next) {
			printf(" \xC4\xC4> |%3d|", p->data);
		}
		printf(" \xC4\xC4> null\n\n\n");
		if (count > 10) {
			break;
		}

		int value;
		printf("Enter any number to add or 0 to return: ");
		scanf_s("%d", &value);
		if (value == 0) {
			break;
		}
		addToStack(s, value);
		count++;
	};
	deleteList(s.head);
	system("pause");
}

void startQueueDemo() {
	queue q;
	q.head = q.tail = NULL;
	int count = 0;

	while (true) {
		system("cls");
		printf("\n(HEAD)");
		for (item *p = q.head; p; p = p->next) {
			printf(" \xC4\xC4> |%3d|", p->data);
		}
		printf(" \xC4\xC4> null\n");

		int offset = 3 + count * 10;
		if (!q.head) offset += 10;
		for (int i = 0; i < offset; i++) printf(" ");
		printf("^\n");
		for (int i = 0; i < offset; i++) printf(" ");
		printf("\xC0\xC4\xC4 (TAIL)\n\n\n");

		if (count > 10) {
			break;
		}

		int value;
		printf("Enter any number to add or 0 to return: ");
		scanf_s("%d", &value);
		if (value == 0) {
			break;
		}
		addToQueue(q, value);
		count++;
	};
	deleteList(q.head);
	system("pause");
}

int main() {
	while (true) {
		int ch;
		system("cls");
		printf("1) Stack\n2) Queue\n\nChoose option: ");
		scanf_s("%d", &ch);
		if (ch == 1) {
			startStackDemo();
		}
		else if (ch == 2) {
			startQueueDemo();
		}
	}
}
