//==========================================================================================
#include <iostream>
#include "save.h"

class Dog;	// forward declaration

void change(int*, int*);
void change(Dog&, Dog&);

void change(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}



class Dog {
private:
	int num;
public:
	Dog() = default;
	Dog(int n) : num{ n } {}

	operator int() {
		return num;
	}

};

void change(Dog& a, Dog& b)
{
	Dog temp{ a };
	a = b;		// operater
	b = temp;
}

int main()
{
	// [문제] 의도대로 실행되게 하자
	{
		// using Dog = int	// #define Dog int 이건 사용하면 안된다.
		// Dog는 class로 작성하자
		
		Dog a{ 1 }, b{ 2 };
		change(a, b);
		std::cout << a << ", " << b << std::endl;
	}

	{
		int a{ 1 }, b{ 2 };
		change(&a, &b);
		std::cout << a << ", " << b << std::endl;
	}

	//save("메인.cpp");
}
