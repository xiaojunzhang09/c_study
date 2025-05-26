//
// Created by rust on 2025/5/26.
//
// Demo9-9.cpp : 定义控制台应用程序的入口点。
//



#include <boost/lexical_cast.hpp>
#include <iostream>
using namespace std;
using boost::lexical_cast;


int main()
{
    int i = lexical_cast<int>("123");
    cout << i << endl;

    string s = lexical_cast<string>(1.23);
    cout << s << endl;

    int ii;
    try
    {
        ii = lexical_cast<int>("abcd");
    }
    catch (boost::bad_lexical_cast& e)
    {
        cout << e.what() << endl;
    }

    return 0;
}

