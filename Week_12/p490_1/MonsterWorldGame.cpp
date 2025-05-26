#include "MonsterWorld.h"
#include "Tuman.h"

int main() {
    MonsterWorld game(20, 10);
    game.add(new Zombie("Zombie", "Z ", 1, 1));
    game.add(new Vampire("Vampire", "V ", 5, 5));
    // 플레이어 추가
    game.add(new Tuman("좌 플레이어", "좌", 1, 8));
    game.add(new Tuman("우 플레이어", "우", 18, 8));
    game.play(1000, 100);
    return 0;
}
