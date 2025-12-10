#include "calculator.h"
#include <stdexcept>
#include <cmath>

double Calculator::add(double a, double b) {
    return a + b;
}

double Calculator::subtract(double a, double b) {
    return a - b;
}

double Calculator::multiply(double a, double b) {
    return a * b;
}

double Calculator::divide(double a, double b) {
    // 检查除数是否为 0（使用浮点数比较的安全方法）
    if (std::abs(b) < 1e-10) {
        throw std::invalid_argument("除数不能为零");
    }
    return a / b;
}
