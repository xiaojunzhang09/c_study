//
// Created by rust on 2025/5/26.
//

#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

int g_money = 2000;

mutex g_m;

//存钱
void Deposit() {
    g_m.lock();
    for (int index = 0; index < 100; index++) {
        g_money += 1;
    }
    g_m.unlock();
}

//取钱
void Withdraw() {
    g_m.lock();
    for (int index = 0; index < 100; index++) {
        g_money -= 1;
    }
    g_m.unlock();
}

int main() {
    cout << "Current money is: " << g_money << endl;

    thread t1(Deposit);
    thread t2(Withdraw);
    t1.join();
    t2.join();

    cout << "Finally money is: " << g_money << endl;
}
