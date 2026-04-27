//==========================================================================================
// STL 컨테이너 - Containers are objects that store other objects.
// Sequenece Container
// - array<T,N> - 유일하게 컴파일 타임에 size 결정 - STACK, DATA 
// - vector<T> - dynamic (size) array - free-store에 data 관리 

#include <iostream>
#include <vector>
#include <algorithm>
#include "ZString.h"
#include "save.h"

using namespace std;

extern bool 관찰;	// 관찰하려면 true


int main()
{
	vector<int> v{ 1,2,3,4,5 };

	// [문제] v에서 3을 제거하라. v.size() == 4, 원소{ 1, 2, 4, 5}, v.capacity() == 5

	
	remove(v.begin(), v.end(), 3);
	for(const auto& c : v)
		cout << c << ' ';
	// 1 2 4 5 5
	// remove는 제거된 원소를 뒤로 보내고, 제거된 원소의 개수만큼 뒤에서부터 원소가 중복되어 보인다.


	//save("메인.cpp");
}

