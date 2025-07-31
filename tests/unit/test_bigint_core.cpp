#include <gtest/gtest.h>
extern "C" {
    #include "bigint.h"
}

class BigIntCoreTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code for each test
    }

    void TearDown() override {
        // Cleanup code for each test
    }
};

// Test BigInt creation from string
TEST_F(BigIntCoreTest, CreatePositiveNumber) {
    BigInt* num = bigint_create("12345");
    ASSERT_NE(num, nullptr);

    char* str = bigint_to_string(num);
    EXPECT_STREQ(str, "12345");

    free(str);
    bigint_free(num);
}

TEST_F(BigIntCoreTest, CreateNegativeNumber) {
    BigInt* num = bigint_create("-9876");
    ASSERT_NE(num, nullptr);

    char* str = bigint_to_string(num);
    EXPECT_STREQ(str, "-9876");

    free(str);
    bigint_free(num);
}

TEST_F(BigIntCoreTest, CreateZero) {
    BigInt* num = bigint_create("0");
    ASSERT_NE(num, nullptr);

    char* str = bigint_to_string(num);
    EXPECT_STREQ(str, "0");

    free(str);
    bigint_free(num);
}

TEST_F(BigIntCoreTest, CreateLargeNumber) {
    const char* large_num = "123456789012345678901234567890";
    BigInt* num = bigint_create(const_cast<char*>(large_num));
    ASSERT_NE(num, nullptr);

    char* str = bigint_to_string(num);
    EXPECT_STREQ(str, large_num);

    free(str);
    bigint_free(num);
}

TEST_F(BigIntCoreTest, CreateFromInvalidString) {
    BigInt* num = bigint_create(nullptr);
    EXPECT_EQ(num, nullptr);

    num = bigint_create("");
    EXPECT_EQ(num, nullptr);

    num = bigint_create("abc123");
    EXPECT_EQ(num, nullptr);
}

// Test BigInt comparison
TEST_F(BigIntCoreTest, CompareEqualNumbers) {
    BigInt* num1 = bigint_create("12345");
    BigInt* num2 = bigint_create("12345");

    EXPECT_EQ(bigint_compare(num1, num2), 0);

    bigint_free(num1);
    bigint_free(num2);
}

TEST_F(BigIntCoreTest, ComparePositiveNumbers) {
    BigInt* smaller = bigint_create("123");
    BigInt* larger = bigint_create("456");

    EXPECT_EQ(bigint_compare(smaller, larger), -1);
    EXPECT_EQ(bigint_compare(larger, smaller), 1);

    bigint_free(smaller);
    bigint_free(larger);
}

TEST_F(BigIntCoreTest, CompareNegativeNumbers) {
    BigInt* neg_small = bigint_create("-456");
    BigInt* neg_large = bigint_create("-123");

    EXPECT_EQ(bigint_compare(neg_small, neg_large), -1);
    EXPECT_EQ(bigint_compare(neg_large, neg_small), 1);

    bigint_free(neg_small);
    bigint_free(neg_large);
}

TEST_F(BigIntCoreTest, CompareMixedSigns) {
    BigInt* positive = bigint_create("123");
    BigInt* negative = bigint_create("-123");

    EXPECT_EQ(bigint_compare(positive, negative), 1);
    EXPECT_EQ(bigint_compare(negative, positive), -1);

    bigint_free(positive);
    bigint_free(negative);
}

TEST_F(BigIntCoreTest, CompareWithZero) {
    BigInt* zero = bigint_create("0");
    BigInt* positive = bigint_create("123");
    BigInt* negative = bigint_create("-123");

    EXPECT_EQ(bigint_compare(zero, zero), 0);
    EXPECT_EQ(bigint_compare(positive, zero), 1);
    EXPECT_EQ(bigint_compare(zero, positive), -1);
    EXPECT_EQ(bigint_compare(negative, zero), -1);
    EXPECT_EQ(bigint_compare(zero, negative), 1);

    bigint_free(zero);
    bigint_free(positive);
    bigint_free(negative);
}

// Test BigInt to string conversion
TEST_F(BigIntCoreTest, ToStringPositive) {
    BigInt* num = bigint_create("98765");
    char* str = bigint_to_string(num);

    EXPECT_STREQ(str, "98765");

    free(str);
    bigint_free(num);
}

TEST_F(BigIntCoreTest, ToStringNegative) {
    BigInt* num = bigint_create("-54321");
    char* str = bigint_to_string(num);

    EXPECT_STREQ(str, "-54321");

    free(str);
    bigint_free(num);
}

TEST_F(BigIntCoreTest, ToStringZero) {
    BigInt* num = bigint_create("0");
    char* str = bigint_to_string(num);

    EXPECT_STREQ(str, "0");

    free(str);
    bigint_free(num);
}

// Test BigInt copy functionality
TEST_F(BigIntCoreTest, CopyBigInt) {
    BigInt* original = bigint_create("123456789");
    BigInt* copy = bigint_create("0");

    copy = bigint_copy(original);

    char* orig_str = bigint_to_string(original);
    char* copy_str = bigint_to_string(copy);

    EXPECT_STREQ(orig_str, copy_str);

    free(orig_str);
    free(copy_str);
    bigint_free(original);
    bigint_free(copy);
}

// Test memory management
TEST_F(BigIntCoreTest, MemoryManagement) {
    // Test that we can create and free multiple BigInts without memory leaks
    for (int i = 0; i < 1000; i++) {
        BigInt* num = bigint_create("123456789");
        ASSERT_NE(num, nullptr);
        bigint_free(num);
    }
}
