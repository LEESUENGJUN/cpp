#include "MyTime.h"

int main() {
    MyTime t1, t2, t3;

    std::cout << "[첫 번째 시간 입력]" << std::endl;
    t1.read();

    std::cout << "[두 번째 시간 입력]" << std::endl;
    t2.read();

    std::cout << "\n[입력된 시간 출력]" << std::endl;
    std::cout << "t1: ";
    t1.print();
    std::cout << "t2: ";
    t2.print();

    t3 = t1.add(t2);
    std::cout << "\n[t1 + t2 결과]" << std::endl;
    std::cout << "t3: ";
    t3.print();

    std::cout << "\n[초 단위 입력을 통한 변환 테스트]" << std::endl;
    MyTime t4;
    double secInput;
    std::cout << "초(double) 입력: ";
    std::cin >> secInput;
    t4.convert(secInput);
    std::cout << "변환된 시간: ";
    t4.print();

    std::cout << "\n[시간 초기화 테스트 (t1)]" << std::endl;
    t1.reset();
    std::cout << "초기화된 t1: ";
    t1.print();

    return 0;
}
