#include <iostream>
#include <string>
#include <limits>
#include "calculator.h"

/**
 * @brief 显示菜单选项
 */
void displayMenu() {
    std::cout << "\n===== 计算器演示程序 =====" << std::endl;
    std::cout << "1. 加法 (+)" << std::endl;
    std::cout << "2. 减法 (-)" << std::endl;
    std::cout << "3. 乘法 (*)" << std::endl;
    std::cout << "4. 除法 (/)" << std::endl;
    std::cout << "5. 退出" << std::endl;
    std::cout << "请选择操作 (1-5): ";
}

/**
 * @brief 获取用户输入的数字
 * @param prompt 提示信息
 * @return 用户输入的数字
 */
double getNumber(const std::string& prompt) {
    double num;
    std::cout << prompt;
    while (!(std::cin >> num)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "输入无效，请输入一个数字: ";
    }
    return num;
}

int main() {
    Calculator calc;
    int choice;
    bool running = true;

    std::cout << "欢迎使用 CMake + GitHub Actions 演示项目" << std::endl;
    std::cout << "这是一个简单的计算器应用程序" << std::endl;

    while (running) {
        displayMenu();
        std::cin >> choice;

        // 清除输入缓冲区
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice >= 1 && choice <= 4) {
            double a = getNumber("请输入第一个数字: ");
            double b = getNumber("请输入第二个数字: ");
            double result;

            try {
                switch (choice) {
                    case 1:
                        result = calc.add(a, b);
                        std::cout << "\n结果: " << a << " + " << b << " = " << result << std::endl;
                        break;
                    case 2:
                        result = calc.subtract(a, b);
                        std::cout << "\n结果: " << a << " - " << b << " = " << result << std::endl;
                        break;
                    case 3:
                        result = calc.multiply(a, b);
                        std::cout << "\n结果: " << a << " * " << b << " = " << result << std::endl;
                        break;
                    case 4:
                        result = calc.divide(a, b);
                        std::cout << "\n结果: " << a << " / " << b << " = " << result << std::endl;
                        break;
                }
            } catch (const std::invalid_argument& e) {
                std::cerr << "\n错误: " << e.what() << std::endl;
            }
        } else if (choice == 5) {
            running = false;
            std::cout << "\n感谢使用,再见!" << std::endl;
        } else {
            std::cout << "\n无效的选项,请重新选择!" << std::endl;
        }
    }

    return 0;
}
