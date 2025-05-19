// MonsterWorldGame.cpp
#include "MonsterWorld.h"
#include <ctime>

int main() {
    srand((unsigned)time(NULL));
    int w = 16, h = 8;
    MonsterWorld game(w, h);

    // 생성자를 4개 인자로 호출 (초기 에너지 100)
    game.add(new Monster("몬스터", "※", rand() % w, rand() % h));
    game.add(new Monster("도깨비", "§", rand() % w, rand() % h));
    game.add(new Monster("별그대", "★", rand() % w, rand() % h));
    game.add(new Monster("고스트", "♥", rand() % w, rand() % h));

    // 느린 속도로 실행: 대기시간을 500ms로 늘림
    game.play(500, 500);
    return 0;
}
