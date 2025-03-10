// C2.9.Example2Metodichka.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include <stdio.h>
#include <conio.h>
#include <stdlib.h>


typedef struct st
{
	char data[20];
	struct st *next;
} spis;
spis * create(void); //функция создания списка
void list(spis *head); // функция просмотра списка
void free_spis(spis *head); //функция освобождения памяти
int main()
{
	system("CLS");
	spis *head; // адрес головы списка
	head = create();
	list(head);
	free_spis(head);
	_getch();
}
spis * create(void)
{
	spis *p, *pred, *h;
	// pred – указатель на предыдущую структуру
	// h- указатель на первую структуру
	h = pred = new spis; //выделение памяти для первой структуры
	printf("  fam: "); scanf_s("%s", pred->data);
	do {
		p = new spis;
		printf("\n  fam: "); scanf_s("%s", p->data);
		pred->next = p; //ссылка из предыдущей на текущую
		pred = p; // сохранение адреса текущей 
		printf(" закончить? y/n  ");
	} while (_getch() == 'y');
	p->next = NULL;
	return h;
}
void list(spis *head)
{
	spis *p;
	p = head;
	while (p != NULL) // пока не конец списка
	{
		printf("\n  fio: %s", p->data);
		p = p->next; // продвижение по списку 
	}
}
void free_spis(spis *head)
{
	spis *p, *q;
	q = p = head;
	while (p != NULL)
	{
		p = q->next;
		delete q;
		q = p;
	}
	head = NULL;
}


//typedef struct st
//{
//	char ch;
//	struct st *next;
//} stack;
//int main()
//{
//	stack *p, *q;
//	char a;
//	p = NULL;
//	system("CLS");
//	//  заполнение стека 
//	do
//	{
//		a = getchar();
//		q = (stack *)malloc(sizeof(stack));
//		q->next = p;
//		p = q;
//		q->ch = a;
//	} while (a != '.');
//	//  печать стека c освобождением памяти
//	do
//	{
//		p = q->next;
//		free(q);
//		q = p;
//		printf("%c", p->ch);
//	} while (p->next != NULL);
//	_getch();
//	return 0;
//}





//typedef struct st
//{
//	char data[20];
//	struct st *next;
//} spis;//но ведь spis – это уже инициализированная область памяти… почему его используют как тип в следующих строчках?
//spis * create(void); //функция создания списка//что это за параметр такой?
//void list(spis *head); // функция просмотра списка
//void free_spis(spis *head); //функция освобождения памяти
//int main()
//{
//	system("CLS");
//	spis *head; // адрес головы списка
//	head = create();
//	list(head);
//	free_spis(head);
//	_getch();
//	return 0;
//}
//spis * create(void)
//{
//	spis *p, *pred, *h;
//	// pred – указатель на предыдущую структуру
//	// h- указатель на первую структуру
//	h = pred = new spis; //выделение памяти для первой структуры
//	printf("  fam: "); scanf_s("%s", pred->data);
//	do {
//		p = new spis;
//		printf("\n  fam: "); scanf_s("%s", p->data);
//		pred->next = p; //ссылка из предыдущей на текущую
//		pred = p; // сохранение адреса текущей 
//		printf(" закончить? y/n  ");
//	} while (_getch() == 'y');
//	p->next = NULL;
//	return h;
//}
//void list(spis *head)
//{
//	spis *p;
//	p = head;
//	while (p != NULL) // пока не конец списка
//	{
//		printf("\n  fio: %s", p->data);
//		p = p->next; // продвижение по списку 
//	}
//}
//void free_spis(spis *head)
//{
//	spis *p, *q;
//	q = p = head;
//	while (p != NULL)
//	{
//		p = q->next;
//		delete q;
//		q = p;
//	}
//	head = NULL;
//}