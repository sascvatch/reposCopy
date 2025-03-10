#include "stdafx.h"


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <conio.h>

using namespace std;
typedef struct tabTree Tree;

void AddTree(Tree **root, int D);
Tree *BalansTree(int L, int R, int *mass);
int TreeFind(Tree *p);
int HeightTree(Tree *p);
int Find(Tree *root, int X);
int op;
bool disgrow;
//Tree *q;
//Tree *s;
//Tree *r;

struct tabTree {

	int Key;
	int data;
	struct tabTree *pleft = NULL;
	struct tabTree *pright = NULL;
	int Bal;

};

void quicksort(int mass[], int pleft, int pright) {
	int x = mass[(pleft + pright) / 2];
	int i = pleft;
	int j = pright;
	while (i <= j) {
		while (mass[i] <x)i++;
		while (mass[j] > x)j--;
		if (i <= j) {
			swap(mass[i], mass[j]);
			++i; j--;
		}
	}
	if (j> pleft) quicksort(mass, pleft, j);
	if (i < pright) quicksort(mass, i, pright);
}


/* СДПk */

/* rectree */
void addrec(tabTree *&p, int D) {
	if ((p) == NULL) {
		(p) = (Tree*)malloc(sizeof(Tree));
		(*p).data = D;
		(*p).pleft = (*p).pright = NULL;
	}
	else if (D < (*p).data)
		addrec(p->pleft, D);
	else if (D>(*p).data)
		addrec(p->pright, D);
}

/*АВЛ дерево*/

void LLrotate(tabTree *&p) {
	tabTree *q = (*p).pleft;
	(*q).Bal = 0;
	(*p).Bal = 0;
	(*p).pleft = q->pright;
	(*q).pright = p;
	p = q;

}

void RRrotate(tabTree *&p) {
	tabTree *q = (*p).pright;
	(*q).Bal = 0;
	(*p).Bal = 0;
	(*p).pright = q->pleft;
	(*q).pleft = p;
	p = q;
}

void LL1rotate(tabTree *&p) {
	tabTree *q = (*p).pleft;
	if (q->Bal == 0) {		
		q->Bal = 1;
		p->Bal = -1;
		disgrow = 0;
	}
	else {
		q->Bal = 0;
		p->Bal = 0;
	}
	p->pleft = q->pright;
	q->pright = p;
	p = q;
}

void RR1rotate(tabTree *&p) {
	tabTree *q = (*p).pright;
	if (q->Bal = 0) {
		p->Bal = 1;
		q->Bal = -1;
		disgrow = 0;
	}
	else {
		p->Bal = 0;
		q->Bal = 0;
	}
	p->pright = q->pleft;
	q->pleft = p;
	p = q;
}




void LRrotate(tabTree *&p) {
	tabTree *q = (*p).pleft;
	tabTree *r = (*q).pright;
	if (r->Bal<0) (*p).Bal = +1;
	else (*p).Bal = 0;
	if (r->Bal>0) (*q).Bal = -1;
	else (*q).Bal = 0;
	r->Bal = 0;
	(*p).pleft = r->pright;
	q->pright = r->pleft;
	r->pleft = q;
	r->pright = p;
	p = r;
}

void RLrotate(tabTree *&p) {
	tabTree *q = (*p).pright;
	tabTree *r = (*q).pleft;
	if (r->Bal<0) (*p).Bal = 1;
	else (*p).Bal = 0;
	if (r->Bal>0) (*q).Bal = -1;
	else (*q).Bal = 0;

	(*p).pright = r->pleft;
	q->pleft = r->pright;
	r->pleft = p;
	r->pright = q;
	p = r;
}



void BL(tabTree *&p) {
	if (p->Bal == -1) p->Bal = 0;
	else if (p->Bal == 0) {
		p->Bal = 1;
		disgrow = 0;
	}
	else if (p->Bal == 1) {
		if (p->pright->Bal >= 0) RR1rotate(p);
		else RLrotate(p);
	}
}

