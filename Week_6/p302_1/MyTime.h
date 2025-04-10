#ifndef MYTIME_H
#define MYTIME_H

#include <iostream>
#include <iomanip>

// (1)번 : MyTime 클래스를 정의하며, 구조체를 클래스 형태로 변환
class MyTime {
private:
    // (1)번 : 멤버 변수는 모두 private로 설정
    int hour;
    int minute;
    int second;
    int millisecond;

public:
    // (1)번 : 기본 생성자, 초기값은 모두 0
    inline MyTime() : hour(0), minute(0), second(0), millisecond(0) {}

    // (1)번 : 초 단위(double) 시간을 시:분:초:밀리초로 변환
    inline void convert(double duration) {
        int total_ms = static_cast<int>(duration * 1000);
        hour = total_ms / 3600000;
        total_ms %= 3600000;
        minute = total_ms / 60000;
        total_ms %= 60000;
        second = total_ms / 1000;
        millisecond = total_ms % 1000;
    }

    // (1)번 : 시간 정보를 01:02:34:567 형식으로 출력
    // (3)번 : cout과 입출력 조작자(setfill, setw 등) 사용
    inline void print() {
        std::cout << std::setfill('0') << std::setw(2) << hour << ":"
                  << std::setfill('0') << std::setw(2) << minute << ":"
                  << std::setfill('0') << std::setw(2) << second << ":"
                  << std::setfill('0') << std::setw(3) << millisecond << std::endl;
    }

    // (1)번 : 두 MyTime 객체를 더해서 새 MyTime 객체를 반환
    // (2)번 : 기존 일반 함수와 달리 객체 내부 연산을 수행
    inline MyTime add(MyTime t) {
        MyTime result;
        result.millisecond = millisecond + t.millisecond;
        result.second = second + t.second + result.millisecond / 1000;
        result.millisecond %= 1000;

        result.minute = minute + t.minute + result.second / 60;
        result.second %= 60;

        result.hour = hour + t.hour + result.minute / 60;
        result.minute %= 60;

        return result;
    }

    // (1)번 : 모든 멤버 값을 0으로 초기화
    inline void reset() {
        hour = minute = second = millisecond = 0;
    }

    // (4)번 : 사용자로부터 시간 정보를 입력받는 함수
    // cin을 사용하며, 안내 메시지는 cout으로 출력
    inline void read() {
        std::cout << "시간(hour): ";
        std::cin >> hour;
        std::cout << "분(minute): ";
        std::cin >> minute;
        std::cout << "초(second): ";
        std::cin >> second;
        std::cout << "밀리초(millisecond): ";
        std::cin >> millisecond;
    }
};

// (5)번 : 이 클래스는 헤더(MyTime.h)와 메인(MyTime.cpp) 파일로 구성되며,
//              모든 main 함수는 MyTime.cpp에서 구현됨

#endif
