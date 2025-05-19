// Monster.cpp
#include "Monster.h"

int Monster::count = 0; // 정적 멤버 변수 정의

void Monster::clip(int maxx, int maxy) {
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x >= maxx) x = maxx - 1;
    if (y >= maxy) y = maxy - 1;
}

void Monster::eat(int** map) {
    if (map[y][x] > 0) {
        map[y][x]--;
        nItem++;
        nEnergy += 8;           // 아이템을 먹으면 에너지 +8
    } else {
        nEnergy -= 1;           // 못 먹으면 에너지 -1
        if (nEnergy < 0) nEnergy = 0;  // 최소 0
    }
}

void Monster::move(int** map, int maxx, int maxy) {
    switch (rand() % 8) {
        case 0: x--; break;
        case 1: x++; break;
        case 2: y--; break;
        case 3: y++; break;
        case 4: x--; y--; break;
        case 5: x++; y++; break;
        case 6: x--; y++; break;
        case 7: x++; y--; break;
    }
    clip(maxx, maxy);
    eat(map);  // 이동 후 아이템 체크 및 에너지 조절
}

void Monster::draw(Canvas& canvas) {
    canvas.draw(x, y, icon);
}

void Monster::print() const {
    std::cout << "\t" << name << icon
              << " : 아이템 " << nItem
              << ", 에너지 " << nEnergy << "\n";
}

void Monster::printCount() {
    std::cout << "현재 몬스터 수 = " << count << "\n";
}

// 소멸자 정의: 에너지가 0일 때 호출
Monster::~Monster() {
    std::cout << "Monster 하나가 굶어 죽습니다.\n";
    --count;
}
