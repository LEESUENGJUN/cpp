#include <iostream>
using namespace std;

class TimeHMS {
    int hour, min, sec;

public:
    TimeHMS(int h = 0, int m = 0, int s = 0) : hour(h), min(m), sec(s) {}

    // (1) + 연산자 중복
    TimeHMS operator+(const TimeHMS& t) const {
        int totalSec = sec + t.sec;
        int totalMin = min + t.min + totalSec / 60;
        int totalHour = hour + t.hour + totalMin / 60;
        return TimeHMS(totalHour, totalMin % 60, totalSec % 60);
    }

    // (2) - 연산자 중복
    TimeHMS operator-(const TimeHMS& t) const {
        int total1 = hour * 3600 + min * 60 + sec;
        int total2 = t.hour * 3600 + t.min * 60 + t.sec;
        int diff = total1 - total2;
        if (diff < 0) diff = 0;
        return TimeHMS(diff / 3600, (diff % 3600) / 60, diff % 60);
    }

    // (3) ==, != 연산자 중복
    bool operator==(const TimeHMS& t) const {
        return hour == t.hour && min == t.min && sec == t.sec;
    }
    bool operator!=(const TimeHMS& t) const {
        return !(*this == t);
    }

    // (4) 전위 증감 연산자 ++, --
    TimeHMS& operator++() {
        ++hour;
        return *this;
    }
    TimeHMS& operator--() {
        if (hour > 0) --hour;
        return *this;
    }

    // (5) 후위 증감 연산자 ++, --
    TimeHMS operator++(int) {
        TimeHMS temp = *this;
        sec++;
        normalize();
        return temp;
    }
    TimeHMS operator--(int) {
        TimeHMS temp = *this;
        int total = hour * 3600 + min * 60 + sec;
        if (total > 0) total--;
        hour = total / 3600;
        min = (total % 3600) / 60;
        sec = total % 60;
        return temp;
    }

    // (6) 인덱스 연산자 중복
    int operator[](int idx) const {
        if (idx == 0) return hour;
        else if (idx == 1) return min;
        else if (idx == 2) return sec;
        else {
            cout << "잘못된 인덱스\n";
            return -1;
        }
    }

    // (7) int 형 변환 연산자
    operator int() const {
        return hour * 3600 + min * 60 + sec;
    }

    // (8) double 형 변환 연산자
    operator double() const {
        return hour + min / 60.0 + sec / 3600.0;
    }

    // (9) friend * 연산자 중복
    friend TimeHMS operator*(int n, const TimeHMS& t) {
        int total = n * (int)t;
        return TimeHMS(total / 3600, (total % 3600) / 60, total % 60);
    }

    // (10) friend 입력/출력 연산자
    friend istream& operator>>(istream& is, TimeHMS& t) {
        is >> t.hour >> t.min >> t.sec;
        t.normalize();
        return is;
    }

    friend ostream& operator<<(ostream& os, const TimeHMS& t) {
        os << t.hour << "시간 " << t.min << "분 " << t.sec << "초";
        return os;
    }

private:
    void normalize() {
        int total = hour * 3600 + min * 60 + sec;
        hour = total / 3600;
        min = (total % 3600) / 60;
        sec = total % 60;
    }
};

// (11) 출력
int main() {
    TimeHMS t1(1, 20, 30), t2(4, 35, 46), t3;

    t3 = t1 + t2; // (1)
    cout << "t1 + t2 = " << t3 << endl;

    t3 = t1 - t2; // (2)
    cout << "t1 - t2 = " << t3 << endl;

    cout << "t1 == t2: " << (t1 == t2) << endl; // (3)
    cout << "t1 != t2: " << (t1 != t2) << endl;

    cout << "++t1: " << ++t1 << endl; // (4)
    cout << "--t1: " << --t1 << endl;

    cout << "t1++: " << t1++ << endl; // (5)
    cout << "t1--: " << t1-- << endl;

    cout << "t1[0]: " << t1[0] << ", t1[1]: " << t1[1] << ", t1[2]: " << t1[2] << endl; // (6)

    cout << "(int)t1: " << (int)t1 << "초" << endl; // (7)
    cout << "(double)t1: " << (double)t1 << "시간" << endl; // (8)

    TimeHMS t4 = 2 * t1; // (9)
    cout << "2 * t1 = " << t4 << endl;

    TimeHMS t5;
    cout << "시간 입력(h m s): "; // (10)
    cin >> t5;
    cout << "입력된 시간: " << t5 << endl;

    return 0;
}
