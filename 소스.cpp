/*
#include <iostream>
#include <fstream>
#include <array>
#include <string>
#include <memory>

class Player {
public:
    std::string name;
    int score;
    size_t id;
    size_t num;
    std::unique_ptr<char[]> p;

    void read(std::ifstream& in) {
        // 1. Player 객체 크기만큼 임시 버퍼에 읽기
        //char buffer[sizeof(Player)];
		std::array<char, sizeof(Player)> buffer; // 안전하게 버퍼 크기 관리
        in.read(buffer.data(), sizeof(Player));

        // 2. 멤버 변수 위치(Offset)에 맞춰 값 복사 (MSVC x64 기준 레이아웃)
        // name은 보통 맨 앞에 위치하며, 15자 이하는 SSO(Small String Optimization)로 버퍼 안에 저장됨

        // score, id, num의 위치는 컴파일러 환경에 따라 다를 수 있지만, 
        // 일반적으로 string(32) 뒤에 배치됩니다.
        memcpy(&score, buffer.data() + 32, sizeof(int));
        memcpy(&id, buffer.data() + 40, sizeof(size_t));
        memcpy(&num, buffer.data() + 48, sizeof(size_t));

        // 이름 복구: SSO 덕분에 이름 문자열이 버퍼 앞부분(0~15)에 들어있을 확률이 높음
        // 'a'-'z'로 구성된다는 조건이 있으므로 해당 범위만큼 읽음
        name = std::string(buffer.data(), strnlen(buffer.data(), 15));

        // 3. 자원(p) 복구: 이전에 읽어온 num 바이트만큼 할당 후 실제 데이터 읽기
        if (num > 0 && num < 1000000) { // 비정상적인 num 값 체크 (안전장치)
            p = std::make_unique<char[]>(num);
            in.read(p.get(), num);
        }
    }
};

// 전역 변수
std::array<Player, 300'0000> players;

int main() {
    std::ifstream in("a", std::ios::binary);
    if (!in) {
        std::cout << "파일을 열 수 없습니다." << std::endl;
        exit(20260416);
    }

    // 300만 개 로드
    for (Player& p : players) {
        p.read(in);
    }

    // 마지막 플레이어(2,999,999) 출력
    const auto& last = players[2999999];
    std::cout << "이름:" << last.name << ", 아이디:" << last.id
        << ", 점수:" << last.score << ", 자원수:" << last.num << std::endl << "저장된 글자:" << last.p << std::endl;

    return 0;
}
*/








/*
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include <cstring>

class Player {
public:
    std::string name;
    int score;
    size_t id;
    size_t num;
    std::unique_ptr<char[]> p;

    void read(std::ifstream& in) {
        // 1. 객체 전체 크기만큼 임시 버퍼에 읽기
        // (객체의 실제 메모리 레이아웃을 그대로 복사해옵니다)
        std::vector<char> buffer(sizeof(Player));
        in.read(buffer.data(), sizeof(Player));

        // 2. 오프셋을 이용해 기본 자료형 복사
        // reinterpret_cast를 사용해 버퍼 내의 특정 위치를 멤버 변수 타입으로 해석합니다.
        score = *reinterpret_cast<int*>(buffer.data() + offsetof(Player, score));
        id = *reinterpret_cast<size_t*>(buffer.data() + offsetof(Player, id));
        num = *reinterpret_cast<size_t*>(buffer.data() + offsetof(Player, num));

        // 3. 이름(string) 복구
        // pfyexsy 같이 짧은 이름은 string 객체 내부 버퍼(SSO)에 저장되어 있습니다.
        // string의 오프셋부터 시작해서 'a'-'z' 문자열만 추출합니다.
        char* namePtr = buffer.data() + offsetof(Player, name);
        name = std::string(namePtr, strnlen(namePtr, 15));

        // 4. 별도로 저장된 데이터(p) 읽기
        if (num > 0 && num < 10000000) { // 비정상적인 크기 방지 안전장치
            p = std::make_unique<char[]>(num);
            in.read(p.get(), num);
        }
    }
};

std::vector<Player> players;

int main() {
    std::ifstream in("a", std::ios::binary);
    if (!in) return 20240609;

    // 버퍼링 최적화
    std::vector<char> io_buffer(1024 * 1024);
    in.rdbuf()->pubsetbuf(io_buffer.data(), io_buffer.size());

    players.resize(3000000);

    for (int i = 0; i < 3000000; ++i) {
        players[i].read(in);

        // 진행 상황 확인 (너무 오래 걸리면 답답하니까요)
        if (i % 500000 == 0) std::cout << i << "개 로드 완료..." << std::endl;
    }

    const auto& last = players.back();
    std::cout << "--- 결과 ---" << std::endl;
    std::cout << "이름: " << last.name << ", ID: " << last.id << ", 점수: " << last.score << std::endl;

    if (last.p) {
        std::cout << "저장된 글자: ";
        std::cout.write(last.p.get(), last.num);
        std::cout << std::endl;
    }

    return 0;
}
*/

#include <iostream>
#include <fstream>
#include <array>
#include <print>
#include <chrono>
#include <execution>
#include <ranges>
#include <functional>
#include <algorithm>
#include <string_view>


