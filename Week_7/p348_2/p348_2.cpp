#include "p348_2.h"

// 기본 생성자
MyTime::MyTime() {
    hour = 0;
    minute = 0;
    second = 0;
    millisecond = 0;
}

// 4개 매개변수 생성자
MyTime::MyTime(int h, int m, int s, int ms) {
    hour = h;
    minute = m;
    second = s;
    millisecond = ms;
}

// double(초) 입력 생성자
// 문제 요구사항: 실수형(double) 시간(duration)을 받아 시/분/초/밀리초로 초기화
MyTime::MyTime(double duration) {
    int total_ms = static_cast<int>(duration * 1000);
    hour = total_ms / 3600000;
    total_ms %= 3600000;
    minute = total_ms / 60000;
    total_ms %= 60000;
    second = total_ms / 1000;
    millisecond = total_ms % 1000;
}

// 초(double) 입력 변환 함수
void MyTime::convert(double duration) {
    int total_ms = static_cast<int>(duration * 1000);
    hour = total_ms / 3600000;
    total_ms %= 3600000;
    minute = total_ms / 60000;
    total_ms %= 60000;
    second = total_ms / 1000;
    millisecond = total_ms % 1000;
}

// 시간 출력
void MyTime::print() {
    cout << setfill('0') << setw(2) << hour << ":"
         << setfill('0') << setw(2) << minute << ":"
         << setfill('0') << setw(2) << second << ":"
         << setfill('0') << setw(3) << millisecond << endl;
}

// 두 MyTime 객체를 더한 결과 반환
MyTime MyTime::add(const MyTime& t) {
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

// 시간 초기화
void MyTime::reset() {
    hour = minute = second = millisecond = 0;
}

// 사용자로부터 시간 입력
void MyTime::read() {
    cout << "시간(hour): ";
    cin >> hour;
    cout << "분(minute): ";
    cin >> minute;
    cout << "초(second): ";
    cin >> second;
    cout << "밀리초(millisecond): ";
    cin >> millisecond;
}

// 메인 함수
int main() {
    MyTime t1, t2, t3;

    // 첫 번째 시간 입력
    cout << "[첫 번째 시간 입력]" << endl;
    t1.read();

    // 두 번째 시간 입력
    cout << "[두 번째 시간 입력]" << endl;
    t2.read();

    // 입력된 시간 출력
    cout << "\n[입력된 시간 출력]" << endl;
    cout << "t1: ";
    t1.print();
    cout << "t2: ";
    t2.print();

    // t1과 t2를 더한 결과를 t3에 저장
    t3 = t1.add(t2);
    cout << "\n[t1 + t2 결과]" << endl;
    cout << "t3: ";
    t3.print();

    // 초 단위 입력 후 시간 변환
    cout << "\n[초 단위 입력을 통한 변환 테스트]" << endl;
    MyTime t4;
    double secInput;
    cout << "초(double) 입력: ";
    cin >> secInput;
    t4.convert(secInput);
    cout << "변환된 시간: ";
    t4.print();

    // 시간 초기화 테스트
    cout << "\n[시간 초기화 테스트 (t1)]" << endl;
    t1.reset();
    cout << "초기화된 t1: ";
    t1.print();

    // 새로운 생성자(double duration)로 객체 생성 테스트
    cout << "\n[새로운 생성자 테스트 - 초 입력하여 객체 생성]" << endl;
    MyTime t5(3723.456); // 3723.456초를 입력해서 생성자 호출
    cout << "t5 (3723.456초): ";
    t5.print();

    return 0;
}
