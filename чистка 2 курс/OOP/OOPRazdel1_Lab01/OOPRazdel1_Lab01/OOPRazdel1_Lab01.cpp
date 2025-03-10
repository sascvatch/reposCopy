#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iostream>//for cout(for C++ only)
#include <math.h>
using namespace std;// for cout(for C++ only)
char random(char N) { return rand() % N; }
void sortA(char **matr, char *final, int str, int stl) {//works only for square matrix
	int v = 0, st = 0, sl = stl, num = str * stl;
	int sll = stl;
	for (sl = stl - 1; sl >= 0; sl--)// sl - a number of passes(diagonals)
	{
		int sll = sl;
		while (sll < stl) {//for this type of viborka it will be needed to use nonexistent indexes...
			//(if I want to do it in one cycle)
			final[v] = matr[st][sll];
			v++; st++; sll++;
		}
		st = 0;
	}
	sl = 0;
	for (st = 1; st < str; st++)// sl - a number of passes(diagonals)
	{
		int stt = st;
		while (stt < str) {
			final[v] = matr[stt][sl];
			v++; stt++; sl++;
		}
		sl = 0;
	}
}
void sortB(char **matr, char *final, int str, int stl) {
	int v = 0, st = 0, sl = stl, num = str * stl;
	int sll = stl;
	for (sl = 0; sl < stl; sl++)
	{
		int sll = sl;
		while (sll >= 0) {
			final[v] = matr[st][sll];
			v++; st++; sll--;
		}
		st = 0;
	}
	sl = stl - 1;
	for (st = 1; st < str; st++)
	{
		int stt = st;
		while (stt < str) {
			final[v] = matr[stt][sl];
			v++; stt++; sl--;
		}
		sl = stl - 1;
	}
}
void sortC(char **matr, char *final, int str, int stl) {//finalize(for even numbers)
	int mel = 0;
	int melst = 0;
	int melsl = 0;
	if (str % 2 == 1) {
		mel = str / 2;
		melst = str / 2;//mel - middle element
		melsl = str / 2;
	}
	else {
		mel = ((str / 2) - 1);
		melst = ((str / 2) - 1);//mel - middle element
		melsl = ((str / 2) - 1);
	}

	int sl = stl, st = str;
	int slch = 0, stch = 0;
	int cnt = 1;
	int flag = 0;
	int flag2 = 0;
	int flag3 = 0;// 1 indicates the last upper horizontal pass

	final[0] = matr[melst][melsl];
	//int s = final[0];
	//cout << s << " ";

	for (int i = 1; i < (str * stl -1); )
	{
		if (cnt == str) { cnt--; flag3 = 1; }
		for (int j = 0; j < abs(cnt); j++)
		{
			if (flag % 2 == 0)
				final[i++] = matr[melst][melsl += cnt / abs(cnt)];
			else
				final[i++] = matr[melst += cnt / abs(cnt)][melsl];
			//int s = final[--i]; i++;
			//cout << s << " ";
		}
		if (flag3 == 1)break;
		flag++;
		for (int j = 0; j < abs(cnt) && i < (str * stl -1); j++)
		{
			if (flag % 2 == 0)
				final[i++] = matr[melst][melsl += cnt / abs(cnt)];
			else
				final[i++] = matr[melst += cnt / abs(cnt)][melsl];
			//int s = final[--i]; i++;
			//cout << s << " ";
		}
		flag++;
		flag2++;
		cnt = abs(cnt);
		cnt++;
		cnt *= pow(-1, flag2);

		if (slch > (mel + 1) || stch >= (mel + 1))break;
	}
	//cout << endl;
	//getchar();
}
void sortD(char **matr, char *final, int str, int stl) {
	int cnt = 0;
	int a = 0, b = 1, c = 0, d = 0;
	final[0] = matr[0][0];
	//int s = final[0];
	//cout << s << ' ';
	for (int i = 1; i <= str * stl;)
	{
		int tmp = b;
		while (a <= b && i <= str * stl) {
			final[i++] = matr[a++][b];//in the last pass a is increased, but I don't want that
			//int s = final[--i]; i++;
			//cout << s << " ";
		}
		a--;//--a because of what's written upper
		while (b > 0 && i <= str * stl) {
			final[i++] = matr[a][--b];
			//int s = final[--i]; i++;
			//cout << s << " ";
		}
		b = ++tmp;
		a = 0;
	}//cout << endl;
}

void randArr(char **matrR) {
	int str = 10;//a number of lines

	for (int i = 0; i < str; i++)
	{
		int y = rand() % 10;
		matrR[i] = new char[y];
		for (int j = 0; j < y; j++)
		{
			matrR[i][j] = rand() % 90;
			int s = matrR[i][j];
			cout << s << " ";
		}cout << endl;
	}

}

int main()
{
	srand(time(NULL));
	int str = 5, stl = 5;
	char l = 120, k = -30;
	char **matr;
	char **matrR;
	char *final;// matr - указатель на массив указателей
	final = new char[str*stl];

	matr = new char*[str];// выделяем память под массив указателей //checking sort_ methods here
	for (int i = 0; i < str; i++)
	{
		matr[i] = new char[stl];// Выделяем память под i-ю строку
		for (int j = 0; j < stl; j++)
		{
			matr[i][j] = rand() % 90;
			int g = matr[i][j];
			cout.width(4);
			cout << g << " ";

		}
		cout << endl;
	}
	sortC(matr, final, str, stl);
	for (int i = 0; i < str*stl; i++)
	{
		int s = final[i];
		cout << s << " ";
	}
	/*matrR = new char*[str];
	randArr(matrR);*/


	getchar();
	return 0;
}

