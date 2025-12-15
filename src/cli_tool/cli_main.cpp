#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "algorithms/sort.h"
#include "algorithms/search.h"

void printUsage() {
    std::cout << "使用方法: cli_tool <命令> [参数]" << std::endl;
    std::cout << "\n可用命令:" << std::endl;
    std::cout << "  sort <数字...>      - 对数字进行排序（使用快速排序）" << std::endl;
    std::cout << "  search <目标> <数字...> - 在已排序数组中查找目标值（使用二分查找）" << std::endl;
    std::cout << "  help                - 显示此帮助信息" << std::endl;
    std::cout << "\n示例:" << std::endl;
    std::cout << "  cli_tool sort 5 2 8 1 9" << std::endl;
    std::cout << "  cli_tool search 5 1 2 5 8 9" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "错误: 缺少命令参数" << std::endl;
        printUsage();
        return 1;
    }
    
    std::string command = argv[1];
    
    if (command == "help" || command == "--help" || command == "-h") {
        printUsage();
        return 0;
    }
    
    if (command == "sort") {
        if (argc < 3) {
            std::cerr << "错误: sort 命令需要至少一个数字参数" << std::endl;
            return 1;
        }
        
        std::vector<int> numbers;
        for (int i = 2; i < argc; i++) {
            try {
                numbers.push_back(std::stoi(argv[i]));
            } catch (const std::exception& e) {
                std::cerr << "错误: 无效的数字 '" << argv[i] << "'" << std::endl;
                return 1;
            }
        }
        
        std::cout << "原始数据: ";
        for (int num : numbers) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
        
        algorithms::quickSort(numbers);
        
        std::cout << "排序结果: ";
        for (int num : numbers) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
        
    } else if (command == "search") {
        if (argc < 4) {
            std::cerr << "错误: search 命令需要目标值和至少一个数字参数" << std::endl;
            return 1;
        }
        
        int target;
        try {
            target = std::stoi(argv[2]);
        } catch (const std::exception& e) {
            std::cerr << "错误: 无效的目标值 '" << argv[2] << "'" << std::endl;
            return 1;
        }
        
        std::vector<int> numbers;
        for (int i = 3; i < argc; i++) {
            try {
                numbers.push_back(std::stoi(argv[i]));
            } catch (const std::exception& e) {
                std::cerr << "错误: 无效的数字 '" << argv[i] << "'" << std::endl;
                return 1;
            }
        }
        
        // 检查数组是否已排序
        bool is_sorted = std::is_sorted(numbers.begin(), numbers.end());
        
        if (!is_sorted) {
            std::cout << "警告: 输入数组未排序，自动排序后再执行二分查找..." << std::endl;
            algorithms::quickSort(numbers);
        }
        
        std::cout << "搜索数组: ";
        for (int num : numbers) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
        
        int index = algorithms::binarySearch(numbers, target);
        
        if (index != -1) {
            std::cout << "找到目标值 " << target << "，索引位置: " << index << std::endl;
        } else {
            std::cout << "未找到目标值 " << target << std::endl;
        }
        
    } else {
        std::cerr << "错误: 未知命令 '" << command << "'" << std::endl;
        printUsage();
        return 1;
    }
    
    return 0;
}