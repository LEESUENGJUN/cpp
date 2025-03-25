#include <stdio.h>

int reverse(int num);  // 함수 원형 선언

int main() {
    int num;
    printf("숫자를 입력하세요: ");
    scanf("%d", &num);
    printf("역순: %d\n", reverse(num));
    return 0;
}

int reverse(int num) {  // 함수 정의
    int reversed = 0;
    while (num != 0) {
        reversed = reversed * 10 + num % 10;
        num /= 10;
    }
    return reversed;
}
