// sumOfDigits.cpp

#include <iostream>
#include <string>
#include <vector>
#include "sumOfDigits.h"

int sumOfDigits(int number) {
    int sum = 0;
    number = std::abs(number); // 确保处理正数
    while (number > 0) {
        sum += number % 10; // 提取最后一位数字并累加
        number /= 10;       // 去掉最后一位数字
    }
    return sum;
}

std::vector<int> factorial(int n) {
    std::vector<int> result(1, 1);
    for (int i = 2; i <= n; ++i) {
        int carry = 0;
        for (auto& digit : result) {
            int product = digit * i + carry;
            digit = product % 10;
            carry = product / 10;
        }
        while (carry) {
            result.push_back(carry % 10);
            carry /= 10;
        }
    }
    return result;
}