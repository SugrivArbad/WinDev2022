// header files
#include <cstdio>

// global variable declarations
FILE* fp;

// global fuction declarations
void f1(void);
void f2(void);
void f3(void);

int main()
{
	fp = fopen("log.txt", "a");
	f1();
	f2();
	f3();

	return (0);
}

void f1(void)
{
	fprintf(fp, "f1()\n");
	printf("Inside f1()\n");
	fprintf(fp, "f1()\n");
}

void f2(void)
{
	fprintf(fp, "f2()\n");
	printf("Inside f2()\n");
	fprintf(fp, "f2()\n");
}

void f3(void)
{
	fprintf(fp, "f3()\n");
	printf("Inside f3()\n");
	fprintf(fp, "f3()\n");
}

