#include <iostream>
using namespace std;
void print() { cout << "递归终止" << endl; }
55 template <typename T, typename... Args>
void print(T arg, Args... args) {
    cout << "我是可变参数模版，本次展开的参数是：" << arg << endl;
    print(args...);
}
template <typename T, typename... Args>
void show(T& mine, Args... args) {
    cout << "展开前我要运行，先看一个参数：" << mine << endl;
    print(args...);
    cout << "函数完成" << endl;
}

template <typename T>
int imax(T a) {
    return a;
}
template <typename T, typename... Args>
int imax(T arg, Args... args) {
    return max(arg, imax(args...));
}
int main() { cout << imax(2, 3, 1, 45, 42, 45, 34); }