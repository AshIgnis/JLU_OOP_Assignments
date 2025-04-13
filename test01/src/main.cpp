#include <iostream>
#include "CalcOperations.h"
#include "bitOperations.h"

int main()
{
    CalcOperations calcOps;

    // 测试加法
    int addResult = calcOps.add(5, 3);
    std::cout << "5 + 3 = " << addResult << std::endl;

    // 测试减法
    int subtractResult = calcOps.subtract(10, 7);
    std::cout << "10 - 7 = " << subtractResult << std::endl;

    // 测试乘法
    int multiplyResult = calcOps.multiply(4, -6);
    std::cout << "4 * -6 = " << multiplyResult << std::endl;

    // 测试更多案例
    std::cout << "15 + (-8) = " << calcOps.add(15, -8) << std::endl;
    std::cout << "-10 - (-5) = " << calcOps.subtract(-10, -5) << std::endl;
    std::cout << "-3 * -7 = " << calcOps.multiply(-3, -7) << std::endl;

    return 0;
}
