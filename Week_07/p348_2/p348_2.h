#ifndef P348_2_H
#define P348_2_H

#include <iostream>
#include <iomanip>
using namespace std;

class MyTime {
private:
    int hour;
    int minute;
    int second;
    int millisecond;

public:
    MyTime();                           // 기본 생성자
    MyTime(int h, int m, int s, int ms); // 4개 매개변수 생성자
    MyTime(double duration);            // 문제 요구: double(초) 입력받는 생성자 추가

    void convert(double duration);      // 초(double)를 시분초밀리초로 변환
    void print();                       // 시간 출력
    MyTime add(const MyTime& t);         // 두 시간 합산
    void reset();                       // 시간 초기화
    void read();                        // 사용자로부터 시간 입력
};

#endif
