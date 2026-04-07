//==========================================================================================
// STL 컨테이너 - std::String 과 유사한 ZString을 만ㄷ르어서 컨테이너 본질에 접근

#include <iostream>
#include <array>
#include <fstream>
#include "save.h"

using namespace std;

class ZString {
public:
	ZString() {
		cout << "생성() 글자수: " << len << " 객체주소: " << this << " 글자주소: " << (void*)p.get() << endl;
	};

	ZString(const char* s) {
		len = strlen(s);
		p = make_unique<char[]>(len);
		memcpy(p.get(), s, len);

		cout << "생성(char*) 글자수: " << len << " 객체주소: " << this << " 글자주소: " << (void*)p.get() << endl;
	}

	friend ostream& operator<<(ostream& os, const ZString& zs) {
		for (int i = 0; i < zs.len; ++i) {
			os << *(zs.p.get() + i);	// os << zs.p[i]; 
		}
		return os;
	}

private:
	size_t len{};
	unique_ptr<char[]> p{};
};

int main()
{
	// 이 동작 다시 설명하고 ZString으로 바꾸면 안되는 이유부터 시작
	string s{ "2026년" };
	string t = move(s);

	cout << "s - " << s << endl;
	cout << "t - " << t << endl;


	//save("메인.cpp");

}
