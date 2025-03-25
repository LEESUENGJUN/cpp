#include <stdio.h>

int main() {
    int n;
    double pi = 0.0;

    printf("n: ");
    scanf("%d", &n);

    if (n < 0) {
        printf("입력 오류\n");
        return 1;
    }

    for (int i = 0; i <= n; i++) {
        pi += (i % 2 == 0 ? 1.0 : -1.0) / (2 * i + 1);
    }
    pi *= 4;

    printf("π의 근삿값 (n = %d): %.10f\n", n, pi);
    return 0;
}
