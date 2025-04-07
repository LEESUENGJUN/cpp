#include <iostream>
using namespace std;

//p248_3번 문제: 두 개의 시간을 더하는 다음 함수를 다음과 같이 세 방법으로 구현하라.
struct MyTime {
    int hour;   // 시
    int min;    // 분
    int sec;    // 초
    int msec;   // 밀리초
};

// 1. 반환형 함수
MyTime addTime(MyTime t1, MyTime t2) { // 두 시간의 합을 계산해 새로운 구조체를 만들어 반환.
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

// 2. 참조형 변수
void addTime(MyTime t1, MyTime t2, MyTime& t3) { // 계산 결과를 함수 외부의 t3에 직접 저장
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

// 3. 포인터 변수
void addTime(MyTime t1, MyTime t2, MyTime* pt) { // pt가 가리키는 메모리 주소에 결과를 저장.
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

    // 방식 1: 반환형 사용
    MyTime result1 = addTime(t1, t2);
    cout << "\n[반환형 함수] 결과: " << result1.hour << "시간 " << result1.min << "분 " << result1.sec << "초 " << result1.msec << "밀리초" << endl;

    // 방식 2: 참조형 사용
    MyTime result2;
    addTime(t1, t2, result2);
    cout << "[참조형 변수] 결과: " << result2.hour << "시간 " << result2.min << "분 " << result2.sec << "초 " << result2.msec << "밀리초" << endl;

    // 방식 3: 포인터 사용
    MyTime result3;
    addTime(t1, t2, &result3);
    cout << "[포인터 변수] 결과: " << result3.hour << "시간 " << result3.min << "분 " << result3.sec << "초 " << result3.msec << "밀리초" << endl;

    return 0;
}
