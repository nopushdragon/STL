//==========================================================================================
// 호출가능 타입 - callable types
// 1. 함수
//	- 함수 포인터도 가능
// 2. lambda
// 3. () 연산자를 구현한 클래스 - 객체를 functor (함수객체)라 함
// 4. 멤버함수와 멤버함수 포인터 
//
// ----> function 클래스로 일관된 사용 가능

#include <iostream>
#include "save.h"

using namespace std;

int main()
{
	[]() {
		cout << "안녕 난 람다야 반가워!" << endl;
		}();

	// 람다 표현식은 아래와 같이 컴파일러가 내부적으로 클래스 형태로 변환하여 처리한다.

	class HUNGRY {
	public:
		void operator()() {	// 함수 호출 연산자 오버로딩, 현재는 딱히 리턴값 없으니 void
			cout << "안녕 난 람다야 반가워!" << endl;
		};
	};

	HUNGRY a;
	a();

	cout << typeid(a).name() << endl;

	//save("메인.cpp");

}
