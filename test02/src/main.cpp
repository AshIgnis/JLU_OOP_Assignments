#include <iostream>
#include "CString.h"

int main() {
    CString m("software");
    CString n(m), o;
    o = m;
    cout << n[4] << endl;       // 输出第4位字符
    cout << n.len() << endl;    // 输出字符串的长度
    o = m + n;                  // 合并字符串
    cout << o << endl;          // 输出合并后的字符串
    o = m(2,8);                 //截取从2位到第8位的子字符串
    cout << o << endl;          // 输出合并后的字符串
    return 0;
}