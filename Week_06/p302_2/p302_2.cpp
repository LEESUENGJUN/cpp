#include <iostream>
#include <fstream>
#include <string>
#include "p302_2.h"
using namespace std;

// 클래스의 멤버함수 정의
// 클래스 내부 기능을 외부에서 정의함으로써 캡슐화 실현

// 단어 추가
void MyDic::add(string eng, string kor) {
    if (nwords < MAXWORDS) {
        words[nwords].eng = eng;
        words[nwords].kor = kor;
        nwords++;
    } else {
        cout << "단어장이 가득 찼습니다.\n";
    }
}

// 파일에서 단어 불러오기
// 파일 입출력1: 클래스 기능의 확장 예시
void MyDic::load(string filename) {
    ifstream fin(filename);
    if (!fin) {
        cout << "파일을 열 수 없습니다: " << filename << endl;
        return;
    }
    string eng, kor;
    nwords = 0;
    while (fin >> eng >> kor && nwords < MAXWORDS) {
        words[nwords].eng = eng;
        words[nwords].kor = kor;
        nwords++;
    }
    fin.close();
    cout << "📂 " << nwords << "개의 단어를 불러왔습니다.\n";
}

// 단어장 저장
void MyDic::store(string filename) {
    ofstream fout(filename);
    for (int i = 0; i < nwords; i++) {
        fout << words[i].eng << " " << words[i].kor << endl;
    }
    fout.close();
    cout << "💾 " << nwords << "개의 단어가 저장되었습니다.\n";
}

// 전체 단어 출력
void MyDic::print() {
    if (nwords == 0) {
        cout << "단어장이 비어 있습니다.\n";
        return;
    }
    cout << "\n현재 단어장 목록:\n";
    for (int i = 0; i < nwords; i++) {
        cout << i + 1 << ". " << words[i].eng << " - " << words[i].kor << endl;
    }
}

// 현재 단어 수 반환
int MyDic::size() {
    return nwords;
}

// main 함수: 프로그램 테스트 및 사용자 인터페이스
// 객체를 생성하고 클래스의 기능을 활용하는 예시
int main() {
    MyDic dic; // 클래스 기반 객체 생성
    int choice;

    while (true) {
        cout << "\n===== 나만의 단어장 =====\n";
        cout << "1. 단어 추가\n";
        cout << "2. 단어장 출력\n";
        cout << "3. 파일 저장\n";
        cout << "4. 파일 불러오기\n";
        cout << "0. 종료\n";
        cout << "선택 >> ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string eng, kor;
            cout << "영어 단어: ";
            getline(cin, eng);
            cout << "뜻: ";
            getline(cin, kor);
            dic.add(eng, kor);
            cout << "단어가 추가되었습니다.\n";
            cout << "[Enter를 누르면 메뉴로 돌아갑니다]";
            cin.get();
        }
        else if (choice == 2) {
            dic.print();
            cout << "\n[Enter를 누르면 메뉴로 돌아갑니다]";
            cin.get();
        }
        else if (choice == 3) {
            dic.store("mydic.txt");
            cout << "[Enter를 누르면 메뉴로 돌아갑니다]";
            cin.get();
        }
        else if (choice == 4) {
            dic.load("mydic.txt");
            cout << "[Enter를 누르면 메뉴로 돌아갑니다]";
            cin.get();
        }
        else if (choice == 0) {
            cout << "프로그램을 종료합니다.\n";
            break;
        }
        else {
            cout << "잘못된 입력입니다. 다시 시도해주세요.\n";
            cout << "[Enter를 누르면 메뉴로 돌아갑니다]";
            cin.get();
        }
    }

    return 0;
}
