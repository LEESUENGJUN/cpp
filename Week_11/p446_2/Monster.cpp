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
        nItem++;
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
}

void Monster::draw(Canvas& canvas) {
    canvas.draw(x, y, icon);
}

void Monster::print() {
    cout << "	" << name << icon << ":" << nItem << endl;
}

// Jiangshi move
void Jiangshi::move(int** map, int maxx, int maxy) {
    int dir = rand() % 2;
    int jump = 1;
    if (bHori) x += (dir == 0 ? -jump : jump);
    else       y += (dir == 0 ? -jump : jump);
    clip(maxx, maxy);
    eat(map);
}

// Siangshi move
void Siangshi::move(int** map, int maxx, int maxy) {
    moveCount++;
    if (moveCount >= threshold) {
        bHori = !bHori;
        moveCount = 0;
    }
    Jiangshi::move(map, maxx, maxy);
}

// Smombi move
void Smombi::move(int** map, int maxx, int maxy) {
    int dx[] = { -1, -1, 1, 1 };
    int dy[] = { -1, 1, -1, 1 };
    int dir = rand() % 4;
    x += dx[dir];
    y += dy[dir];
    clip(maxx, maxy);
    eat(map);
}

// Jangsanbeom move
void Jangsanbeom::move(int** map, int maxx, int maxy) {
    int dx[] = { -2, 2, 0, 0 };
    int dy[] = { 0, 0, -2, 2 };
    int dir = rand() % 4;
    x += dx[dir];
    y += dy[dir];
    clip(maxx, maxy);
    eat(map);
}
