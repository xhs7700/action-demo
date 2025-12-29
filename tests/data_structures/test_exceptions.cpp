#include <gtest/gtest.h>
#include "data_structures/exceptions.h"
#include <string>

using namespace data_structures;

// 测试基类异常 DataStructureException
TEST(ExceptionsTest, DataStructureExceptionBasic) {
    DataStructureException ex("Test error message", "TestContainer");
    
    std::string whatStr = ex.what();
    EXPECT_NE(whatStr.find("Test error message"), std::string::npos);
    EXPECT_NE(whatStr.find("TestContainer"), std::string::npos);
    EXPECT_EQ(ex.getStructureName(), "TestContainer");
}

TEST(ExceptionsTest, DataStructureExceptionWithoutContainerName) {
    DataStructureException ex("Simple error");
    
    std::string whatStr = ex.what();
    EXPECT_NE(whatStr.find("Simple error"), std::string::npos);
    EXPECT_EQ(ex.getStructureName(), "");
}

// 测试空容器异常 EmptyContainerException
TEST(ExceptionsTest, EmptyContainerExceptionBasic) {
    EmptyContainerException ex("Stack", "pop");
    
    std::string whatStr = ex.what();
    EXPECT_NE(whatStr.find("Stack"), std::string::npos);
    EXPECT_NE(whatStr.find("pop"), std::string::npos);
    EXPECT_NE(whatStr.find("empty"), std::string::npos);
    
    EXPECT_EQ(ex.getOperationName(), "pop");
    EXPECT_EQ(ex.getStructureName(), "Stack");
}

TEST(ExceptionsTest, EmptyContainerExceptionQueue) {
    EmptyContainerException ex("Queue", "dequeue");
    
    std::string whatStr = ex.what();
    EXPECT_NE(whatStr.find("Queue"), std::string::npos);
    EXPECT_NE(whatStr.find("dequeue"), std::string::npos);
    EXPECT_EQ(ex.getOperationName(), "dequeue");
}

// 测试索引越界异常 OutOfRangeException
TEST(ExceptionsTest, OutOfRangeExceptionBasic) {
    OutOfRangeException ex("LinkedList", 10, 5);
    
    std::string whatStr = ex.what();
    EXPECT_NE(whatStr.find("LinkedList"), std::string::npos);
    EXPECT_NE(whatStr.find("10"), std::string::npos);
    EXPECT_NE(whatStr.find("5"), std::string::npos);
    
    EXPECT_EQ(ex.getIndex(), 10);
    EXPECT_EQ(ex.getValidSize(), 5);
    EXPECT_EQ(ex.getStructureName(), "LinkedList");
}

TEST(ExceptionsTest, OutOfRangeExceptionZeroSize) {
    OutOfRangeException ex("Vector", 0, 0);
    
    std::string whatStr = ex.what();
    EXPECT_NE(whatStr.find("0"), std::string::npos);
    EXPECT_EQ(ex.getIndex(), 0);
    EXPECT_EQ(ex.getValidSize(), 0);
}

// 测试非法操作异常 InvalidOperationException
TEST(ExceptionsTest, InvalidOperationExceptionWithConstraint) {
    InvalidOperationException ex(
        "BTree", 
        "Cannot split node", 
        "Node must have more than minimum keys"
    );
    
    std::string whatStr = ex.what();
    EXPECT_NE(whatStr.find("BTree"), std::string::npos);
    EXPECT_NE(whatStr.find("Cannot split node"), std::string::npos);
    EXPECT_NE(whatStr.find("Constraint"), std::string::npos);
    EXPECT_NE(whatStr.find("minimum keys"), std::string::npos);
    
    EXPECT_EQ(ex.getConstraintDescription(), "Node must have more than minimum keys");
}

TEST(ExceptionsTest, InvalidOperationExceptionWithoutConstraint) {
    InvalidOperationException ex("Graph", "Invalid operation on disconnected graph");
    
    std::string whatStr = ex.what();
    EXPECT_NE(whatStr.find("Graph"), std::string::npos);
    EXPECT_NE(whatStr.find("Invalid operation"), std::string::npos);
    EXPECT_EQ(whatStr.find("Constraint"), std::string::npos);
    
    EXPECT_EQ(ex.getConstraintDescription(), "");
}

