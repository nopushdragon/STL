//==========================================================================================

#include <iostream>
#include <algorithm>
#include <random>
#include <array>
#include <print>
#include <ranges>
#include "save.h"

using namespace std;

default_random_engine dre;
uniform_int_distribution uid{0, 999'9999};

// [문제] 랜덤값을 갖는 int 1000만개를 메모리에 저장하라.
// qsort 를 이용하여 오름차순 정렬하라.
// 정렬 결과를 앞에서부터 1000개만 화면에 출력하라.

array<int, 1000'0000> a;

int 오름차순(const void* a, const void* b) {
	return *(int*)a - *(int*)b;
}

int main()
{
	for (int& b : a) b = uid(dre);

	// 시간 측정 시작
	qsort(a.data(), a.size(), sizeof(array<int,1000'0000>::value_type), 오름차순);
	// 측정 끝

	for (int& num:a | views::take(1000)) {
		print("{:8}", num);
	}

	//save("메인.cpp");

}
