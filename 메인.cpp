//==========================================================================================
// 많은 수의 자료 다루기 - file i/o

#include <iostream>
#include <fstream>
#include <algorithm>
#include "save.h"

using namespace std;


int main()
{
	// [문제] int로 표현할 수 있는 값은 -2147483648 ~ 2147483647 까지 이다.
	// 모든 int 값을 하나도 빼지 않고 한 개씩 파일에 text로 기록하였다.
	// 값과 값은 빈칸 한 개로 구분하였다.
	// 이렇게 하면 int 를 한 개 기록하는데 평균 몇 byte가 필요한지 계산하라.
	
	int cnt = 0;
	for(int i = numeric_limits<int>::min(); i <= numeric_limits<int>::max(); i++)
	{
		cnt++;
	}
		
	cout << cnt*4;
	
	//save("메인.cpp");
}