void BR(tabTree *&p) {
	if (p->Bal == 1) p->Bal = 0;
	else if (p->Bal == 0) {
		p->Bal = -1;
		disgrow = 0;
	}
	else if (p->Bal == -1) {
		if (p->pleft->Bal <= 0) LL1rotate(p);
		else LRrotate(p);
	}
}


void del(tabTree *&r) {
	tabTree *q = new tabTree;
	if (r->pright != 0) {
		del(r->pright);
		if (disgrow == 1) BR(r);
	}
	else {
		q->data = r->data;
		q = r;
		r = r->pleft;
		disgrow = 1;
	}
}

int grow;
void addtree(int D, tabTree *&p) {//AVL tree building

	if (!p) {
		p = new tabTree;
		(*p).data = D; (*p).pleft = NULL;
		(*p).pright = NULL; (*p).Bal = 0; grow = 1;
	}
	else if ((*p).data > D) {
		addtree(D, p->pleft);
		if (grow == 1) {
			if (p->Bal > 0) { p->Bal = 0; grow = 0; }
			else if ((*p).Bal == 0) { (*p).Bal = -1; grow = 1; }
			else {
				if ((*p).pleft->Bal < 0) { LLrotate(p); grow = 0; }
				else { LRrotate(p); grow = 0; }
			}
		}
	}

	else if ((*p).data < D) {
		addtree(D, p->pright);
		if (grow == 1) {
			if (p->Bal < 0) { p->Bal = 0; grow = 0; }
			else if ((*p).Bal == 0) { (*p).Bal = 1; grow = 1; }
			else {
				if ((*p).pright->Bal > 0) { RRrotate(p); grow = 0; }
				else { RLrotate(p); grow = 0; }
			}
		}
	}
}

void deltree(int x, tabTree *&p) {
	tabTree *q;
	if (!p) {
		p = new tabTree;
		(*p).data = x; (*p).pleft = NULL;
		(*p).pright = NULL; (*p).Bal = 0; disgrow = 1;
	}
	else if (p->data>x) {
		deltree(x, p->pleft);
		if (disgrow == 1) BL(p);
	}
	else if (p->data<x) {
		deltree(x, p->pright);
		if (disgrow == 1) BR(p);
	}
	else {
		q = p;
		if (q->pleft == 0) {
			p = q->pright;
			disgrow = 1;
		}
		else if (q->pright == 0) {
			p = q->pleft;
			disgrow = 1;
		}
		else {
			del(p->pleft);
			if (disgrow == 1) BL(p);
		}
		free(q);
	}
}


/* высота дерева */
int HeightTree(Tree *p) {
	int pl = 0;
	int pr = 0;
	if (p == NULL) return 0;
	else {
		pl = HeightTree(p->pleft);
		pr = HeightTree(p->pright);
		return 1 + ((pl > pr) ? pl : pr);
	}
}

int treesize(Tree *root) {
	if (!root)
		return 0;
	return 1 + treesize(root->pleft) + treesize(root->pright);
}

int treesrsize(Tree *root, int level = 1) {
	if (!root)
		return 0;
	return level + treesrsize(root->pleft, level + 1) + treesrsize(root->pright, level + 1);
}

float treessize(Tree *root) {
	return(float)treesrsize(root) / treesize(root);
}

int checksum(Tree *root) {
	if (!root) return 0;
	return root->data + checksum(root->pleft) + checksum(root->pright);
}

/*вывод дерева*/
int printtree(Tree *root) { // ЛКП
	if (!root)
		return 0;
	printtree(root->pleft);
	printf("%3d", root->data);
	printtree(root->pright);
}

#define N 10 
int masS[N];
int WeightMass[N + 1];
int Matrix[N + 1][N + 1];
int ARmatrix[N + 1][N + 1];
int APmatrix[N + 1][N + 1];
int *mass; Tree *sroot = NULL; int i;

void matree() {
	//построение массива и весов:
	cout << "\nПостроение массива и весов:\n" << endl;
	for (int i = 0; i <= N; i++) {
		masS[i] = i;
		WeightMass[i] = rand() % 25 + rand() % 10;
		cout << "Element mass : " << masS[i] << " Weigth : " << WeightMass[i] << endl;

	}
}


