#include "Monster.h"

// 함수: main
int main() {
    srand((unsigned int)time(NULL));

    int w = 20, h = 10;
    MonsterWorld game(w, h);

    game.add(Monster("몬스터", "♠", 0, 1));
    game.add(Monster("별그대", "★", 0, 9));
    game.add(Monster("고스트", "♥", 19, 1));
    game.add(Monster("도깨비", "♣", 19, 9));

    game.play(100, 10);

    return 0;
}
