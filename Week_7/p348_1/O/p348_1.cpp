#include "p348_1.h"
int main() {
    MyTime t1, t2, t3;

    // 첫 번째 시간 입력
    std::cout << "[첫 번째 시간 입력]" << std::endl;
    t1.read(); // 사용자로부터 시간 정보를 입력받음

    // 두 번째 시간 입력
    std::cout << "[두 번째 시간 입력]" << std::endl;
    t2.read(); // 사용자로부터 두 번째 시간 입력받음

    // 입력된 시간 출력
    std::cout << "\n[입력된 시간 출력]" << std::endl;
    std::cout << "t1: ";
    t1.print(); // 첫 번째 시간 출력
    std::cout << "t2: ";
    t2.print(); // 두 번째 시간 출력

    // t1 + t2 계산하여 t3에 저장
    t3 = t1.add(t2); // 두 시간 합산
    std::cout << "\n[t1 + t2 결과]" << std::endl;
    std::cout << "t3: ";
    t3.print(); // 계산된 시간 출력

    // 초 단위 입력을 통한 변환 테스트
    std::cout << "\n[초 단위 입력을 통한 변환 테스트]" << std::endl;
    MyTime t4;
    double secInput;
    std::cout << "초(double) 입력: ";
    std::cin >> secInput; // 초 입력받기
    t4.convert(secInput); // 초를 시:분:초:밀리초로 변환
    std::cout << "변환된 시간: ";
    t4.print(); // 변환된 시간 출력

    // 시간 초기화 테스트
    std::cout << "\n[시간 초기화 테스트 (t1)]" << std::endl;
    t1.reset(); // t1 초기화
    std::cout << "초기화된 t1: ";
    t1.print(); // 초기화된 t1 출력

    return 0;
}
