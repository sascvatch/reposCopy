#include "stdafx.h"
#include <iostream.h>
#include <stdlib.h>
#include <string.h>
#include "Item.h"
typedef struct { char *str; } Item;
static char buf[100000];
static int cnt = 0;
int operator<(const Item& a, const Item& b)
{
	return strcmp(a.str, b.str) < 0;
}
void show(const Item& x)
{
	cout << x.str << " ";
}
int scan(Item& x)
{
	int flag = (cin >> (x.str = &buf[cnt])) != 0;
	cnt += strlen(x.str) + 1;
	return flag;
}