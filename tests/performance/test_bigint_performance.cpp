#include <gtest/gtest.h>
#include <chrono>
#include <vector>
#include <string>
extern "C" {
    #include "bigint.h"
}

class BigIntPerformanceTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code for performance tests
    }

    void TearDown() override {
        // Cleanup code for performance tests
    }

    // Helper function to measure execution time
    template<typename Func>
    double MeasureExecutionTime(Func func) {
        auto start = std::chrono::high_resolution_clock::now();
        func();
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        return duration.count() / 1000.0; // Return milliseconds
    }

    // Generate a large number string
    std::string GenerateLargeNumber(int digits) {
        std::string result;
        result.reserve(digits);
        for (int i = 0; i < digits; i++) {
            result += (i == 0) ? '1' + (rand() % 9) : '0' + (rand() % 10);
        }
        return result;
    }
};

// Test creation performance with various sizes
TEST_F(BigIntPerformanceTest, CreationPerformance) {
    std::vector<int> sizes = {10, 50, 100, 500, 1000, 5000};

    for (int size : sizes) {
        std::string large_num = GenerateLargeNumber(size);

        double time = MeasureExecutionTime([&]() {
            BigInt* num = bigint_create(const_cast<char*>(large_num.c_str()));
            bigint_free(num);
        });

        std::cout << "Creation time for " << size << " digits: " << time << " ms" << std::endl;

        // Performance should be reasonable even for large numbers
        EXPECT_LT(time, 1000.0); // Should take less than 1 second
    }
}

// Test addition performance
TEST_F(BigIntPerformanceTest, AdditionPerformance) {
    std::vector<int> sizes = {100, 500, 1000, 2000};

    for (int size : sizes) {
        std::string num1_str = GenerateLargeNumber(size);
        std::string num2_str = GenerateLargeNumber(size);

        BigInt* num1 = bigint_create(const_cast<char*>(num1_str.c_str()));
        BigInt* num2 = bigint_create(const_cast<char*>(num2_str.c_str()));

        double time = MeasureExecutionTime([&]() {
            BigInt* result = bigint_add(num1, num2);
            bigint_free(result);
        });

        std::cout << "Addition time for " << size << " digits: " << time << " ms" << std::endl;

        bigint_free(num1);
        bigint_free(num2);

        // Addition should be linear in complexity
        EXPECT_LT(time, size * 0.1); // Reasonable upper bound
    }
}

// Test multiplication performance
TEST_F(BigIntPerformanceTest, MultiplicationPerformance) {
    std::vector<int> sizes = {50, 100, 200, 400};

    for (int size : sizes) {
        std::string num1_str = GenerateLargeNumber(size);
        std::string num2_str = GenerateLargeNumber(size);

        BigInt* num1 = bigint_create(const_cast<char*>(num1_str.c_str()));
        BigInt* num2 = bigint_create(const_cast<char*>(num2_str.c_str()));

        double time = MeasureExecutionTime([&]() {
            BigInt* result = bigint_multiply(num1, num2);
            bigint_free(result);
        });

        std::cout << "Multiplication time for " << size << " digits: " << time << " ms" << std::endl;

        bigint_free(num1);
        bigint_free(num2);

        // Multiplication is typically O(n²) for basic algorithms
        EXPECT_LT(time, 5000.0); // Should complete within reasonable time
    }
}

// Test division performance
TEST_F(BigIntPerformanceTest, DivisionPerformance) {
    std::vector<int> sizes = {50, 100, 200, 400};

    for (int size : sizes) {
        std::string dividend_str = GenerateLargeNumber(size * 2);
        std::string divisor_str = GenerateLargeNumber(size);

        BigInt* dividend = bigint_create(const_cast<char*>(dividend_str.c_str()));
        BigInt* divisor = bigint_create(const_cast<char*>(divisor_str.c_str()));

        double time = MeasureExecutionTime([&]() {
            BigInt* result = bigint_divide(dividend, divisor);
            bigint_free(result);
        });

        std::cout << "Division time for " << size << " digit divisor: " << time << " ms" << std::endl;

        bigint_free(dividend);
        bigint_free(divisor);

        // Division is typically the most expensive operation
        EXPECT_LT(time, 10000.0); // Should complete within reasonable time
    }
}

