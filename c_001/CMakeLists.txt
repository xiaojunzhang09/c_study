cmake_minimum_required(VERSION 3.31)
project(c_001)

set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_FLAGS -stdlib=libstdc++)

#添加的为这两行
find_package(Boost 1.88.0 REQUIRED COMPONENTS filesystem)
include_directories("/usr/local/Cellar/b    oost/1.88.0/include")

# 添加头文件搜索路径
include_directories(${PROJECT_SOURCE_DIR}/include)

# 创建静态库
add_library(Singleton STATIC
        "第8章 C++编程思想/src/demo8-1/Singleton.cpp"
)
add_library(Observerable STATIC
        "第8章 C++编程思想/src/Demo8-2/Observerable.cpp"
)

add_executable(c_001 "第4章 C++基础容器/src/demo4-4.cpp" "第4章 C++基础容器/src/demo4-5.cpp" "第4章 C++基础容器/src/demo4-4-01.cpp" "第4章 C++基础容器/src/demo4-4-02.cpp" "第4章 C++基础容器/src/demo4-6.cpp" "第5章 彻底学会 C++ 指针，引用/src/demo5-1.cpp" "第5章 彻底学会 C++ 指针，引用/src/demo5-2.cpp" "第5章 彻底学会 C++ 指针，引用/src/demo5-2-02.cpp" "第5章 彻底学会 C++ 指针，引用/src/demo5-3.cpp" "第5章 彻底学会 C++ 指针，引用/src/demo5-4.cpp" "第5章 彻底学会 C++ 指针，引用/src/demo5-5.cpp" "第5章 彻底学会 C++ 指针，引用/src/demo5-6.cpp" "第5章 彻底学会 C++ 指针，引用/src/demo5-7.cpp" "第5章 彻底学会 C++ 指针，引用/src/demo5-8.cpp" "第5章 彻底学会 C++ 指针，引用/src/demo5-9.cpp" "第5章 彻底学会 C++ 指针，引用/src/demo5-10.cpp" "第5章 彻底学会 C++ 指针，引用/src/demo5-11.cpp" "第5章 彻底学会 C++ 指针，引用/src/demo5-12.cpp" "第6章 C++基础句法/src/demo6-1.cpp" "第6章 C++基础句法/src/demo6-2.cpp" "第6章 C++基础句法/src/demo6-3.cpp" "第6章 C++基础句法/src/demo6-4.cpp" "第6章 C++基础句法/src/demo6-5.cpp" "第6章 C++基础句法/src/demo6-6.cpp" "第6章 C++基础句法/src/demo6-7.cpp" "第6章 C++基础句法/src/demo6-8.cpp" "第6章 C++基础句法/src/demo6-9.cpp" "第7章 C++高级语法/src/Complex.cpp" "第7章 C++高级语法/src/demo7-1.cpp" "第7章 C++高级语法/src/demo7-1.cpp" "第7章 C++高级语法/src2/Complex2.cpp" "第6章 C++基础句法/src/demo6-6.cpp" "第7章 C++高级语法/src3/CTimeSpan.cpp" include/Complex2.h "第7章 C++高级语法/src/demo7-2.cpp" "第7章 C++高级语法/src/demo7-3.cpp" "第7章 C++高级语法/src/demo7-4.cpp"

        "第8章 C++编程思想/src/demo8-1/demo8-1.cpp"
        "第8章 C++编程思想/src/Demo8-2/Demo8-2.cpp"
        "第8章 C++编程思想/src/Demo8-3/Demo8-3.cpp"
        "第8章 C++编程思想/src/Demo8-5/Demo8-5.cpp"
        "第8章 C++编程思想/src/Demo8-4/Demo8-4.cpp"
        "第8章 C++编程思想/src/Demo8-6/Demo8-6.cpp"
        "第8章 C++编程思想/src/Demo8-7/Demo8-7.cpp"
        "第9章 C++进阶编程/src/Demo9-1/Demo9-1.cpp"
        "第9章 C++进阶编程/src/Demo9-2/Demo9-2.cpp"
        "第9章 C++进阶编程/src/Demo9-3/Demo9-3.cpp"
        "第9章 C++进阶编程/src/Demo9-4/Demo9-4.cpp"
        "第9章 C++进阶编程/src/Demo9-5/Demo9-5.cpp"
        "第9章 C++进阶编程/src/Demo9-6/Demo9-6.cpp"
        "第9章 C++进阶编程/src/MyGC/GCPtr.h"
        "第9章 C++进阶编程/src/MyGC/MyGC.cpp"
        "第9章 C++进阶编程/src/Demo9-7/Demo9-7.cpp"
        "第9章 C++进阶编程/src/Demo9-8/jjalloc.h"
        "第9章 C++进阶编程/src/Demo9-8/Demo9-8.cpp"
        "第9章 C++进阶编程/src/Demo9-9/Demo9-9.cpp"
        "第9章 C++进阶编程/src/Demo9-10/Demo9-10.cpp"
        "第9章 C++进阶编程/src/Demo9-10/Demo9-10-1.cpp"
        "第9章 C++进阶编程/src/Demo9-11/Demo9-11.cpp"
        "第9章 C++进阶编程/src/Demo9-11/Demo9-11-1.cpp"
)

