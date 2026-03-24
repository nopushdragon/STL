//==========================================================================================
// 동적 메모리 할당(Dynamic memory allocation)
// 
// 정적(static): program 할 때 사용할 메모리를 결정 // compile-time	// 이름을 줄 수 있는 변수 ex) int num; stack, data, code 영역에 존재, code에는 함수
// 동적(dynamic): 실행한 이후에 결정할 수 있는 메모리 // run-time // 주소로만 이루어진, 이름을 줄 수 없는 변수, free store에 존재


// 다음시간 -> 스마트 포인터 -> 콜러블 타입 -> 실습 -> STL


#include <iostream>
#include <fstream>
#include <filesystem>
#include <array>
#include <algorithm>
#include <random>
#include <print>
#include <string>
#include <numeric>
#include <memory>
#include "save.h"

using namespace std;

// [문제] 사용자가 입력한 수 만큼 int를 저장할 메모리를 확보하라.
// 1부터 시자가는 정수로 메모리를 채워라.
// 합계를 화면에 출력하라.

int main()
{
	// int* p; -> 사용하지 말아야함
	// c++11(modern c++)에 완벽한 대체 수단이 있음 -> smart_pointer

	unique_ptr<int[]> p;	// unique_ptr은 배열도 지원함 -> unique_ptr<int[]> p; -> p[i]로 접근 가능
	while (1) {
		size_t input;
		cout << "몇 개의 메모리를 원하니: ";
		cin >> input;

		// 설마 음수를 입력하시는 건 아니겠죠? ㅋㅋㅋ << 이거 코파일럿 자동 생성인데 말투 왜이럼

		try {
			//p = new int[input];
			p.reset(new int[input]);	// unique_ptr은 reset() 함수를 통해 메모리를 할당할 수 있음
		}
		catch (exception& e) {
			cout << "메모리 고갈됐어욧 - " << e.what() << endl;
		}

		//iota(p, p + input, 1);
		//
		//long long sum = accumulate(p, p + input, 0LL);	//accumulate(p, p + input, static_cast<long long>(0));
		iota(p.get(), p.get() + input, 1);

		long long sum = accumulate(p.get(), p.get() + input, 0LL);
		cout << "합계: " << sum << endl;

		//delete[] p; // unique_ptr은 delete를 자동으로 해줌 -> 메모리 누수 방지, 예외 안전성 제공
	}

	//save("메인.cpp");
}
