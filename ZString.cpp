//-------------------------------------------------------------------
// STL의 동작을 잘 살펴보려고 만든 std::String과 비슷한 class
//
// 2026.04.13
//-------------------------------------------------------------------
#include <print>
#include <string>
#include "ZString.h"

size_t ZString::gid = 0;			// 외부에서 초기화
bool 관찰{ false };


ZString::ZString()
	:id{ ++gid }
{
	if (관찰) 
		special("생성");
};

ZString::~ZString() 
{
	if (관찰) 
		special("소멸");
};

ZString::ZString(const char* s)
	:id{ ++gid }
{
	len = strlen(s);
	p = std::make_unique<char[]>(len);
	memcpy(p.get(), s, len);

	if(관찰)
		special("생성(*)");
}

// 복사생성과 복사할당연산자
ZString::ZString(const ZString& other)
	:id{ ++gid }
{
	len = other.len;
	p = std::make_unique<char[]>(len);
	memcpy(p.get(), other.p.get(), len);

	if(관찰)
		special("복사생성");
}

ZString& ZString::operator=(const ZString& other)
{
	if (this == &other)
		return *this;

	len = other.len;

	p.reset();
	p = std::make_unique<char[]>(len);
	memcpy(p.get(), other.p.get(), len);

	if(관찰)
		special("복사할당");

	return *this;
}

// 이동생성과 이동할당연산자
// 2026.04.20 move에서 예외를 던지지 않는다.
ZString::ZString(ZString&& other) noexcept
	:id{++gid}
{
	len = other.len;
	p.reset(other.p.release());	// other의 p가 관리하는 메모리를 가져오고, other의 p는 nullptr이 됨
	
	other.len = 0;
	// 자기 자원이 이동된 otehr는 xvalue가 되고 이것을 사용하면 undefined behavior

	if(관찰)
		special("이동생성");
}

ZString& ZString::operator=(ZString&& other) noexcept
{
	if(this == &other)
		return *this;

	len = other.len;
	// 잘 한 건가? 내 메모리 반환했나?
	p.reset(other.p.release());
	other.len = 0;

	if(관찰)
		special("이동할당");

	return *this;
}

size_t ZString::getLen() const
{
	return len;
}

// STL 컨테이너가 되려면 다음 함수정도는 제공해야 - 2026.04.20
size_t ZString::size() const
{
	return len;
}

void ZString::special(std::string 동작) const
{
	// 글자수가 10개 이상이라도 10개까지만 출력
	int num = 10;
	if (len < num)
		num = len;
	std::string 글자{};
	for (int i = 0; i < num; ++i)
		글자 += p[i];

	std::println("[{:7}] {:8} - 객체:{:#014X}, 글자:{:#014X}, 개수:{:<6} 내용:{}",
		id, 동작, (long long)this, (long long)p.get(), len, 글자);
}

void ZString::show() const			// 2026.04.20
{
	special("show");
}

std::ostream& operator<<(std::ostream& os, const ZString& zs) 
{
	for (int i = 0; i < zs.len; ++i) {
		os << *(zs.p.get() + i);	// os << zs.p[i]; 
	}
	return os;
}

// 파일에서 읽어오려고 만듦 - 2026.04.13
std::istream& operator>>(std::istream& is, ZString& zs)
{
	std::string s;
	is >> s;
	zs.len = s.size();
	zs.p.reset();
	zs.p = std::make_unique<char[]>(s.size());
	memcpy(zs.p.get(), s.data(), zs.len);

	return is;
}
