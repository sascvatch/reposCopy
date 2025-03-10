// saod_L3_i.cpp : Defines the entry point for the console application.
//
#include <locale.h> 
#include "stdafx.h"
#include <iostream>//for cout(for C++ only)// char будет выведен именно буквами, а не численными значениями
using namespace std;

//#include <iostream.h>
#define TRUE 1
#define FALSE 0
struct  node
{
	int Key;
	int Count;
	node *Left;
	node *Right;
};

int random(int N) { return rand() % N; }

class TREE
{
private:
	node * Tree;//Указатель на корень дерева.
	node  *Res;//Указатель на найденную вершину.
	int B; //Признак нахождения вершины в дереве.
		   //Поиск вершины в дереве (рекурсивный алгоритм).
	void Search(int, node**);
	void Delete_1(node**, node**);
public:
	TREE() { Tree = NULL; }
	node** GetTree() { return &Tree; }
	void  BuildTree();//Построение бинарного дерева.
	void BuildTreeAuto();
	//Вывод дерева на экран (рекурсивный алгоритм).
	void Vyvod(node**, int);
	//Поиск вершины в дереве (нерекурсивный алгоритм).
	int Poisk(int);
	//Поиск вершины в дереве (рекурсивный алгоритм).
	node *Poisk_1(int, node **);
	//Добавление вершины в дерево (нерекурсивный алгоритм).
	void Addition(int);
	// Удаление вершины из дерева.
	void Delete(node**, int);
	void Obhod2(node**);
};

void main()
{
	srand(NULL);
	setlocale(LC_ALL, "RUS");
	TREE A;
	int el;

	A.BuildTreeAuto();  A.Vyvod(A.GetTree(), 0);

	//cout << "Введите ключ вершины, которую нужно найти в дереве: ";
	//cin >> el;
	//if (A.Poisk(el)) cout << "В дереве есть такая вершина!\n";
	//else  cout << "В дереве нет такой вершины!\n";
	//cout << "Введите ключ вершины, которую нужно найти в дереве: ";
	//cin >> el;
	//if (A.Poisk_1(el, A.GetTree()) != NULL)
	//	cout << "В дереве есть такая вершина!\n";
	//else  cout << "В дереве нет такой вершины!\n";

	//cout << "Введите ключ добавляемой вершины: ";
	//cin >> el;
	//A.Addition(el);  A.Vyvod(A.GetTree(), 0);

	while (A.GetTree() != NULL) {
		cout << "\nВведите ключ удаляемой вершины: "; cin >> el;
		A.Delete(A.GetTree(), el);  //A.Vyvod(A.GetTree(), 0);
		cout << endl;
		A.Obhod2(A.GetTree());
		
	}

}

void TREE::BuildTree()
//Построение бинарного дерева.
//Tree - указатель на вершину дерева.
{
	int el;

	cout << "Вводите ключи вершин дерева: \n";
	cin >> el;
	while (el != 0)
	{
		Search(el, &Tree); cin >> el;
	}
}
void TREE::Obhod2(node** p) {
	//to the left
	if (*p != NULL) {
		Obhod2(&((**p).Left));
		printf("%d ", (**p).Key);
		Obhod2(&(**p).Right);
	}
}

void TREE::BuildTreeAuto()
//Построение бинарного дерева.
//Tree - указатель на вершину дерева.
{
	int el, i = 0;
	int aa = 0, bb = 100, cnt = 0;

	while (i++ != 10)
	{
		el = random(bb - aa + 1) + aa;;
		Search(el, &Tree);
	}
}

void TREE::Vyvod(node **w, int l)
//Изображение дерева w на экране дисплея
//         (рекурсивный алгоритм).
//*w - указатель на корень дерева.
{
	int i;

	if (*w != NULL)
	{
		Vyvod(&((**w).Right), l + 1);
		for (i = 1; i <= l; i++) cout << "   ";
		cout << (**w).Key << endl;
		Vyvod(&((**w).Left), l + 1);
	}
}


void TREE::Search(int x, node **p)
//Поиск звена x в бинарном дереве со вставкой
//            (рекурсивный алгоритм).
//*p - указатель на вершину дерева.
{
	if (*p == NULL)
	{ // Вершины в дереве нет; включить ее.
		*p = new(node);
		(**p).Key = x;     (**p).Count = 1;
		(**p).Left = (**p).Right = NULL;
	}
	else
		if (x < (**p).Key) Search(x, &((**p).Left));
		else
			if (x > (**p).Key) Search(x, &((**p).Right));
			else  (**p).Count += 1;
}

void TREE::Addition(int k)
// Поиск звена k в бинарном дереве со вставкой
//         (нерекурсивный алгоритм).
// Tree - указатель на вершину дерева.
{
	node *s;

	Poisk(k);
	if (!B)
	{
		s = new(node);
		(*s).Key = k;    (*s).Count = 1;
		(*s).Left = (*s).Right = NULL;
		if (Tree == NULL) Tree = s;
		else
			if (k < (*Res).Key) (*Res).Left = s;
			else  (*Res).Right = s;
	}
	else  (*Res).Count += 1;
}

int TREE::Poisk(int k)
// Поиск вершины с ключом k в дереве
//      (нерекурсивный алгоритм).
// Tree - указатель на бинарное дерево.
// Res  - указатель на найденную вершину
// или на лист, к которому можно присоединить новую вершину.
{
	node *p, *q = NULL;

	B = FALSE; p = Tree;
	if (Tree != NULL)
		do
		{
			q = p;
			if ((*p).Key == k) B = TRUE;
			else
			{
				q = p;
				if (k < (*p).Key) p = (*p).Left;
				else  p = (*p).Right;
			}
		} while (!B && p != NULL);
		Res = q;
		return B;
}

node *TREE::Poisk_1(int k, node **p)
// Поиск вершины с ключом k в дереве
//        (рекурсивный алгоритм).
// *p - указатель на корень дерева.
{
	if (*p == NULL) return (NULL);
	else
		if ((**p).Key == k) return (*p);
		else
			if (k < (**p).Key) return Poisk_1(k, &((**p).Left));
			else return Poisk_1(k, &((**p).Right));
}

void TREE::Delete(node **p, int k)
// Удаление вершины k из бинарного дерева.
// *p - указатель на корень дерева.
{
	node *q;

	if (*p == NULL) cout << "Вершина с заданным ключом не найдена!\n";
	else
		if (k < (**p).Key) Delete(&((**p).Left), k);
		else
			if (k > (**p).Key) Delete(&((**p).Right), k);
			else
			{
				q = *p;
				if ((*q).Right == NULL) { *p = (*q).Left; delete q; }//Если правая или левая дочерние вершины остсутствуют, то просто указать от высшей к нижней, минуя удаляемую
				else
					if ((*q).Left == NULL) { *p = (*q).Right; delete q; }
					else  Delete_1(&((*q).Left), &q);//Иначе идём по спец правилу
			}
}

void TREE::Delete_1(node **r, node **q)//Находим крайнюю наибольшую вершину из левого поддерева и ставим на место удаляемой 
{
	node *s;
	
	if ((**r).Right == NULL)
	{
		(**q).Key = (**r).Key; (**q).Count = (**r).Count;
		*q = *r;
		s = *r; *r = (**r).Left; delete s;
	}
	else  Delete_1(&((**r).Right), q);
}

