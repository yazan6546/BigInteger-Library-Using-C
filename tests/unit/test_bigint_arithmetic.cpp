#include <gtest/gtest.h>
extern "C" {
    #include "bigint.h"
}

class BigIntArithmeticTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code for each test
    }

    void TearDown() override {
        // Cleanup code for each test
    }
};

// Addition Tests
TEST_F(BigIntArithmeticTest, AddPositiveNumbers) {
    BigInt* a = bigint_create("123");
    BigInt* b = bigint_create("456");
    BigInt* result = bigint_add(a, b);

    char* result_str = bigint_to_string(result);
    EXPECT_STREQ(result_str, "579");

    free(result_str);
    bigint_free(a);
    bigint_free(b);
    bigint_free(result);
}

TEST_F(BigIntArithmeticTest, AddNegativeNumbers) {
    BigInt* a = bigint_create("-123");
    BigInt* b = bigint_create("-456");
    BigInt* result = bigint_add(a, b);

    char* result_str = bigint_to_string(result);
    EXPECT_STREQ(result_str, "-579");

    free(result_str);
    bigint_free(a);
    bigint_free(b);
    bigint_free(result);
}

TEST_F(BigIntArithmeticTest, AddMixedSigns) {
    BigInt* a = bigint_create("456");
    BigInt* b = bigint_create("-123");
    BigInt* result = bigint_add(a, b);

    char* result_str = bigint_to_string(result);
    EXPECT_STREQ(result_str, "333");

    free(result_str);
    bigint_free(a);
    bigint_free(b);
    bigint_free(result);
}

TEST_F(BigIntArithmeticTest, AddWithZero) {
    BigInt* a = bigint_create("123");
    BigInt* zero = bigint_create("0");
    BigInt* result = bigint_add(a, zero);

    char* result_str = bigint_to_string(result);
    EXPECT_STREQ(result_str, "123");

    free(result_str);
    bigint_free(a);
    bigint_free(zero);
    bigint_free(result);
}

TEST_F(BigIntArithmeticTest, AddLargeNumbers) {
    BigInt* a = bigint_create("999999999999999999999");
    BigInt* b = bigint_create("1");
    BigInt* result = bigint_add(a, b);

    char* result_str = bigint_to_string(result);
    EXPECT_STREQ(result_str, "1000000000000000000000");

    free(result_str);
    bigint_free(a);
    bigint_free(b);
    bigint_free(result);
}

// Subtraction Tests
TEST_F(BigIntArithmeticTest, SubtractPositiveNumbers) {
    BigInt* a = bigint_create("456");
    BigInt* b = bigint_create("123");
    BigInt* result = bigint_subtract(a, b);

    char* result_str = bigint_to_string(result);
    EXPECT_STREQ(result_str, "333");

    free(result_str);
    bigint_free(a);
    bigint_free(b);
    bigint_free(result);
}

TEST_F(BigIntArithmeticTest, SubtractResultingInNegative) {
    BigInt* a = bigint_create("123");
    BigInt* b = bigint_create("456");
    BigInt* result = bigint_subtract(a, b);

    char* result_str = bigint_to_string(result);
    EXPECT_STREQ(result_str, "-333");

    free(result_str);
    bigint_free(a);
    bigint_free(b);
    bigint_free(result);
}

TEST_F(BigIntArithmeticTest, SubtractFromZero) {
    BigInt* zero = bigint_create("0");
    BigInt* b = bigint_create("123");
    BigInt* result = bigint_subtract(zero, b);

    char* result_str = bigint_to_string(result);
    EXPECT_STREQ(result_str, "-123");

    free(result_str);
    bigint_free(zero);
    bigint_free(b);
    bigint_free(result);
}

TEST_F(BigIntArithmeticTest, SubtractSameNumbers) {
    BigInt* a = bigint_create("123");
    BigInt* b = bigint_create("123");
    BigInt* result = bigint_subtract(a, b);

    char* result_str = bigint_to_string(result);
    EXPECT_STREQ(result_str, "0");

    free(result_str);
    bigint_free(a);
    bigint_free(b);
    bigint_free(result);
}

// Multiplication Tests
TEST_F(BigIntArithmeticTest, MultiplyPositiveNumbers) {
    BigInt* a = bigint_create("123");
    BigInt* b = bigint_create("456");
    BigInt* result = bigint_multiply(a, b);

    char* result_str = bigint_to_string(result);
    EXPECT_STREQ(result_str, "56088");

    free(result_str);
    bigint_free(a);
    bigint_free(b);
    bigint_free(result);
}

TEST_F(BigIntArithmeticTest, MultiplyByZero) {
    BigInt* a = bigint_create("123");
    BigInt* zero = bigint_create("0");
    BigInt* result = bigint_multiply(a, zero);

    char* result_str = bigint_to_string(result);
    EXPECT_STREQ(result_str, "0");

    free(result_str);
    bigint_free(a);
    bigint_free(zero);
    bigint_free(result);
}

