#include <iostream>
#include <cstring>
using namespace std;

class CString {
    private:
        char* str;
        int length;
    
    public:
        // 构造函数
        CString(const char* s = "");
    
        // 拷贝构造函数
        CString(const CString& other);
    
        // 析构函数
        ~CString();
    
        // 重载赋值运算符
        CString& operator=(const CString& other);

        // 重载加法运算符：字符串拼接
        CString operator+(const CString& other) const;

        // 重载下标运算符：访问字符
        char& operator[](int index);
        
        // 获取字符串长度
        int len() const;
        
        // 截取子字符串，从 start 到 end (不包含 end)
        CString operator()(int start, int end) const;
        
        // 输出字符串
        friend ostream& operator<<(ostream& os, const CString& s);
    };