// MonsterWorld.cpp
#include "MonsterWorld.h"

// 생성자: world 맵에 아이템을 1개씩 채워넣음, 몬스터 수 초기화
MonsterWorld::MonsterWorld(int w, int h)
    : world(h, w), xMax(w), yMax(h), nMon(0), nMove(0), canvas(w, h)
{
    for (int y = 0; y < yMax; ++y)
        for (int x = 0; x < xMax; ++x)
            Map(x, y) = 1;  // 초기 아이템 1
}

MonsterWorld::~MonsterWorld() {
    for (int i = 0; i < nMon; ++i)
        delete pMon[i];
}

void MonsterWorld::print() {
    canvas.print("<Monster World>");
    for (int i = 0; i < nMon; ++i)
        pMon[i]->print();
    Monster::printCount();
}

bool MonsterWorld::isDone() {
    return countItems() == 0;
}

int MonsterWorld::countItems() {
    int sum = 0;
    for (int y = 0; y < yMax; ++y)
        for (int x = 0; x < xMax; ++x)
            sum += Map(x, y);
    return sum;
}

void MonsterWorld::add(Monster* pm) {
    if (nMon < MAXMONS)
        pMon[nMon++] = pm;
}

void MonsterWorld::checkStarvation() {
    for (int i = 0; i < nMon;) {
        if (pMon[i]->getEnergy() <= 0) {
            delete pMon[i];
            pMon[i] = pMon[--nMon];
        } else {
            ++i;
        }
    }
}

void MonsterWorld::play(int maxwalk, int wait) {
    for (nMove = 0; nMove < maxwalk && !isDone() && nMon > 0; ++nMove) {
        canvas.clear();  // 기본 fillChar='.' 로 초기화
        for (int i = 0; i < nMon; ++i)
            pMon[i]->move(world.Data(), xMax, yMax);
        for (int i = 0; i < nMon; ++i)
            pMon[i]->draw(canvas);
        print();
        checkStarvation();
        usleep(wait * 1000);
    }

    std::cout << "\n[게임 종료] 총 이동 횟수: " << nMove
              << ", 남은 몬스터: " << nMon
              << ", 남은 아이템: " << countItems() << "\n";
}