void MatrixPlusWeight() {
	int i, j;
	for (i = 0; i <= N; i++) {
		for (j = 0; j <= N; j++) {
			Matrix[i][j] = 0;

		}
	}

	for (i = 0; i< N; i++) {
		for (j = i + 1; j<N; j++) {
			Matrix[i][j] = Matrix[i][j - 1] + WeightMass[i];
		}
	}
	_getch();
	system("cls");

	cout << "\n\n";
	cout << "\t\t\tМатрица весов: " << endl;
	cout << "\n\n";

	for (i = 0; i<N; i++) {
		for (j = 0; j<N; j++) {
			printf("%10d", Matrix[i][j]);
		}
		cout << "\n";
	}
}
void MatrixCalc(void) {

	//вычисление матриц AP and AR:
	int j2, i2, k, h, m, x, min;

	for (i2 = 0; i2 <= N; i2++) {
		APmatrix[i2][i2] = 0;
	}

	for (i2 = 0; i2 < N - 1; i2++) {
		j2 = i2 + 1;
		APmatrix[i2][j2] = Matrix[i2][j2];
		ARmatrix[i2][j2] = j2;
	}

	for (h = 2; h <= N; h++) {
		for (i2 = 0; i2 < N - h; i2++) {
			j2 = i2 + h;
			m = ARmatrix[i2][j2 - 1];
			min = APmatrix[i2][m - 1] + APmatrix[m][j2];
			for (k = m + 1; k <= ARmatrix[i2 + 1][j2]; k++) {
				x = APmatrix[i2][k - 1] + APmatrix[k][j2];
				if (x < min) {
					m = k;
					min = x;
				}
			}
			APmatrix[i2][j2] = min + Matrix[i2][j2];
			ARmatrix[i2][j2] = m;
		}
	}

	_getch();
	system("cls");

	cout << "\n\n\n\n";


	cout << "\n\t\t\t\tВывод  AР:\n" << endl;
	cout << "    AP";
	for (i2 = 0; i2 < N; i2++) {
		printf("%5d", i2);
	}


	cout << "\n\n";
	for (i2 = 1; i2<N; i2++) {
		printf("%5d|", i2);
		for (j2 = 0; j2 < N; j2++) {

			printf("%5d", APmatrix[i2][j2]);
		}

		cout << "\n";

	}
	_getch();
	system("cls");
	cout << "\n\t\t\t\tВывод  AR:\n" << endl;
	for (i2 = 0; i2 < N; i2++) {
		for (j2 = 0; j2 < N; j2++) {
			printf("%5d", ARmatrix[i2][j2]);
		}
		cout << "\n";
	}
}

void  PrintTreeFromMatrix(int L, int R) {
	int k;

	if (L < R) {
		k = ARmatrix[L][R];
		addrec(sroot, masS[i]);
		PrintTreeFromMatrix(L, k - 1);
		PrintTreeFromMatrix(k, R);
	}

}

int main() {

	Tree *sroot = NULL;
	/*int n, i, X, q1, q2;
	float h1, h2;*/
	//3
	setlocale(0, "RUS");
#define n 8

	srand((unsigned)time(NULL));

	/*mass = (int*)malloc(sizeof(int) * n);
	int cnt = 0;*/
	//1
	int ms[10] = { 54, 11, 44, 55, 77, 82, 35, 17 };
	for(i = 0; i < n; i++){
	//ms[i] = rand()%99+1;
	//grow = 0;

	addtree(ms[i], sroot);
	}   
	printtree(sroot);
	int num = 0;
	while (true) {
		printf("\nInsert a nummber to delete:  ");
		//scanf_s("%d", num);
		std::cin >> num;
		printf("\nnum=%d", num);
		printf("\nsroot.data = %d\n", sroot->data);
		deltree(num, sroot);
		printf("\nsroot.data = %d\n", sroot->data);
		printtree(sroot);
	}

	/*matree();
	MatrixPlusWeight();
	MatrixCalc();
	_getch();
	PrintTreeFromMatrix(0, N);*///2

	_getch();
}

