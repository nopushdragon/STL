//==========================================================================================
#include <iostream>
#include <random>
#include <print>
#include <algorithm>
#include <array>
#include "save.h"

using namespace std;

default_random_engine dre;
uniform_int_distribution uid( 0,9999 );


// 다음 시간 멤버 설명부터 다시
template<class T, int N>
class myArray {
public:
	size_t size() const {	// size_t 매우 큰 값까쥐 가능, const 읽기전용
		return N;
	}

	int& operator[](int idx) {	// [] 연산자 오버로딩, idx는 배열의 인덱스
		return arr[idx];
	}

	T* begin(){	// begin() 멤버 함수, 배열의 시작 주소 반환
		return &arr[0];
	}

	T* end() {	// end() 멤버 함수, 배열의 끝 주소 반환
		return &arr[N];
	}

private:
	T arr[N];
};

int main()
{


	myArray<int,1000> arr;

	for(int i =0; i<arr.size(); ++i) {
		arr[i] = uid(dre);
	}
	
	//for(int& num: arr) {
	//	num = uid(dre);
	//}

	for (int num : arr) {
		print("{:<8}", num);
	}

	auto p = minmax_element(arr.begin(), arr.end());
	cout << endl << *(p.first) << " " << *(p.second) << endl;

	//save("메인.cpp");
}
