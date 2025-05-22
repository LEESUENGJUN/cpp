/*p147_5번 문제
3.8 절의 러시안 룰렛 게임을 다음과 같이 확장하라.
1. 6연발 권총이 아니라 n-연발 권총이다. n은 사용자로부터 입력받는다.
2. 모든 총알이 발사될 때까지 게임을 진행한다. 
   예를 들어, 5명이 2발의 총알을 넣어 게임을 한다면 두 명이 총알을 맞는다. */

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    int nTurns, n, m;  // 플레이어 수(nTurns), 탄창 크기(n), 총알 개수(m)

    //  1. 사용자 입력 받기
    cout << "게임 인원: ";
    cin >> nTurns;

    cout << "탄창 크기: ";
    cin >> n;

    cout << "총알 개수: ";
    cin >> m;

    // 입력값 검증
    if (m > n || m < 0 || nTurns <= 0) {
        cout << "잘못된 입력입니다. 프로그램 종료.\n";
        return 1;
    }

    //  2. 탄창 배열 초기화 (0 = 빈 칸, 1 = 총알)
    int* chamber = new int[n]();  // 동적 배열 생성 및 초기화

    //  3. 랜덤하게 총알 삽입
    srand(time(0));  // 현재 시간을 기준으로 난수 생성기를 초기화
    for (int i = 0; i < m; i++) {
        int pos;
        do {
            pos = rand() % n;  // 0~n-1 사이의 난수를 생성하여 총알 위치 설정
        } while (chamber[pos] == 1);  // 이미 총알이 있는 위치라면 다시 랜덤 생성
        chamber[pos] = 1;  // 총알 삽입
    }

    //  4. 게임 진행
    cout << "\n게임 시작을 시작합니다. 방아쇠를 당깁니다.\n";

    int currentPlayer = 0;  // 현재 차례인 플레이어 (0부터 시작)
    int firedBullets = 0;   // 발사된 총알 수

    for (int i = 0; i < n; i++) {
        cout << "플레이어 " << (currentPlayer + 1) << "의 차례! 방아쇠를 당깁니다...\n";

        //  5. 총 발사 여부 확인
        if (chamber[i] == 1) {
            cout << "총알 발사! 플레이어 " << (currentPlayer + 1) << " 빵~~~~~!!!\n";
            firedBullets++;  // 발사된 총알 수 증가
        } else {
            cout << "휴~~~살았습니다!!!\n";
        }

        //  6. 게임 종료 조건 확인
        if (firedBullets == m) {
            cout << "모든 총알이 발사되었습니다. 게임 종료!\n";
            break;
        }

        //  7. 다음 플레이어에게 턴 넘기기
        currentPlayer = (currentPlayer + 1) % nTurns;
    }

    //  8. 동적 배열 해제 (메모리 누수 방지)
    delete[] chamber; 

    return 0;
}
