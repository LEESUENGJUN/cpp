#ifndef P398_1_H
#define P398_1_H

// (1) Sample 객체의 개수를 관리하는 정적 변수와 출력 함수 선언
class Sample {
    char* name;
    static int count;  // (1) 정적 멤버 변수

public:
    Sample();                      // 기본 생성자
    Sample(const char* name);     // (2) this와 new를 이용해 name 초기화
    Sample(const Sample& other);  // (4) 복사 생성자
    ~Sample();                    // (3) 소멸자: name 메모리 해제

    static void printCount();     // (1) 객체 개수 출력 함수
    void print();                 // name 확인용 출력 함수
};

#endif // P398_1_H
