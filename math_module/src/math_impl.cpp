// src/math/math_impl.cpp
module;

#include <iostream>

module math;

int helper_log(int value) {
    std::cout << "Calculating: " << value << '\n';

    return value;
}

int Calculator::multiply(int a, int b) {
    helper_log(a * b);
    return a * b;
}
