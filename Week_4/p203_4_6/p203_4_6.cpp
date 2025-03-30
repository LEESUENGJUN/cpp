/* 4.8절의 4x4 퍼즐 게임을 다음과 같이 확장하라.
 (6) 4.7절의 랭킹 보드 프로그램을 참고하여 상위 10개의 게임을 랭킹 파일에 저장하라. */
 #include <iostream>
 #include <cstdlib>
 #include <ctime>
 #include <termios.h>
 #include <unistd.h>
 #include <cstdio>
 #include <vector>
 #include <cstring>
 #include <fstream>
 #include <algorithm>
 
 using namespace std;
 
 const int MAX_DIM = 5;
 int DIM;
 int map[MAX_DIM][MAX_DIM];
 int initialMap[MAX_DIM][MAX_DIM];
 int x, y;
 int moveCount = 0;
 clock_t startTime;
 
 struct Move {
     int fromX, fromY, toX, toY;
 };
 vector<Move> moveHistory;
 
 void saveGame(const string& filename) {
     ofstream out(filename, ios::binary);
     if (!out) {
         cout << "[오류] 게임 저장 실패\n";
         return;
     }
     out.write((char*)&DIM, sizeof(DIM));
     out.write((char*)map, sizeof(map));
     out.write((char*)&x, sizeof(x));
     out.write((char*)&y, sizeof(y));
     out.write((char*)&moveCount, sizeof(moveCount));
     clock_t now = clock();
     out.write((char*)&now, sizeof(now));
     out.close();
     cout << "[안내] 게임이 save.dat에 저장되었습니다.\n";
 }
 
 bool loadGame(const string& filename) {
     ifstream in(filename, ios::binary);
     if (!in) return false;
     clock_t savedTime;
     in.read((char*)&DIM, sizeof(DIM));
     in.read((char*)map, sizeof(map));
     in.read((char*)&x, sizeof(x));
     in.read((char*)&y, sizeof(y));
     in.read((char*)&moveCount, sizeof(moveCount));
     in.read((char*)&savedTime, sizeof(savedTime));
     in.close();
     startTime = clock() - savedTime;
     return true;
 }
 
 void selectSize() {
     cout << "퍼즐 크기를 선택하세요 (3, 4, 5): ";
     cin >> DIM;
     if (DIM < 3 || DIM > 5) {
         cout << "잘못된 입력입니다. 기본값 4x4로 설정합니다.\n";
         DIM = 4;
     }
 }
 
 void initMap() {
     int num = 1;
     for (int i = 0; i < DIM; i++) {
         for (int j = 0; j < DIM; j++) {
             map[i][j] = num++;
         }
     }
     map[DIM - 1][DIM - 1] = 0;
     x = y = DIM - 1;
 }
 
 void draw() {
     system("clear");
     for (int i = 0; i < DIM; i++) {
         for (int j = 0; j < DIM; j++) {
             if (map[i][j] == 0)
                 cout << "    ";
             else
                 printf("%4d", map[i][j]);
         }
         cout << endl;
     }
     cout << "-----------------------------" << endl;
     double seconds = (double)(clock() - startTime) / CLOCKS_PER_SEC;
     printf("이동 횟수: %d\t소요 시간: %.1f초\n", moveCount, seconds);
 }
 
 int getKey() {
     struct termios oldt, newt;
     int ch;
     tcgetattr(STDIN_FILENO, &oldt);
     newt = oldt;
     newt.c_lflag &= ~(ICANON | ECHO);
     tcsetattr(STDIN_FILENO, TCSANOW, &newt);
     ch = getchar();
     tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
     return ch;
 }
 
 int getArrowKey() {
     int ch = getKey();
     if (ch == 27 && getKey() == 91) {
         switch (getKey()) {
             case 65: return 'U';
             case 66: return 'D';
             case 67: return 'R';
             case 68: return 'L';
         }
     } else if (ch == 's' || ch == 'S') return 'S';
     return 0;
 }
 
 void moveTile(char dir, bool record = true) {
     int nx = x, ny = y;
     int fromX = x, fromY = y;
 
     if (dir == 'U') ny++;
     else if (dir == 'D') ny--;
     else if (dir == 'L') nx++;
     else if (dir == 'R') nx--;
     else if (dir == 'S') {
         saveGame("save.dat");
         exit(0);
     }
 
     if (nx < 0 || nx >= DIM || ny < 0 || ny >= DIM) return;
 
     if (record) {
         moveHistory.push_back({fromX, fromY, nx, ny});
     }
 
     swap(map[y][x], map[ny][nx]);
     x = nx; y = ny;
     moveCount++;
 }
 
 bool isSolved() {
     int val = 1;
     for (int i = 0; i < DIM; i++) {
         for (int j = 0; j < DIM; j++) {
             if (i == DIM - 1 && j == DIM - 1) {
                 if (map[i][j] != 0) return false;
             } else {
                 if (map[i][j] != val++) return false;
             }
         }
     }
     return true;
 }
 
 void shuffle(int count) {
     const char directions[4] = {'U', 'D', 'L', 'R'};
     for (int i = 0; i < count; i++) {
         moveTile(directions[rand() % 4], false);
         draw();
         usleep(30000);
     }
     memcpy(initialMap, map, sizeof(map));
     moveHistory.clear();
     moveCount = 0;
 }
 
 void replay() {
     memcpy(map, initialMap, sizeof(map));
     draw();
     usleep(500000);
 
     for (const auto& m : moveHistory) {
         swap(map[m.fromY][m.fromX], map[m.toY][m.toX]);
         x = m.toX;
         y = m.toY;
         draw();
         usleep(300000);
     }
 }
 
 struct RankEntry {
     char name[20];
     int moves;
     float time;
 };
 
 void saveRanking(const RankEntry& entry) {
     vector<RankEntry> rankings;
     ifstream in("rank.dat", ios::binary);
     if (in) {
         RankEntry temp;
         while (in.read((char*)&temp, sizeof(RankEntry))) {
             rankings.push_back(temp);
         }
         in.close();
     }
     rankings.push_back(entry);
     sort(rankings.begin(), rankings.end(), [](const RankEntry& a, const RankEntry& b) {
         if (a.moves == b.moves)
             return a.time < b.time;
         return a.moves < b.moves;
     });
     if (rankings.size() > 10) rankings.resize(10);
 
     ofstream out("rank.dat", ios::binary);
     for (const auto& r : rankings)
         out.write((char*)&r, sizeof(RankEntry));
     out.close();
 
     cout << "현재 랭킹 TOP 10:" << endl;
     int rank = 1;
     for (const auto& r : rankings) {
         printf("%2d위 - %-10s 이동 %3d회, 시간 %.1f초\n", rank++, r.name, r.moves, r.time);
     }
 }
 
 void handleRanking() {
     double seconds = (double)(clock() - startTime) / CLOCKS_PER_SEC;
     char name[20];
     cout << "이름을 입력하세요 (최대 19자): ";
     cin.ignore();
     cin.getline(name, 20);
     RankEntry newEntry;
     strncpy(newEntry.name, name, 20);
     newEntry.moves = moveCount;
     newEntry.time = seconds;
     saveRanking(newEntry);
 }
 
 int main() {
     srand(time(NULL));
     cout << "저장된 게임을 불러오시겠습니까? (y/n): ";
     char ch;
     cin >> ch;
     if (ch == 'y' || ch == 'Y') {
         if (!loadGame("save.dat")) {
             cout << "불러오기 실패. 새 게임을 시작합니다." << endl;
             selectSize();
             initMap();
             int shuffleCount = rand() % 91 + 10;
             shuffle(shuffleCount);
         }
     } else {
         selectSize();
         initMap();
         int shuffleCount = rand() % 91 + 10;
         shuffle(shuffleCount);
     }
 
     draw();
 
     while (true) {
         int key = getArrowKey();
         moveTile(key);
         draw();
 
         if (isSolved()) {
             cout << "퍼즐을 완성하셨습니다! 축하합니다!" << endl;
             handleRanking();
             break;
         }
     }
 
     char enter;
     cout << "당신의 이동 경로를 재생하겠습니까? (엔터): ";
     cin.ignore();
     cin.get(enter);
     replay();
 
     return 0;
 }
 