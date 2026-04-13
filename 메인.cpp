//==========================================================================================
// STL 컨테이너 - std::String 과 유사한 ZString을 만ㄷ르어서 컨테이너 본질에 접근

#include <iostream>
#include <array>
#include <algorithm>
#include <fstream>
#include "save.h"
#include "ZString.h"

using namespace std;

extern bool 관찰;	// 관찰하려면 true

int main()
{
	// [문제] "메인.cpp"에 있는 모든 단어를 ZString으로 읽어와라.
	// 단어란 공백을 분리된 문자집합을 말한다.
	// 다음 문장이 문제없이 실행되도록 하자.

	ifstream in{ "메인.cpp" };
	if (!in) {
		cout << "파일 없음" << endl;
		return 20260413;
	}

	ZString s;
	while (in >> s) {
		cout << s << endl;
	}


	//save("메인.cpp");

}

