//==========================================================================================

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include "ZString.h"
#include "save.h"

using namespace std;

extern bool 관찰;	// 관찰하려면 true

int main()
{
	list<ZString> v{ "1", "22", "4444", "55555"};

	// [문제] "22" 다음에 "333"을 추가하라.

	관찰 = true;
	v.emplace(++++v.begin(), "333");
	관찰 = false;

	for(const auto& s : v)
		cout << s << endl;

	//save("메인.cpp");
}

