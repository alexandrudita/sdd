#include<stdio.h>

void interschimbare1(int x, int y)
{
	int temp = x;
	x = y;
	y = temp;
}

void interschimbare2(int*x, int*y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

void interschimbare3(int*x, int*y)
{
	int* temp = x;
	x = y;
	y = temp;
}

void interschimbare4(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

void main()
{
	printf("buna lume \n");
	int x = 10;
	int* p;
	p = &x;//initializare pointer cu adresa variabilei x;
	int& ref = *p;
	int& ref1 = x;

	printf("valoare x: %d \n", x);
	printf("adresa x: %d \n", &x);
	printf("adresa p: %d \n", p);
	printf("valoare p: %d \n", *p);
	int x1 = 10;
	int x2 = 15;

	printf("stare initiala x1=%d, x2=%d \n", x1, x2);

	int temp = x1;
	x1 = x2;
	x2 = temp;
	printf("x1=%d, x2=%d \n", x1, x2);
	printf("interschimbare 1\n");
	interschimbare1(x1, x2);
	printf("x1=%d, x2=%d \n", x1, x2);
	printf("interschimbare 2\n");
	interschimbare2(&x1, &x2);
	printf("x1=%d, x2=%d \n", x1, x2);
	printf("interschimbare 3\n");
	interschimbare3(&x1, &x2);
	printf("x1=%d, x2=%d \n", x1, x2);
	printf("interschimbare 4\n");
	interschimbare4(x1, x2);
	printf("x1=%d, x2=%d \n", x1, x2);
}