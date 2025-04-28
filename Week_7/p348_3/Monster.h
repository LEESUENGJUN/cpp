#ifndef MONSTER_H
#define MONSTER_H

#include <string>
using namespace std;

class Canvas; // 전방 선언: Canvas 클래스 사용

// Monster 클래스: 몬스터 속성과 동작 정의
class Monster {
    string name; // 몬스터 이름
    string icon; // 몬스터 아이콘
    int x, y;    // 위치
    int nEnergy; // (1) 에너지 속성 - 조건 (1): 에너지 저장
public:
    // (2) 생성자 - 조건 (2): 에너지 100으로 초기화
    Monster(const string& n, const string& i, int x_, int y_)
        : name(n), icon(i), x(x_), y(y_), nEnergy(100) {}

    void move(int xMax, int yMax); // 자동 랜덤 이동
    void move(int dx, int dy, int xMax, int yMax); // 사용자 제어 이동
    bool eat(int xFood, int yFood); // (3) 아이템 먹기 - 조건 (3): 에너지 관리
    void print() const; // (4) 정보 출력 - 조건 (4): 에너지 포함
    void draw(Canvas& canvas) const; // 캔버스에 그리기
    int getX() const { return x; } // X 좌표 반환
    int getY() const { return y; } // Y 좌표 반환
    int getEnergy() const { return nEnergy; } // 에너지 반환
    string getName() const { return name; } // 이름 반환
};

#endif