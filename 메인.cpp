//==========================================================================================
// STL 컨테이너 - Containers are objects that store other objects.
// Sequenece Container
// - array<T,N> - 유일하게 컴파일 타임에 size 결정 - STACK, DATA 
// - vector<T> - dynamic (size) array - free-store에 data 관리 



#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <string>
#include "save.h"

using namespace std;

extern bool 관찰;	// 관찰하려면 true

int main()
{
	// [문제] 키보드에서 입력한 모든 정수의 합계를 저장하라.

	// long long sum = accumulate(istream_iterator<int>{cin}, {}, 0LL);
	cout << accumulate(istream_iterator<int>{cin}, {}, 0LL) << endl;

	save("메인.cpp");

}