// 测试内存分配异常 AllocationException
TEST(ExceptionsTest, AllocationExceptionBytes) {
    AllocationException ex("HashMap", 1024, "bytes");
    
    std::string whatStr = ex.what();
    EXPECT_NE(whatStr.find("HashMap"), std::string::npos);
    EXPECT_NE(whatStr.find("1024"), std::string::npos);
    EXPECT_NE(whatStr.find("bytes"), std::string::npos);
    EXPECT_NE(whatStr.find("allocate"), std::string::npos);
    
    EXPECT_EQ(ex.getRequestedSize(), 1024);
}

TEST(ExceptionsTest, AllocationExceptionElements) {
    AllocationException ex("Vector", 100, "elements");
    
    std::string whatStr = ex.what();
    EXPECT_NE(whatStr.find("Vector"), std::string::npos);
    EXPECT_NE(whatStr.find("100"), std::string::npos);
    EXPECT_NE(whatStr.find("elements"), std::string::npos);
    
    EXPECT_EQ(ex.getRequestedSize(), 100);
}

TEST(ExceptionsTest, AllocationExceptionDefaultUnit) {
    AllocationException ex("Buffer", 512);
    
    std::string whatStr = ex.what();
    EXPECT_NE(whatStr.find("512"), std::string::npos);
    EXPECT_NE(whatStr.find("bytes"), std::string::npos);
}

// 测试异常继承关系
TEST(ExceptionsTest, InheritanceFromStdException) {
    EmptyContainerException ex("Stack", "pop");
    
    // 可以作为std::exception捕获
    try {
        throw ex;
    } catch (const std::exception& e) {
        EXPECT_NE(std::string(e.what()).find("Stack"), std::string::npos);
    } catch (...) {
        FAIL() << "Exception should be catchable as std::exception";
    }
}

TEST(ExceptionsTest, InheritanceFromDataStructureException) {
    OutOfRangeException ex("List", 5, 3);
    
    // 可以作为DataStructureException捕获
    try {
        throw ex;
    } catch (const DataStructureException& e) {
        EXPECT_EQ(e.getStructureName(), "List");
    } catch (...) {
        FAIL() << "Exception should be catchable as DataStructureException";
    }
}

// 测试异常的noexcept保证
TEST(ExceptionsTest, WhatIsNoexcept) {
    EmptyContainerException ex("Stack", "top");
    
    // what()应该是noexcept
    EXPECT_TRUE(noexcept(ex.what()));
}

TEST(ExceptionsTest, GettersAreNoexcept) {
    OutOfRangeException ex("Vector", 10, 5);
    
    // Getter方法应该是noexcept
    EXPECT_TRUE(noexcept(ex.getIndex()));
    EXPECT_TRUE(noexcept(ex.getValidSize()));
    EXPECT_TRUE(noexcept(ex.getStructureName()));
}

// 测试实际使用场景
TEST(ExceptionsTest, RealWorldScenarioEmptyStack) {
    auto simulateEmptyStackPop = []() {
        // 模拟对空栈执行pop操作
        throw EmptyContainerException("Stack<int>", "pop");
    };
    
    EXPECT_THROW(simulateEmptyStackPop(), EmptyContainerException);
    EXPECT_THROW(simulateEmptyStackPop(), DataStructureException);
    EXPECT_THROW(simulateEmptyStackPop(), std::exception);
}

TEST(ExceptionsTest, RealWorldScenarioIndexOutOfBounds) {
    auto simulateIndexAccess = [](size_t index) {
        size_t size = 10;
        if (index >= size) {
            throw OutOfRangeException("LinkedList<int>", index, size);
        }
    };
    
    EXPECT_NO_THROW(simulateIndexAccess(5));
    EXPECT_THROW(simulateIndexAccess(10), OutOfRangeException);
    EXPECT_THROW(simulateIndexAccess(15), OutOfRangeException);
}
