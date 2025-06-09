#include "RankingBoard.h"
#include "FileException.h"
#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <string>

using namespace std;

// 비밀번호 입력 (리눅스 터미널에서 입력값 안 보이게)
string getPassword(const string& prompt) {
    cout << prompt;
    termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    string password;
    getline(cin, password);

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    cout << endl;
    return password;
}

int main() {
    RankingBoard rank;

    // !! 저장 실패를 일부러 발생시키는 경로로 변경 !!
    // 일반적으로 쓸 수 없는 경로 (테스트 후 정상 경로로 복구 가능)
    try {
        rank.store("/root/MonsterWorld.rnk");
        cout << "[Info] 랭킹 저장 성공: /root/MonsterWorld.rnk" << endl;
    }
    catch (FileException& e) {
        // (1) 동일한 방법으로 관리자 비밀번호 입력받기
        string passwd = getPassword("[랭킹 저장 실패] 관리자 비밀번호를 입력하세요: ");
        // (2) 비밀번호 틀리면 메시지 출력 및 종료
        if (passwd != "123456") {
            cout << "비밀번호가 맞지 않습니다. 프로그램을 종료합니다." << endl;
            return 1;
        }
        // (3) 비밀번호가 맞으면 새 파일명 받아 저장 재시도
        string newFile;
        cout << "비밀번호 확인됨. 새 랭킹 파일 이름을 입력하세요: ";
        cin >> newFile;
        cin.ignore();
        try {
            rank.store(newFile);
            cout << "랭킹이 새 파일에 저장되었습니다: " << newFile << endl;
        }
        catch (FileException& e2) {
            cout << "랭킹 저장 실패: " << e2.filename << endl;
            return 1;
        }
    }


    return 0;
}
