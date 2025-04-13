//bitoperations.cpp

#include "bitOperations.h"
#include <iostream>

int BitOperations::bitAnd(int a, int b) {
    return a & b;
}

int BitOperations::bitOr(int a, int b) {
    return a | b;
}

int BitOperations::bitXor(int a, int b) {
    return a ^ b;
}

int BitOperations::bitNot(int a) {
    return ~a;
}

int BitOperations::bitLeftShift(int a, int n) {
    return a << n;
}

int BitOperations::bitRightShift(int a, int n) {
    return a >> n;
}