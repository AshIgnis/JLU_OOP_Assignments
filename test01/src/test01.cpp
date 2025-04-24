// #include <iostream>
// #include "CalcOperations.h"
// #include "bitOperations.h"

// int main()
// {

//      // 测试位运算
//      BitOperations bitOps;

//      // 按位与
//      int andResult = bitOps.bitAnd(5, 3);
//      std::cout << "5 & 3 = " << andResult << std::endl;
 
//      // 按位或
//      int orResult = bitOps.bitOr(5, 3);
//      std::cout << "5 | 3 = " << orResult << std::endl;
 
//      // 按位异或
//      int xorResult = bitOps.bitXor(5, 3);
//      std::cout << "5 ^ 3 = " << xorResult << std::endl;
 
//      // 按位取反
//      int notResult = bitOps.bitNot(5);
//      std::cout << "~5 = " << notResult << std::endl;
 
//      // 左移位
//      int leftShiftResult = bitOps.bitLeftShift(5, 2);
//      std::cout << "5 << 2 = " << leftShiftResult << std::endl;
 
//      // 右移位
//      int rightShiftResult = bitOps.bitRightShift(20, 2);
//      std::cout << "20 >> 2 = " << rightShiftResult << std::endl; 

//     //测试十进制
//     CalcOperations calcOps;

//     // 测试加法
//     int addResult = calcOps.add(5, 3);
//     std::cout << "5 + 3 = " << addResult << std::endl;

//     // 测试减法
//     int subtractResult = calcOps.subtract(10, 7);
//     std::cout << "10 - 7 = " << subtractResult << std::endl;

//     // 测试乘法
//     int multiplyResult = calcOps.multiply(4, -6);
//     std::cout << "4 * -6 = " << multiplyResult << std::endl;

//     // 测试更多案例
//     std::cout << "15 + (-8) = " << calcOps.add(15, -8) << std::endl;
//     std::cout << "-10 - (-5) = " << calcOps.subtract(-10, -5) << std::endl;
//     std::cout << "-3 * -7 = " << calcOps.multiply(-3, -7) << std::endl;

//     system("pause");

//     return 0;
// }


#include <iostream>
#include <vector>
#include "sumOfDigits.h"

int main() {
    int number = 12345;
    std::cout << "数字 " << number << " 的各位数之和为: " << sumOfDigits(number) << std::endl;

    number = -9876;
    std::cout << "数字 " << number << " 的各位数之和为： " << sumOfDigits(number) << std::endl;

// 计算1000!
    int n = 1000; 
    std::vector<int> result = factorial(n);
    int sum = 0;
    for (int digit : result) {
        sum += sumOfDigits(digit);
    }

    std::cout << "1000！的各位数之和为： " << sum << std::endl;

    return 0;
}