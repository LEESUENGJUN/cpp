#include "MonsterWorld.h"
#include "Tuman.h"

int main() {
    MonsterWorld game(20, 10);
    game.add(new Zombie("Zombie", "Z ", 1, 1));
    game.add(new Vampire("Vampire", "V ", 5, 5));
    game.add(new Tuman("좌(wasd)", "좌", 1, 8, 0));
    game.add(new Tuman("우(키패드4568)", "우", 18, 8, 1));
    game.play(1000, 100);
    return 0;
}
