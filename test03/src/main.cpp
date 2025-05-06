#include <iostream>
using namespace std;

class Male; // 前向声明

class Female {
public:
    Male* getHusband(); // 获取丈夫
};

class Male {
private:
    Female* pWife = nullptr; // 指向妻子的指针
public:
    Male() { m_buffer[m_sum++] = this; } 
    void setWife(Female* wife) { 
        pWife = wife;
    } 
    void deleteWife() { 
        pWife = nullptr; cout << "Successful divorce" << endl;
    } // 删除妻子
    Female* getWife() { 
        return pWife; 
    } // 获取妻子

    static Male* m_buffer[100]; // 存储所有 Male 对象的静态数组
    static int m_sum; // 当前 Male 对象的数量
};

Male* Male::m_buffer[100];
int Male::m_sum = 0;

Male* Female::getHusband() {
    for (int i = 0; i < Male::m_sum; i++) {
        if (Male::m_buffer[i]->getWife() == this) {
            return Male::m_buffer[i];
        }
    }
    return nullptr; 
}

void output1(Male* husbandOfx,char x,Male& husband,char y){
    if (husbandOfx == nullptr) {
        printf("%c has no husband.\n",x);
    } else {
        printf("%c has husband.\n",x);
    }
    if (husbandOfx == &husband) {
        printf("%c's husband is %c.\n",x,y);
    } else {
        printf("%c's husband is not %c.\n",x,y);
    }
}

void output2(Female* wifeOfx,char x,Female& wife,char y){
    if (wifeOfx == nullptr) {
        printf("%c has no wife.\n",x);
    } else {
        printf("%c has wife.\n",x);
    }
    if (wifeOfx == &wife) {
        printf("%c's wife is %c.\n",x,y);
    } else {
        printf("%c's wife is not %c.\n",x,y);
    }
}

int main() {
    Male a, b, x, y;
    Female c, d, e;

    // 设置配偶关系
    a.setWife(&c); 
    b.setWife(&d); 

    // 输出初始配偶关系
    Male* husbandOfd = d.getHusband();
    output1(husbandOfd, 'd', b, 'b');

    Female* wifeofX = x.getWife();
    output2(wifeofX, 'x', d, 'd');

    Female* wifeofb = b.getWife();
    output2(wifeofb, 'b', d, 'd');

    // 测试离婚操作
    b.deleteWife();
    husbandOfd = d.getHusband();
    output1(husbandOfd, 'd', b, 'b');

    // 测试重新结婚操作
    x.setWife(&d); 
    husbandOfd = d.getHusband(); 
    output1(husbandOfd, 'd', x, 'x'); 

    // 测试多次婚姻操作
    y.setWife(&e); 
    Female* wifeofy = y.getWife();
    output2(wifeofy, 'y', e, 'e');

    y.deleteWife(); 
    wifeofy = y.getWife();
    output2(wifeofy, 'y', e, 'e');

    a.setWife(&e); 
    Female* wifeofa = a.getWife();
    output2(wifeofa, 'a', e, 'e');

    // 测试未婚男性和女性的状态
    Male* husbandOfc = c.getHusband();
    output1(husbandOfc, 'c', a, 'a');

    system("pause");
    return 0;
}