#include "Monster.h"
#include <cstdlib>
#include <iomanip>
using namespace std;

void Monster::clip(int maxx, int maxy) {
    if (x < 0) x = 0;
    if (x >= maxx) x = maxx - 1;
    if (y < 0) y = 0;
    if (y >= maxy) y = maxy - 1;
}

void Monster::eat(int** map) {
    if (map[y][x] > 0) {
        map[y][x]--;
        nEnergy += 8;
    }
}

void Monster::move(int** map, int maxx, int maxy) {
    int dx[] = { -1, 1, 0, 0 };
    int dy[] = { 0, 0, -1, 1 };
    int dir = rand() % 4;
    x += dx[dir];
    y += dy[dir];
    clip(maxx, maxy);
    eat(map);
    nEnergy--; // 매턴 소모
}

void Monster::draw(Canvas& canvas) {
    if (isAlive())
        canvas.draw(x, y, icon);
}

void Monster::print() {
    if (isAlive())
        cout << "\t" << name << icon << ":" << nEnergy << endl;
}

void Zombie::move(int** map, int maxx, int maxy) {
    int dx[] = { 0, 1, 0, -1 };
    int dy[] = { -1, 0, 1, 0 };
    int dir = rand() % 4;
    x += dx[dir];
    y += dy[dir];
    clip(maxx, maxy);
    eat(map);
    nEnergy--;
}

void Vampire::move(int** map, int maxx, int maxy) {
    int dir = rand() % 4;
    if (dir == 0) x--;
    else if (dir == 1) x++;
    else if (dir == 2) y--;
    else y++;
    clip(maxx, maxy);
    eat(map);
    nEnergy--;
}

void KGhost::move(int** map, int maxx, int maxy) {
    x = rand() % maxx;
    y = rand() % maxy;
    clip(maxx, maxy);
    eat(map);
    nEnergy--;
}
void KGhost::eat(int** map) {
    if (map[y][x] > 0) {
        map[y][x]--;
        nEnergy += 8;
    }
}

void Jiangshi::move(int** map, int maxx, int maxy) {
    int dir = rand() % 2;
    int jump = rand() % 2 + 1;
    if (bHori) x += (dir == 0 ? -jump : jump);
    else y += (dir == 0 ? -jump : jump);
    clip(maxx, maxy);
    eat(map);
    nEnergy--;
}

void Smombi::move(int** map, int maxx, int maxy) {
    int dx[] = { -1, -1, 1, 1 };
    int dy[] = { -1, 1, -1, 1 };
    int dir = rand() % 4;
    x += dx[dir];
    y += dy[dir];
    clip(maxx, maxy);
    eat(map);
    nEnergy--;
}

void Siangshi::move(int** map, int maxx, int maxy) {
    moveCount++;
    if (moveCount >= threshold) {
        bHori = !bHori;
        moveCount = 0;
    }
    Jiangshi::move(map, maxx, maxy);
}

void Kumiho::eat(int** map) {
    if (map[y][x] > 0) {
        map[y][x]--;
        nEnergy += 10;
    }
}