// Test repeated operations performance
TEST_F(BigIntPerformanceTest, RepeatedOperationsPerformance) {
    const int NUM_OPERATIONS = 1000;

    BigInt* base = bigint_create("123456789");
    BigInt* increment = bigint_create("1");

    double time = MeasureExecutionTime([&]() {
        BigInt* current = bigint_create("123456789");

        for (int i = 0; i < NUM_OPERATIONS; i++) {
            BigInt* new_val = bigint_add(current, increment);
            bigint_free(current);
            current = new_val;
        }

        bigint_free(current);
    });

    std::cout << "Time for " << NUM_OPERATIONS << " additions: " << time << " ms" << std::endl;
    std::cout << "Average time per addition: " << time / NUM_OPERATIONS << " ms" << std::endl;

    bigint_free(base);
    bigint_free(increment);

    // Should be able to perform many small operations quickly
    EXPECT_LT(time / NUM_OPERATIONS, 1.0); // Less than 1ms per operation on average
}

// Test memory allocation performance
TEST_F(BigIntPerformanceTest, MemoryAllocationPerformance) {
    const int NUM_ALLOCATIONS = 10000;

    double time = MeasureExecutionTime([&]() {
        std::vector<BigInt*> numbers;
        numbers.reserve(NUM_ALLOCATIONS);

        // Allocate many BigInts
        for (int i = 0; i < NUM_ALLOCATIONS; i++) {
            BigInt* num = bigint_create("123456789");
            numbers.push_back(num);
        }

        // Free all BigInts
        for (BigInt* num : numbers) {
            bigint_free(num);
        }
    });

    std::cout << "Time for " << NUM_ALLOCATIONS << " allocations/deallocations: " << time << " ms" << std::endl;
    std::cout << "Average time per allocation: " << time / NUM_ALLOCATIONS << " ms" << std::endl;

    // Memory operations should be fast
    EXPECT_LT(time / NUM_ALLOCATIONS, 0.1); // Less than 0.1ms per allocation on average
}

// Test string conversion performance
TEST_F(BigIntPerformanceTest, StringConversionPerformance) {
    std::vector<int> sizes = {100, 500, 1000, 5000};

    for (int size : sizes) {
        std::string large_num = GenerateLargeNumber(size);
        BigInt* num = bigint_create(const_cast<char*>(large_num.c_str()));

        double time = MeasureExecutionTime([&]() {
            char* str = bigint_to_string(num);
            free(str);
        });

        std::cout << "String conversion time for " << size << " digits: " << time << " ms" << std::endl;

        bigint_free(num);

        // String conversion should be linear
        EXPECT_LT(time, size * 0.01); // Reasonable upper bound
    }
}

// Test comparison performance
TEST_F(BigIntPerformanceTest, ComparisonPerformance) {
    std::vector<int> sizes = {100, 500, 1000, 5000};

    for (int size : sizes) {
        std::string num1_str = GenerateLargeNumber(size);
        std::string num2_str = GenerateLargeNumber(size);

        BigInt* num1 = bigint_create(const_cast<char*>(num1_str.c_str()));
        BigInt* num2 = bigint_create(const_cast<char*>(num2_str.c_str()));

        const int NUM_COMPARISONS = 10000;

        double time = MeasureExecutionTime([&]() {
            for (int i = 0; i < NUM_COMPARISONS; i++) {
                bigint_compare(num1, num2);
            }
        });

        std::cout << "Time for " << NUM_COMPARISONS << " comparisons of " << size << " digits: " << time << " ms" << std::endl;

        bigint_free(num1);
        bigint_free(num2);

        // Comparisons should be fast
        EXPECT_LT(time / NUM_COMPARISONS, 0.01); // Less than 0.01ms per comparison
    }
}

// Benchmark test for realistic usage patterns
TEST_F(BigIntPerformanceTest, RealisticUsageBenchmark) {
    // Simulate a realistic computation: factorial calculation
    const int FACTORIAL_N = 100;

    double time = MeasureExecutionTime([&]() {
        BigInt* result = bigint_create("1");

        for (int i = 2; i <= FACTORIAL_N; i++) {
            char i_str[20];
            sprintf(i_str, "%d", i);
            BigInt* i_big = bigint_create(i_str);

            BigInt* new_result = bigint_multiply(result, i_big);
            bigint_free(result);
            bigint_free(i_big);
            result = new_result;
        }

        // Verify we got a reasonable result (factorial(100) is very large)
        char* result_str = bigint_to_string(result);
        EXPECT_GT(strlen(result_str), 150); // 100! has more than 150 digits

        free(result_str);
        bigint_free(result);
    });

    std::cout << "Time to calculate " << FACTORIAL_N << "!: " << time << " ms" << std::endl;

    // Should be able to calculate factorial reasonably quickly
    EXPECT_LT(time, 10000.0); // Less than 10 seconds
}
