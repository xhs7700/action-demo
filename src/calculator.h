#ifndef CALCULATOR_H
#define CALCULATOR_H

/**
 * @brief 简单的计算器类，提供基本的算术运算功能
 * 
 * 该类实现了加法、减法、乘法和除法四种基本运算。
 * 所有运算都使用双精度浮点数类型。
 */
class Calculator {
public:
    /**
     * @brief 加法运算
     * @param a 第一个操作数
     * @param b 第二个操作数
     * @return 两数之和
     */
    double add(double a, double b);

    /**
     * @brief 减法运算
     * @param a 被减数
     * @param b 减数
     * @return 两数之差
     */
    double subtract(double a, double b);

    /**
     * @brief 乘法运算
     * @param a 第一个操作数
     * @param b 第二个操作数
     * @return 两数之积
     */
    double multiply(double a, double b);

    /**
     * @brief 除法运算
     * @param a 被除数
     * @param b 除数
     * @return 两数之商
     * @throw std::invalid_argument 当除数为 0 时抛出异常
     */
    double divide(double a, double b);
};

#endif // CALCULATOR_H
