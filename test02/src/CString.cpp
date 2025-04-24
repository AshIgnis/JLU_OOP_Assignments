#include "CString.h"
//构造函数
CString::CString(const char* s) {
    length = strlen(s);
    str = new char[length + 1];
    strcpy(str, s);
}
//拷贝构造
CString::CString(const CString& other) {
    length = other.length;
    str = new char[length + 1];
    strcpy(str, other.str);
}
//析构
CString::~CString() {
    delete[] str;
}
//重载=
CString& CString::operator=(const CString& other) {
    if (this != &other) {
        delete[] str;
        length = other.length;
        str = new char[length + 1];
        strcpy(str, other.str);
    }
    return *this;
}
//重载<<
ostream& operator<<(ostream& os, const CString& s) { 
    os << s.str;
    return os;
}
//重载+
CString CString::operator+(const CString& other) const {
    CString result;
    result.length = length + other.length;
    result.str = new char[result.length + 1];
    strcpy(result.str, str);
    strcat(result.str, other.str);
    return result;
}
//重载[]
char& CString::operator[](int index) { 
    return str[index];
}
//获取长度
int CString::len() const { 
    return length;
}
//重载()
CString CString::operator()(int start, int end) const {    
    int sLength = end - start;
    char* sStr = new char[sLength + 1];
    
    for (int i = 0; i < sLength; i++) {
        sStr[i] = str[start + i];
    }
    sStr[sLength] = '\0';
    
    CString result(sStr);
    delete[] sStr;
    return result;
}
