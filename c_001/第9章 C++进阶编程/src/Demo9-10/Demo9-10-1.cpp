//
// Created by rust on 2025/5/26.
//

#include <thread>
#include <iostream>

using namespace std;


void T1() {
    cout << "T1 Hello" << endl;
}

void T2(const char* str) {
    cout << "T2 Hello " << str << endl;
}

int main() {

    thread t1(T1);

    thread  t2(T2, "World");

    t1.join();
    t2.join();

    cout << "Main Hi " << endl;

    return 0;
}