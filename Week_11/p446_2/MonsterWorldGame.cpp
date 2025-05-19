#include "MonsterWorld.h"
#include <ctime>

int main() {
    srand((unsigned)time(NULL));
    int w = 16, h = 8;
    MonsterWorld game(w, h);

    game.add(new Zombie("좀비", "§", rand()%w, rand()%h));
    game.add(new Vampire("뱀파이어", "★", rand()%w, rand()%h));
    game.add(new KGhost("도깨비", "♥", rand()%w, rand()%h));
    game.add(new Jiangshi("강시", "↔", rand()%w, rand()%h, true));
    game.add(new Smombi("스몸비", "▽", rand()%w, rand()%h));
    game.add(new Siangshi("상시", "↕", rand()%w, rand()%h, false, 15));
    game.add(new Kumiho("구미호", "🦊", rand()%w, rand()%h));

    game.play(500, 100);
    printf("------ 게임 종료 -------------------\n");
    return 0;
}
