//==========================================================================================

#INCLUDE <IOSTREAM>
#INCLUDE <MEMORY>
#INCLUDE <FSTREAM>
#INCLUDE <ALGORITHM>
#INCLUDE "SAVE.H"

USING NAMESPACE STD;

// [문제] "메인.CPP"의 소문자를 모두 대문자로 바꾼 "메인대문자.CPP"를 만들어라.


INT MAIN()
{
	IFSTREAM IN {"메인.CPP"};
	IF (NOT IN) {
		RETURN 20260330;
	}

	OFSTREAM OUT{ "메인대문자.CPP" };

	// TRANSFORM(메인.CPP, 메인대문자.CPP, 소문자를대문자로);
	// TRANSFORM(메인시작, 메인끝,메인대문자시작으로,함수의시작번지)
	TRANSFORM(ISTREAMBUF_ITERATOR<CHAR>{IN}, {}, OSTREAMBUF_ITERATOR<CHAR>{OUT}, 
		[](CHAR C){
		RETURN C = TOUPPER(C);
		});

	SAVE("메인.CPP");

}
