//==========================================================================================
// 중간고사 4월 21일


#include <iostream>
#include "save.h"

using namespace std;



class Dog {
private:
	string name;	// [1,16]
	int id;			// [0,999'9999]

	friend ostream& operator<<(ostream& os, const Dog& dog) {
		print(os,"[{:7}] - {}", dog.id, dog.name);
		return os;
	}
};

// [문제] 다운받은 "Dog 십만마리" 에는 class Dog 객체 십만개가 저장되어 있다.
// 바이너리 모드로 저장하여 정확하게 4MB이다.
// 메로리로 모두 읽어와라.
// 앞에서부터 100개 출력하여 확인하라.

int main()
{
	//save("메인.cpp");

}
