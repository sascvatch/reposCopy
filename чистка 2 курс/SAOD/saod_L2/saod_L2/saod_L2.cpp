/*
Лабораторная работа №2

1). Разработать процедуру построения случайного дерева поиска (СДП) двумя способами:
рекурсивно и с двойной косвенностью.
2). Построить СДП из 100 вершин, заданных случайно, распечатать обход дерева слева направо.
3). Для построенного дерева вычислить размер, контрольную сумму, высоту и среднюю высоту,
сравнить их с аналогичными характеристиками ИСДП, построить таблицу вида:

n=100  Размер   Контр. сумма  Высота  Средн.высота
ИСДП
СДП

4). Дополнительное задание (на 5+):
Реализовать графическую процедуру изображения дерева на экране.
*/

#include "stdafx.h"

void quickSort(int arr[], int left, int right);
int random(int N);
struct Vertex
{
	int data;
	Vertex* left;
	Vertex* right;
};
//Vertex* SDP(int d, Vertex *root) {
	//if (p == NULL) {
	//	p = new Vertex;
	//	p->data = a[i];
	//}
	//if (p != NULL) {
	//	if(p->data)
	//}else Vertex *p = new Vertex;

//	Vertex **p = &root;
//	while (*p != NULL) {
//		if (d < (*p)->data) {//pointer to class type... what is the structure (*p)?
//			p = &((*p)->left);
//		}
//		else if (d > (*p)->data) p = &((*p)->right);
//		else break;//the data is already in the tree
//
//	}
//	if (*p == NULL) {
//		Vertex(*p) = new Vertex;
//		(*p)->data = d;
//		(*p)->left = NULL;
//		(*p)->right = NULL;
//	}
//
//}

//void SDPrek(int *d, int &i, Vertex*&p) {//*& is like **, but to invoke the pointer you don't have to use *
//	if (p == NULL) {//the case for the last Vertex
//		(p) = new Vertex;
//		(p)->data = d[i++];
//		(p)->left = NULL;
//		(p)->right = NULL;
//		//return p;
//	}
//	else if (d[i] < p->data) {
//		p->left = new Vertex;
//		p->left->data = d[i++];
//		SDPrek(d, i, p->left);
//	}
//	else if (d[i] > p->data) {
//		p->right = new Vertex;
//		p->right->data = d[i++];
//		SDPrek(d, i, p->right);
//	}
//		
//}//else //vertex exists in the tree

int max(int a, int b) {
	if (a > b)return a;
	else return b;
}

int sizeoftree(Vertex* p, int &count)
{
	if (p == NULL) count = 0;
	else count = 1 + sizeoftree(p->left, count) + sizeoftree(p->right, count);
	return count;
}

int htree(Vertex* p, int &count)
{
	if (p == NULL) count = 0;
	else count = 1 + max(htree(p->left, count), htree(p->right, count));
	return count;
}

int medsizetree(Vertex* p, int L, int &count)
{
	if (p == NULL) count = 0;
	else count = L + medsizetree(p->left, L + 1, count) + medsizetree(p->right, L + 1, count);
	return count;
}
int sum(Vertex *p, int &count)
{
	if (p == NULL) count = 0;
	else count = p->data + sum(p->left, count) + sum(p->right, count);
	return count;
}

Vertex* ISDP(int L, int R, int *a, int m) {//perfectly balanced search tree

	if (L > R)return NULL;
	else m = ceil((L + R) / (double)2);
	Vertex *p = new Vertex;
	//printf("a vot i chislo m = %d\n", m);
	p->data = a[m];
	p->left = ISDP(L, m - 1, a, m);
	p->right = ISDP(m + 1, R, a, m);
	//printf("p->data = %d\n", p->data);
	return p;

}


void SDPAdd(int D, Vertex*& root)
{
	Vertex** p = &root;
	while ((*p) != NULL)
	{
		if (D < (*p)->data) p = &((*p)->left);
		else if (D >(*p)->data) p = &((*p)->right);
		else break;
	}
	if ((*p) == NULL)
	{
		(*p) = new Vertex;
		(*p)->data = D;
		(*p)->left = NULL;
		(*p)->right = NULL;
	}
}

void SDPREC(int D, Vertex *&p)
{
	if (!p)
	{
		p = new Vertex;
		p->data = D;
		p->left = NULL;
		p->right = NULL;
	}
	else if (D < p->data) SDPREC(D, p->left);
	else if (D > p->data) SDPREC(D, p->right);

}

void Obhod2(Vertex *p) {//to the left
	if (p != NULL) {
		Obhod2(p->left);
		printf("p-data = %d; ", p->data);
		Obhod2(p->right);
		
	}
	printf("\n");
}
int main()
{
	setlocale(LC_ALL, "RUS");
	srand(NULL);
	int aa = 0, bb = 12364, cnt = 0, i = 1 ;
	const int number = 100;
	int a[number];
	
	//= { 100, 3, 23, 15,39, 70, 17 };
	for (int i = 0; i < number; i++)
	{
		a[i] = random(bb - aa + 1) + aa;
	}
	for (int i = 0; i < number; i++)
	{
		printf("a[%d] = %d; ", i, a[i]);
	}
	printf("\n");
	Vertex* root2  = new Vertex;
	root2->data = a[0];
	root2->left = NULL;
	root2->right = NULL;
	for (int i = 1; i < number; i++)
		SDPREC(a[i], root2);
	Obhod2(root2);

	Vertex *root3 = NULL;
	for (int i = 0; i < number; i++)
	{
		SDPAdd(a[i], root3);
	}
	Obhod2(root3);
	
	quickSort(a, 0, number-1);

	int m = 0;
	Vertex *root = ISDP(0, number-1, a, m);

	printf("n=100     Размер  Контр.сумма  Высота  Средн.высота \n");
	
	printf("   ИСДП %8d%12d%8d%14.2f\n", sizeoftree(root, cnt), sum(root, cnt), htree(root, cnt), (float)medsizetree(root, 1, cnt) / (float)sizeoftree(root, cnt));
	cnt = 0;
	printf("СДПрек  %8d%12d%8d%14.2f\n", sizeoftree(root2, cnt), sum(root2, cnt), htree(root2, cnt), (float)medsizetree(root2, 1, cnt) / (float)sizeoftree(root2, cnt));
	printf("СДПпро  %8d%12d%8d%14.2f\n", sizeoftree(root3, cnt), sum(root3, cnt), htree(root3, cnt), (float)medsizetree(root3, 1, cnt) / (float)sizeoftree(root3, cnt));
	
	//There's less size because SDP doesn't add equal numbers

	getchar();
	return 0;
}

int random(int N) { return rand() % N; }

void quickSort(int arr[], int left, int right) {

	int i = left, j = right;

	int tmp;

	int pivot = arr[(left + right) / 2];

	/* partition */

	while (i <= j) {

		while (arr[i] < pivot)

			i++;

		while (arr[j] > pivot)

			j--;

		if (i <= j) {

			tmp = arr[i];

			arr[i] = arr[j];

			arr[j] = tmp;

			i++;

			j--;

		}

	};



	/* recursion */

	if (left < j)

		quickSort(arr, left, j);

	if (i < right)

		quickSort(arr, i, right);

}