#include "stdafx.h"
#include <cstring>
#include <iostream>//  for cout(for C++ only)
#include<conio.h>// for _getch()
using namespace std;// for cout(for C++ only)
					/*
					Здесь будет реализован стек... Хотя просто двусвязный список...
					Способ доступа ведь можно поменять для уже существующего списка.

					Сформировать двусвязный список, состоящий из структур, содержащих информацию: 
					фамилия студента и 4 оценки. Найти и удалить из списка студентов, имеющих хотя бы 
					одну неудовлетворительную оценку. Вывести список до и после удаления записей.*/
typedef struct Node {
	Node *next, *prev;
	char name[20];
	int m1, m2, m3, m4;

};
typedef Node *PNode;

//По аналогии со стопкой тарелок начало списка называют основанием стека, а его конец — вершиной.

void del(PNode &prohod, PNode &Head, int n, int &nAfter) {
	for (int i = 0; i < n; i++)
	{
		if (prohod->prev->m1 < 3 || prohod->prev->m2 < 3 ||
			prohod->prev->m3 < 3 || prohod->prev->m4 < 3)
		{
			prohod->prev = prohod->prev->prev;
			nAfter--;
			i++;
		}
		prohod = prohod->prev;
	}
}
/*Функция составляет список, записывая начальный элемент после заранее
проинициализированного Tail. Конечный элемент всегда ссылается(своим next) на
заранее проинициализированный Head;
Tail->prev - всегда NULL. Head->next всегда NULL.*/
PNode CreateNode(PNode &Head, PNode &NewNode, PNode &root, PNode &tail, PNode &temp) {
	NewNode = new Node;
	if (tail->next = NULL)tail->next = NewNode;
	NewNode->prev = temp;//в первую инициализацию темп хранит в себе ссылку на теил
	NewNode->next = Head;
	Head->prev = NewNode;

	cout << "Введите фамилию студента ";
	cin >> NewNode->name;
	cout << "Введите 4 его оценки ";
	cin >> NewNode->m1 >> NewNode->m2 >> NewNode->m3 >> NewNode->m4;
	cout << endl;

	temp = NewNode;
	return NewNode;
}

void print(PNode &prohod, int n) {
	for (int i = 0; i < n; i++) {//Вывод на экран
		cout << prohod->prev->name
			<< endl
			<< prohod->prev->m1 << " "
			<< prohod->prev->m2 << " "
			<< prohod->prev->m3 << " "
			<< prohod->prev->m4
			<< endl << endl;

		prohod = prohod->prev;
	}
	cout << endl;
}

int main()
{
	PNode Head = NULL, prohod = NULL, NewNode = NULL, tail = NULL, root, temp = NULL;
	setlocale(LC_ALL, "Russian");
	int n, nAfter;
	cout << "Введите число студентов ";
	cin >> n;
	nAfter = n;
	//temp = new Node;
	Head = new Node;
	Head->next = NULL;
	temp = tail = new Node;
	tail->prev = NULL;
	for (int i = 0; i < n; i++) {
		CreateNode(Head, NewNode, root, tail, temp);
	}
	prohod = Head;//prohod - временная переменная для прохода по списку
	cout << endl << "before deletion" << endl;
	print(prohod, n);
	prohod = Head;
	del(prohod, Head, n, nAfter);
	prohod = Head;
	cout << endl << "after deletion" << endl;
	print(prohod, nAfter);

	_getch();
	return 0;
}

