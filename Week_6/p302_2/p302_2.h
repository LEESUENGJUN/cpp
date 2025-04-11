#ifndef P302_2_H
#define P302_2_H

#include <string>
using namespace std;

const int MAXWORDS = 100; // 단어 수 제한용 상수 정의

// 단어 하나를 나타내는 구조체
// 구조체: 다양한 자료형을 하나로 묶음. 클래스의 전신 역할.
struct WordPair {
    string eng; // 영어 단어
    string kor; // 한글 뜻
};

// 클래스 선언부
// 클래스: 구조체에서 진화하여 멤버함수 포함, 캡슐화 지원
class MyDic {
    WordPair words[MAXWORDS]; // 배열과 구조체 활용
    int nwords = 0;           // 현재 저장된 단어 수

public:
    // 멤버함수 정의: 클래스 내에서 동작하는 기능 단위
    void add(string eng, string kor);     // 단어 추가
    void load(string filename);           // 파일에서 불러오기
    void store(string filename);          // 파일로 저장
    void print();                         // 전체 단어 출력
    int size();                           // 저장된 단어 수 반환
};

#endif