class Player {
public:
    void read(std::ifstream& in)
    {
        in.read((char*)this, sizeof(Player) - sizeof(std::unique_ptr<char[]>));
        in.ignore(sizeof(std::unique_ptr<char[]>));

        p = std::make_unique<char[]>(num);
        in.read(p.get(), num);
    }

    const std::string& getName() const { return name; }

    int getScore() const { return score; }

    size_t getId() const { return id; }

    size_t getNum() const { return num; }

    const char* getData() const { return p.get(); }

    char* getData() { return p.get(); }

private:
    std::string name;
    int score;
    size_t id;
    size_t num;
    std::unique_ptr<char[]> p;
};

std::array<Player,300'0000> players;


int main()
{
    std::ifstream in{ "2026 STL 과제 파일 - 2022180019",std::ios::binary };
    if (!in) {
        std::cout << "파일이 없습니다." << std::endl;
        return 20260416;
    }

    for (Player& p : players) {
        p.read(in);
        if (!in) break;
    }

    std::print("이름:{:<15}, 아이디:{}, 점수:{}, 자원수:{}, \n저장된 글자:{}\n",
        players.back().getName(), players.back().getId(), players.back().getScore(), players.back().getNum(), players.back().getData());

    std::cout << "=======================================================================================================" << std::endl;
    std::cout << "2번" << std::endl;
    std::cout << "=======================================================================================================" << std::endl;
    // vector를 사용해서 max_elemet 를 쓰지 않고 범위기반 for문으로 돌리면서 가장 큰 점수를 가진 객체들의 주소를 저장하게 하면 원패스로도 가능하지만 
    // 투패스로 하는거랑 걸리는 시간이 유의미하게 있다고 생각하지 않아서 이 버전으로 했다.
    // std::execution::par_unseq 옵션을 추가해서 병렬로 max_element를 처리할 수 있는데 속도가 비슷하거나 오히려 느렸다. 아마 300만개는 그리 많은 개수가 아니거나
    // 람다함수 내에서 단순 연산하고 바로 return 해주는거라서 크게 속도에 차이가 없는 것 같다. 오히려 병렬로 하기위한 과정에서도 시간이 드는 것으로 보인다.
    // std::ranges::max_element와 std::max_element 중 성능 차이가 있을지 알아봤는데 코드 생김새가 더 깔끔해지는 것일 뿐 성능에는 관련이 없다고 했다.
    // 또한 오류인지 모르겠으나 c++20버전에서는 std::ranges::max_element가 인식이 잘 됐는데 최신c++초안의 기능으로 하면 실행은 되지만 빨간줄이 뜬다.

    auto start = std::chrono::high_resolution_clock::now();

    int highScore = std::max_element( players.begin(), players.end(),
        [](const Player& a, const Player& b) {
            return a.getScore() < b.getScore();
        })->getScore();

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "걸린 시간: " << duration << std::endl;

    for (const Player& p : players) {
        if (highScore == p.getScore()) {
            std::print("이름:{:<15}, 아이디:{}, 점수:{}, 자원수:{}, \n저장된 글자:{}\n",
                p.getName(), p.getId(), p.getScore(), p.getNum(), p.getData());
        }
    }

    std::cout << "=======================================================================================================" << std::endl;
    std::cout << "3번" << std::endl;
    std::cout << "=======================================================================================================" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    std::vector<const Player*> ptrs_3;
    ptrs_3.reserve(players.size());
    for (const Player& p : players) {
        ptrs_3.push_back(&p);
    }

    std::sort(std::execution::par, ptrs_3.begin(), ptrs_3.end(),
        [](const Player* a, const Player* b) {
            return a->getId() < b->getId();
        });

    std::ofstream out{ "같은아이디.txt" };
    if (not out) {
        std::cout << "파일 생성 불가능" << std::endl;
        return 20260419;
    }

    bool duplication = false;
    int duplicationCnt = 0;
    for (int i = 1; i < ptrs_3.size(); ++i) {
        if (ptrs_3[i]->getId() == ptrs_3[i - 1]->getId()) {
            if (not duplication) {
                out << ptrs_3[i - 1]->getName() << " " << ptrs_3[i - 1]->getId() << "\n";
                duplication = true;
                duplicationCnt++;
            }
            out << ptrs_3[i]->getName() << " " << ptrs_3[i]->getId() << "\n";
            duplicationCnt++;
        }
        else {
            duplication = false;
        }
    }
    std::cout << "중복 id 개수: " << duplicationCnt << std::endl;

    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "걸린 시간: " << duration << std::endl;

    std::cout << "=======================================================================================================" << std::endl;
    std::cout << "4번" << std::endl;
    std::cout << "=======================================================================================================" << std::endl;

    constexpr std::string_view targetDigits = "0123456789";
    int count = std::count_if(std::execution::par, players.begin(), players.end(),
        [](Player& p) {
            std::sort(p.getData(), p.getData() + p.getNum());

            return std::includes(p.getData(), p.getData() + p.getNum(), targetDigits.begin(), targetDigits.end());
        });
    std::cout << "0~9가 존재하는 객체 개수: " << count << std::endl;

}