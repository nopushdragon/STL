//==========================================================================================
// 많은 수의 자료 다루기 - file i/o

#include <iostream>
#include <fstream>
#include <filesystem>
#include <array>
#include <algorithm>
#include <random>
#include <print>
#include <string>
#include "save.h"

using namespace std;

default_random_engine dre;
uniform_int_distribution uid(0, 9999);
uniform_int_distribution uidNameLen(10, 30);
uniform_int_distribution<int> uidChar('a', 'z');

class Dog {
private:
	string name;	// [10,30] 10이상30이하 길이의 소문자로 구성된 이름  //※(10,30) 10초과30미만
	size_t id;		// [0,9999]

	friend ostream& operator<<(ostream& os, const Dog& dog) {
		print(os, "[{:>4}] - {}", dog.id, dog.name);
		return os;
	}
};

// [문제] 파일 "Dog천마리"에는 class Dog 객체 1000개가 저장되어 있다.
// 파일은 binary mode이고 각 객체는 메모리 크기 그대로 stream의 write 함수로 기록하였다.
// 모든 객체를 한번의 write 함수로 기록하였다
// Dog의 멤버는 위와 같다.
// 메모리로 그대로 읽어 와라.

int main()
{
	ifstream in("Dog천마리", ios::binary);
	if (!in) {
		cout << "Dog 없음" << endl;
		return 20240601;
	}
	
	array<Dog, 1000> dogs;
	
	in.read((char*)dogs.data(), dogs.size() * sizeof(Dog));
	
	for (const Dog& dog : dogs) {
		cout << dog << endl;
	}
	
	//array<Dog, 1000> dogs;
	//for (Dog& dog : dogs) {
	//	in >> dog;
	//	cout << dog << endl;
	//}

	//save("메인.cpp");
}
