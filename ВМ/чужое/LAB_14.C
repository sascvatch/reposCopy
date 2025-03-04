/* ��᫥���� ��⥣�஢���� */
#include<stdio.h>
#include<conio.h>
#include<math.h>

#define H 0.2
#define E 6

float x,y,x0,y0,xN,yN;
float accuracy,h1,h2;
float x0=2, xN=4;
int i,n;

float f(float x) { return (sqrt(x)); }

float integral(float x1, float x2)
{
	return (2*sqrt(x2*x2*x2)/3-2*sqrt(x1*x1*x1)/3);
}

float integralTR(float x1, float x2, float hTR)
{
	float xTR=0, yTR=0, sum=0;
	int k=0;
	do
	{
		k++;
		xTR=x1+hTR*k;
   	yTR=f(xTR);
		sum+=yTR;
	} while(xTR<=(x2-hTR));
	return ((f(x1)+f(x2)+2*sum)*hTR/2);
}

float integralSM(float x1, float x2, float hSM)
{
	float xSM=0, ySM=0, odd=0, even=0;
	int k=0;
	do
   {
		k++;
		xSM=x1+hSM*k;
      ySM=f(xSM);
		if(k%2==0) even+=ySM;
		else odd+=ySM;
	} while(xSM<=(x2-hSM));
	return ((f(x1)+f(x2)+4*odd+2*even)*hSM/3);
}

int main()
{
	clrscr();
	accuracy=exp(-E*log(10));
	/* �뢮� ⠡���� ���祭�� */
	printf(" %.10f | %.10f \n", x0, y0);
	do
   {
		n++;
		x=x0+H*n;
     	y=f(x);
		printf(" %.10f | %.10f\n", x, y);
	} while(x<=(xN-H));
	getch();
	clrscr();
	printf("��筮���: %.9f\n", accuracy);
	/* ���᫥��� �筮�� ���祭�� ��⥣ࠫ� */
	printf("��筮� ���祭�� ��⥣ࠫ�: %.9f\n", integral(x0,xN));
	/* ���᫥��� ��⥣ࠫ� �� ��㫥 �࠯�権 */
	printf("���祭�� ��⥣ࠫ� �� ��㫥 �࠯�権: %.9f\n", integralTR(x0,xN,H));
	/* ���᫥��� ��⥣ࠫ� �� ��㫥 ����ᮭ� */
	printf("���祭�� ��⥣ࠫ� �� ��㫥 ����ᮭ�: %.9f\n", integralSM(x0,xN,H));
	/* ��⮤ �������� ������ ��� �࠯�権 */
	printf("\n");
	n=0; h1=H;
	do
   {
		h2=h1; h1/=2; n++;
	} while(fabs(integralTR(x0,xN,h2)-integralTR(x0,xN,h1))>3*accuracy);
	printf("��� ��� �࠯�権: %.9f\n",integralTR(x0,xN,h1));
	printf("����� 蠣�: %.9f = H/(2*%d)\n", h1, n);
	/* ��⮤ �������� ������ ��� ����ᮭ� */
	printf("\n"); n=0; h1=H;
	do
   {
		h2=h1; h1/=2; n++;
	} while(fabs(integralSM(x0,xN,h2)-integralSM(x0,xN,h1))>3*accuracy);
	printf("��� ��� ����ᮭ�: %.9f\n", integralSM(x0,xN,h1));
	printf("����� 蠣�: %.9f = H/(2*%d)\n", h1, n);
	getch();
	return 0;
}