add_executable(demo4-4 "第4章 C++基础容器/src/demo4-4.cpp")
add_executable(demo4-5 "第4章 C++基础容器/src/demo4-5.cpp")
add_executable(demo4-4-01 "第4章 C++基础容器/src/demo4-4-01.cpp")
add_executable(demo4-4-02 "第4章 C++基础容器/src/demo4-4-02.cpp")
add_executable(demo4-6 "第4章 C++基础容器/src/demo4-6.cpp")
add_executable(demo5-1 "第5章 彻底学会 C++ 指针，引用/src/demo5-1.cpp")
add_executable(demo5-2 "第5章 彻底学会 C++ 指针，引用/src/demo5-2.cpp")
add_executable(demo5-2-02 "第5章 彻底学会 C++ 指针，引用/src/demo5-2-02.cpp")
add_executable(demo5-3 "第5章 彻底学会 C++ 指针，引用/src/demo5-3.cpp")
add_executable(demo5-4 "第5章 彻底学会 C++ 指针，引用/src/demo5-4.cpp")
add_executable(demo5-8 "第5章 彻底学会 C++ 指针，引用/src/demo5-8.cpp")
add_executable(demo5-12 "第5章 彻底学会 C++ 指针，引用/src/demo5-12.cpp")
add_executable(demo6-3 "第6章 C++基础句法/src/demo6-3.cpp")
add_executable(demo6-7 "第6章 C++基础句法/src/demo6-7.cpp")
add_executable(demo7-1 "第7章 C++高级语法/src/demo7-1.cpp")
add_executable(Complex "第7章 C++高级语法/src/Complex.cpp")

add_executable(Complex2 "第7章 C++高级语法/src2/Complex2.cpp")
add_executable(CTimeSpan "第7章 C++高级语法/src3/CTimeSpan.cpp")
add_executable(demo7-2 "第7章 C++高级语法/src/demo7-2.cpp")
add_executable(demo7-4 "第7章 C++高级语法/src/demo7-4.cpp")
add_executable(demo8-1 "第8章 C++编程思想/src/demo8-1/demo8-1.cpp")
add_executable(Demo8-2 "第8章 C++编程思想/src/Demo8-2/Demo8-2.cpp")

# ✅ 链接 Singleton 库
target_link_libraries(demo8-1 PRIVATE Singleton)
target_link_libraries(Demo8-2 PRIVATE Observerable)


add_executable(Demo8-3 "第8章 C++编程思想/src/Demo8-3/Demo8-3.cpp")
add_executable(Demo8-4 "第8章 C++编程思想/src/Demo8-4/Demo8-4.cpp")
add_executable(Demo8-5 "第8章 C++编程思想/src/Demo8-5/Demo8-5.cpp")
add_executable(Demo8-6 "第8章 C++编程思想/src/Demo8-6/Demo8-6.cpp")
add_executable(Demo8-7 "第8章 C++编程思想/src/Demo8-7/Demo8-7.cpp")
add_executable(Demo9-1 "第9章 C++进阶编程/src/Demo9-1/Demo9-1.cpp")
add_executable(Demo9-2 "第9章 C++进阶编程/src/Demo9-2/Demo9-2.cpp")
add_executable(Demo9-3 "第9章 C++进阶编程/src/Demo9-3/Demo9-3.cpp")
add_executable(Demo9-4 "第9章 C++进阶编程/src/Demo9-4/Demo9-4.cpp")
add_executable(Demo9-5 "第9章 C++进阶编程/src/Demo9-5/Demo9-5.cpp")
add_executable(Demo9-6 "第9章 C++进阶编程/src/Demo9-6/Demo9-6.cpp")
add_executable(Demo9-7 "第9章 C++进阶编程/src/Demo9-7/Demo9-7.cpp")
add_executable(Demo9-9 "第9章 C++进阶编程/src/Demo9-9/Demo9-9.cpp")
add_executable(Demo9-10-1 "第9章 C++进阶编程/src/Demo9-10/Demo9-10-1.cpp")
add_executable(Demo9-10 "第9章 C++进阶编程/src/Demo9-10/Demo9-10.cpp")
add_executable(Demo9-11-1 "第9章 C++进阶编程/src/Demo9-11/Demo9-11-1.cpp")
add_executable(Demo9-11 "第9章 C++进阶编程/src/Demo9-11/Demo9-11.cpp")