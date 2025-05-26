//
// Created by rust on 2025/5/26.
//
// Demo9-10.cpp : 定义控制台应用程序的入口点。
//



#include <thread>
#include <mutex>
#include <iostream>
using namespace std;

mutex g_mutex;

//入口函数
void T1()
{
    g_mutex.lock();
    cout << "T1 Hello" << endl;
    g_mutex.unlock();
}
void T2(const char* str)
{
    g_mutex.lock();
    cout << "T2 " << str << endl;
    g_mutex.unlock();
}
int main()
{
    thread t1(T1);
    thread t2(T2, "Hello World");
    t1.join();
    //t2.join();
    t2.detach();
    cout << "Main Hi" << endl;


    return 0;
}

