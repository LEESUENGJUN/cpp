/*p147_2번 방법 5 : main.cpp (소스 파일, 함수 정의 + 호출)*/

#include <iostream>
#include "reverse.h"

// 함수 정의
int reverse(int num) {
    int reversed = 0;
    while (num > 0) {
        reversed = reversed * 10 + num % 10;
        num /= 10;
    }
    return reversed;
}

int main() {
    int number;
    std::cout << "정수 입력: ";
    std::cin >> number;

    int reversedNumber = reverse(number); // 함수 호출
    std::cout << "역순 숫자: " << reversedNumber << std::endl;

    return 0;
}
