/*
(1) Sample 객체의 개수를 관리하는 정적 변수 count와 출력을 해주는 함수 printcount() 를 구현하라.
(2) 생성자 Sample(const char* name)에서 클래스 sample의 name을 this와 new 키워드를 이용하여 초기화하라.
(3) 클래스 Sample의 소멸자 ~Sample()을 만들어라, 소멸자에는 char* name을 동적해제 시켜주는 코드를 작성하라.
(4) 클래스 Sample의 복사 생성자를 만들어라.
 */
#include <iostream>
#include <cstring>
#include "p398_1.h"

using namespace std;

// (1) 정적 변수 정의
int Sample::count = 0;

// 기본 생성자
Sample::Sample() {
    name = nullptr;
    count++;
}

// (2) 문자열 name을 this와 new 키워드로 초기화하는 생성자
Sample::Sample(const char* n) {
    if (n) {
        name = new char[strlen(n) + 1];
        strcpy(this->name, n);  // this 사용
    } else {
        name = nullptr;
    }
    count++;
}

// (4) 복사 생성자
Sample::Sample(const Sample& other) {
    if (other.name) {
        name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
    } else {
        name = nullptr;
    }
    count++;
}

// (3) 소멸자: 동적으로 할당된 name 메모리 해제
Sample::~Sample() {
    delete[] name;
    count--;
}

// (1) 객체 수 출력 함수
void Sample::printCount() {
    cout << "Sample 객체 수: " << count << endl;
}

// 디버깅용 name 출력 함수
void Sample::print() {
    cout << "name: " << (name ? name : "null") << endl;
}

// =====================
// main() 포함
// =====================
int main() {
    Sample::printCount();       // 객체 수: 0
    Sample a("sample");         // name = "sample"
    Sample::printCount();       // 객체 수: 1
    Sample b(a);                // 복사 생성자 호출
    Sample::printCount();       // 객체 수: 2
    a.print();                  // name: sample
    b.print();                  // name: sample
    return 0;                   // 소멸자 호출 → count 감소
}
