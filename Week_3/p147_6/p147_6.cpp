#include "p147_6.h"

// 구구단 게임 (1~9 사이의 숫자 곱셈)
int playGugu(int numQuestions) {
    int score = 0;

    for (int i = 0; i < numQuestions; i++) {
        int a = rand() % 9 + 1;
        int b = rand() % 9 + 1;
        int answer, correctAnswer = a * b;

        cout << "[문제 " << (i + 1) << "] " << a << " x " << b << " = ";

        while (true) {
            cin >> answer;
            if (answer == correctAnswer) {
                cout << "정답!" << endl;
                score += 10;  // 정답 시 점수 추가
                break;
            } else {
                cout << "틀렸습니다! 다시 입력하세요: ";
            }
        }
    }
    return score;
}

// 두 자리 곱셈 게임 (10~99 사이의 숫자 곱셈)
int playMul(int numQuestions) {
    int score = 0;

    for (int i = 0; i < numQuestions; i++) {
        int a = rand() % 90 + 10;
        int b = rand() % 90 + 10;
        int answer, correctAnswer = a * b;

        cout << "[문제 " << (i + 1) << "] " << a << " x " << b << " = ";

        while (true) {
            cin >> answer;
            if (answer == correctAnswer) {
                cout << "정답!" << endl;
                score += 10;
                break;
            } else {
                cout << "틀렸습니다! 다시 입력하세요: ";
            }
        }
    }
    return score;
}

// 여러 자리 덧셈 게임 (자리 수에 따라 숫자 생성)
int playAdd(int digits, int numQuestions) {
    int score = 0;

    for (int i = 0; i < numQuestions; i++) {
        int maxNum = static_cast<int>(pow(10, digits)) - 1;
        int minNum = static_cast<int>(pow(10, digits - 1));
        int a = rand() % (maxNum - minNum + 1) + minNum;
        int b = rand() % (maxNum - minNum + 1) + minNum;
        int answer, correctAnswer = a + b;

        cout << "[문제 " << (i + 1) << "] " << a << " + " << b << " = ";

        while (true) {
            cin >> answer;
            if (answer == correctAnswer) {
                cout << "정답!" << endl;
                score += 10;
                break;
            } else {
                cout << "틀렸습니다! 다시 입력하세요: ";
            }
        }
    }
    return score;
}

// 메인 함수
int main() {
    srand(time(0));  // 랜덤 시드 설정

    int choice, numQuestions, score = 0;
    cout << "게임을 선택하세요 (1: 구구단, 2: 두 자리 곱셈, 3~9: 덧셈): ";
    cin >> choice;

    cout << "몇 문제를 풀겠습니까? ";
    cin >> numQuestions;

    if (choice == 1)
        score = playGugu(numQuestions);
    else if (choice == 2)
        score = playMul(numQuestions);
    else if (choice >= 3 && choice <= 9)
        score = playAdd(choice, numQuestions);
    else {
        cout << "잘못된 선택입니다." << endl;
        return 0;
    }

    // 최종 점수 출력
    cout << "게임 종료! 당신의 점수: " << score << "점" << endl;

    return 0;
}
