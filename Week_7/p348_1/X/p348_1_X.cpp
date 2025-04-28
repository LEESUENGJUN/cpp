#include <iostream>
#include <iomanip>
using namespace std;

// MyTime 클래스 정의
class MyTime {
private:
    int hour;
    int minute;
    int second;
    int millisecond;

public:
    // 기본 생성자
    MyTime() {
        hour = 0;
        minute = 0;
        second = 0;
        millisecond = 0;
    }

    // 매개변수 생성자
    MyTime(int h, int m, int s, int ms) {
        hour = h;
        minute = m;
        second = s;
        millisecond = ms;
    }

    // 초(double) 단위를 시/분/초/밀리초로 변환
    void convert(double duration) {
        int total_ms = static_cast<int>(duration * 1000);
        hour = total_ms / 3600000;
        total_ms %= 3600000;
        minute = total_ms / 60000;
        total_ms %= 60000;
        second = total_ms / 1000;
        millisecond = total_ms % 1000;
    }

    // 시간을 00:00:00:000 형식으로 출력
    void print() {
        cout << setfill('0') << setw(2) << hour << ":"
             << setfill('0') << setw(2) << minute << ":"
             << setfill('0') << setw(2) << second << ":"
             << setfill('0') << setw(3) << millisecond << endl;
    }

    // 두 MyTime 객체를 더한 결과 반환
    MyTime add(const MyTime& t) {
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

    // 모든 멤버 변수 초기화
    void reset() {
        hour = minute = second = millisecond = 0;
    }

    // 사용자로부터 시간 입력 받기
    void read() {
        cout << "시간(hour): ";
        cin >> hour;
        cout << "분(minute): ";
        cin >> minute;
        cout << "초(second): ";
        cin >> second;
        cout << "밀리초(millisecond): ";
        cin >> millisecond;
    }
};

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

    // t1 시간 초기화
    cout << "\n[시간 초기화 테스트 (t1)]" << endl;
    t1.reset();
    cout << "초기화된 t1: ";
    t1.print();

    return 0;
}
