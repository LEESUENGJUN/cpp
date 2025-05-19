#include "MonsterWorld.h"
#include <ctime>

int main() {
    srand((unsigned int)time(NULL));
    int w = 16, h = 8;
    MonsterWorld game(w, h);

    game.add(new Smombi("스몸비", "▽", rand() % w, rand() % h));
    game.add(new Siangshi("상시", "↕", rand() % w, rand() % h, false, 15));
    game.add(new Jangsanbeom("장산범", "※", rand() % w, rand() % h));

    game.play(500, 10);
    printf("------ 게임 종료 -------------------\n");
    return 0;
}
