#include <iostream>

void fun1(int&);

int main(void)
{
	int a = 4;

	fun1(a);
}

void fun1(cosnt int& iRef)
{
	iRef = 5;
	std::cout << " iRef = " << iRef << std::endl;
}