TEST_F(BigIntArithmeticTest, MultiplyByOne) {
    BigInt* a = bigint_create("123");
    BigInt* one = bigint_create("1");
    BigInt* result = bigint_multiply(a, one);

    char* result_str = bigint_to_string(result);
    EXPECT_STREQ(result_str, "123");

    free(result_str);
    bigint_free(a);
    bigint_free(one);
    bigint_free(result);
}

TEST_F(BigIntArithmeticTest, MultiplyNegativeNumbers) {
    BigInt* a = bigint_create("-123");
    BigInt* b = bigint_create("-456");
    BigInt* result = bigint_multiply(a, b);

    char* result_str = bigint_to_string(result);
    EXPECT_STREQ(result_str, "56088");

    free(result_str);
    bigint_free(a);
    bigint_free(b);
    bigint_free(result);
}

TEST_F(BigIntArithmeticTest, MultiplyMixedSigns) {
    BigInt* a = bigint_create("123");
    BigInt* b = bigint_create("-456");
    BigInt* result = bigint_multiply(a, b);

    char* result_str = bigint_to_string(result);
    EXPECT_STREQ(result_str, "-56088");

    free(result_str);
    bigint_free(a);
    bigint_free(b);
    bigint_free(result);
}

// Division Tests
TEST_F(BigIntArithmeticTest, DividePositiveNumbers) {
    BigInt* a = bigint_create("456");
    BigInt* b = bigint_create("123");
    BigInt* result = bigint_divide(a, b);
    bigint_print(result, stdout);


    char* result_str = bigint_to_string(result);
    EXPECT_STREQ(result_str, "1");

    free(result_str);
    bigint_free(a);
    bigint_free(b);
    bigint_free(result);
}

TEST_F(BigIntArithmeticTest, DivideByOne) {
    BigInt* a = bigint_create("123");
    BigInt* one = bigint_create("1");
    BigInt* result = bigint_divide(a, one);

    bigint_print(result, stdout);

    char* result_str = bigint_to_string(result);
    EXPECT_STREQ(result_str, "123");

    free(result_str);
    bigint_free(a);
    bigint_free(one);
    bigint_free(result);
}

TEST_F(BigIntArithmeticTest, DivideByZero) {
    BigInt* a = bigint_create("123");
    BigInt* zero = bigint_create("0");
    BigInt* result = bigint_divide(a, zero);

    // Division by zero should return NULL or handle error
    EXPECT_EQ(result, nullptr);

    bigint_free(a);
    bigint_free(zero);
}

TEST_F(BigIntArithmeticTest, DivideZeroByNumber) {
    BigInt* zero = bigint_create("0");
    BigInt* b = bigint_create("123");
    BigInt* result = bigint_divide(zero, b);

    char* result_str = bigint_to_string(result);
    EXPECT_STREQ(result_str, "0");

    free(result_str);
    bigint_free(zero);
    bigint_free(b);
    bigint_free(result);
}

// Remainder/Modulo Tests
TEST_F(BigIntArithmeticTest, RemainderPositiveNumbers) {
    BigInt* a = bigint_create("456");
    BigInt* b = bigint_create("123");
    BigInt* result = bigint_remainder(a, b);

    char* result_str = bigint_to_string(result);
    EXPECT_STREQ(result_str, "87");  // 456 % 123 = 87

    free(result_str);
    bigint_free(a);
    bigint_free(b);
    bigint_free(result);
}

TEST_F(BigIntArithmeticTest, RemainderByZero) {
    BigInt* a = bigint_create("123");
    BigInt* zero = bigint_create("0");
    BigInt* result = bigint_remainder(a, zero);

    // Remainder by zero should return NULL or handle error
    EXPECT_EQ(result, nullptr);

    bigint_free(a);
    bigint_free(zero);
}

// Divide and Remainder Tests
TEST_F(BigIntArithmeticTest, DivideAndRemainder) {
    BigInt* a = bigint_create("456");
    BigInt* b = bigint_create("123");
    BigInt** results = bigint_divide_and_remainder(a, b);

    if (results != nullptr) {
        char* quotient_str = bigint_to_string(results[0]);
        char* remainder_str = bigint_to_string(results[1]);

        EXPECT_STREQ(quotient_str, "3");
        EXPECT_STREQ(remainder_str, "87");

        free(quotient_str);
        free(remainder_str);
        bigint_free(results[0]);
        bigint_free(results[1]);
        free(results);
    }

    bigint_free(a);
    bigint_free(b);
}

// Edge Cases and Large Number Tests
TEST_F(BigIntArithmeticTest, ArithmeticWithLargeNumbers) {
    BigInt* a = bigint_create("123456789012345678901234567890");
    BigInt* b = bigint_create("987654321098765432109876543210");

    // Test addition with large numbers
    BigInt* sum = bigint_add(a, b);
    char* sum_str = bigint_to_string(sum);
    EXPECT_STREQ(sum_str, "1111111110111111111011111111100");

    free(sum_str);
    bigint_free(sum);
    bigint_free(a);
    bigint_free(b);
}
