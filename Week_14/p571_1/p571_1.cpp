#include <iostream>
#include <string>
using namespace std;

class AccountException {
    string message;
    int amount;
public:
    AccountException(const string& msg, int amt = 0) : message(msg), amount(amt) {}
    void printError() const {
        cout << "오류: " << message;
        if (amount != 0)
            cout << " (금액: " << amount << ")";
        cout << endl;
    }
};

class CustomerAccount {
    int balance;
public:
    CustomerAccount(int b = 0) : balance(b) {}
    int getBalance() const { return balance; }

    int deposit(int amount) {
        if (amount <= 0)
            throw AccountException("입금 금액이 올바르지 않습니다", amount);
        balance += amount;
        return balance;
    }

    int withdraw(int amount) {
        if (amount > balance)
            throw AccountException("잔액이 부족합니다", amount);
        balance -= amount;
        return balance;
    }
};

int main() {
    CustomerAccount acc(1000);
    try {
        cout << "초기 잔액: " << acc.getBalance() << "원" << endl;
        acc.deposit(500);
        cout << "입금 후 잔액: " << acc.getBalance() << "원" << endl;
        acc.withdraw(2000);  
        cout << "출금 후 잔액: " << acc.getBalance() << "원" << endl;
    }
    catch (AccountException& e) {
        e.printError();
    }

    try {
        acc.deposit(-100);
    }
    catch (AccountException& e) {
        e.printError();
    }

    return 0;
}
