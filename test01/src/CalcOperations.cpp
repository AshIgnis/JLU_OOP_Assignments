// calcOperation.cpp

#include "bitOperations.h"
#include "CalcOperations.h"
#include <iostream>
#include <stdbool.h>

int CalcOperations::add(int a, int b) {
    BitOperations bitOps;
    while (b != 0) {
        int sum = bitOps.bitXor(a, b);        // 无进位相加结果
        int carry = bitOps.bitLeftShift(bitOps.bitAnd(a, b), 1); // 进位值
        a = sum;
        b = carry;
    }
    return a;
}

int CalcOperations::subtract(int a, int b) {
    BitOperations bitOps;
    return add(a, add(bitOps.bitNot(b), 1)); // a + (-b)
}

int CalcOperations::multiply(int a, int b) {
    BitOperations bitOps;
    bool negative = bitOps.bitXor(a < 0, b < 0); // 确定符号
    a = a < 0 ? add(bitOps.bitNot(a), 1) : a;  
    b = b < 0 ? add(bitOps.bitNot(b), 1) : b;

    int result = 0;
    while (b != 0) {
        if (bitOps.bitAnd(b, 1))
            result = add(result, a);
        a = bitOps.bitLeftShift(a, 1);
        b = bitOps.bitRightShift(b, 1);
    }
    return negative ? add(bitOps.bitNot(result), 1) : result;
}