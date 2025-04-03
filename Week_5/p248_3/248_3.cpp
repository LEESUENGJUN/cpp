#include <iostream>
using namespace std;

// 시간 정보를 저장하는 구조체
struct MyTime {
    int hour;   // 시
    int min;    // 분
    int sec;    // 초
    int msec;   // 밀리초
};

// 1. 두 시간을 더하고 결과를 반환하는 함수
MyTime addTime(MyTime t1, MyTime t2) {
    MyTime result;
    
    // 밀리초 계산 및 초로 반영
    result.msec = t1.msec + t2.msec;
    result.sec = t1.sec + t2.sec + result.msec / 1000;
    result.msec %= 1000;

    // 초 계산 및 분으로 반영
    result.min = t1.min + t2.min + result.sec / 60;
    result.sec %= 60;

    // 분 계산 및 시로 반영
    result.hour = t1.hour + t2.hour + result.min / 60;
    result.min %= 60;

    return result;
}

// 2. 참조형 매개변수를 사용하여 결과를 외부에 저장하는 함수
void addTime(MyTime t1, MyTime t2, MyTime& t3) {
    // 밀리초 계산 및 초로 반영
    t3.msec = t1.msec + t2.msec;
    t3.sec = t1.sec + t2.sec + t3.msec / 1000;
    t3.msec %= 1000;

    // 초 계산 및 분으로 반영
    t3.min = t1.min + t2.min + t3.sec / 60;
    t3.sec %= 60;

    // 분 계산 및 시로 반영
    t3.hour = t1.hour + t2.hour + t3.min / 60;
    t3.min %= 60;
}

// 3. 포인터 매개변수를 사용하여 결과를 저장하는 함수
void addTime(MyTime t1, MyTime t2, MyTime* pt) {
    // 밀리초 계산 및 초로 반영
    pt->msec = t1.msec + t2.msec;
    pt->sec = t1.sec + t2.sec + pt->msec / 1000;
    pt->msec %= 1000;

    // 초 계산 및 분으로 반영
    pt->min = t1.min + t2.min + pt->sec / 60;
    pt->sec %= 60;

    // 분 계산 및 시로 반영
    pt->hour = t1.hour + t2.hour + pt->min / 60;
    pt->min %= 60;
}

int main() {
    MyTime t1, t2;

    // 사용자로부터 두 시간 입력 받기
    cout << "첫 번째 시간을 입력하세요 (시 분 초 밀리초): ";
    cin >> t1.hour >> t1.min >> t1.sec >> t1.msec;

    cout << "두 번째 시간을 입력하세요 (시 분 초 밀리초): ";
    cin >> t2.hour >> t2.min >> t2.sec >> t2.msec;

    // 방식 1: 반환형 함수 사용
    MyTime result1 = addTime(t1, t2);
    cout << "\n방식 1 결과: " << result1.hour << ":" << result1.min << ":" << result1.sec << "." << result1.msec << endl;

    // 방식 2: 참조형 매개변수 사용
    MyTime result2;
    addTime(t1, t2, result2);
    cout << "방식 2 결과: " << result2.hour << ":" << result2.min << ":" << result2.sec << "." << result2.msec << endl;

    // 방식 3: 포인터 매개변수 사용
    MyTime result3;
    addTime(t1, t2, &result3);
    cout << "방식 3 결과: " << result3.hour << ":" << result3.min << ":" << result3.sec << "." << result3.msec << endl;

    return 0;
}
