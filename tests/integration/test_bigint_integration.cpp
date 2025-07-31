#include <gtest/gtest.h>
#include <vector>
#include <string>
extern "C" {
    #include "bigint.h"
}

class BigIntIntegrationTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code for integration tests
    }

    void TearDown() override {
        // Cleanup code for integration tests
    }

    // Helper function to verify arithmetic identity: (a + b) - b = a
    void VerifyAddSubtractIdentity(const char* a_str, const char* b_str) {
        BigInt* a = bigint_create(const_cast<char*>(a_str));
        BigInt* b = bigint_create(const_cast<char*>(b_str));

        BigInt* sum = bigint_add(a, b);
        BigInt* result = bigint_subtract(sum, b);

        EXPECT_EQ(bigint_compare(a, result), 0);

        bigint_free(a);
        bigint_free(b);
        bigint_free(sum);
        bigint_free(result);
    }

    // Helper function to verify multiplication identity: (a * b) / b = a (when b != 0)
    void VerifyMultiplyDivideIdentity(const char* a_str, const char* b_str) {
        BigInt* a = bigint_create(const_cast<char*>(a_str));
        BigInt* b = bigint_create(const_cast<char*>(b_str));

        BigInt* product = bigint_multiply(a, b);
        BigInt* result = bigint_divide(product, b);

        EXPECT_EQ(bigint_compare(a, result), 0);

        bigint_free(a);
        bigint_free(b);
        bigint_free(product);
        bigint_free(result);
    }
};

// Test complete arithmetic workflows
TEST_F(BigIntIntegrationTest, CompleteArithmeticWorkflow) {
    BigInt* a = bigint_create("12345");
    BigInt* b = bigint_create("6789");
    BigInt* c = bigint_create("100");

    // Complex expression: ((a + b) * c) - (a * c + b * c) should equal 0
    BigInt* sum_ab = bigint_add(a, b);
    BigInt* product_sum_c = bigint_multiply(sum_ab, c);

    BigInt* product_ac = bigint_multiply(a, c);
    BigInt* product_bc = bigint_multiply(b, c);
    BigInt* sum_products = bigint_add(product_ac, product_bc);

    BigInt* final_result = bigint_subtract(product_sum_c, sum_products);

    char* result_str = bigint_to_string(final_result);
    EXPECT_STREQ(result_str, "0");

    free(result_str);
    bigint_free(a);
    bigint_free(b);
    bigint_free(c);
    bigint_free(sum_ab);
    bigint_free(product_sum_c);
    bigint_free(product_ac);
    bigint_free(product_bc);
    bigint_free(sum_products);
    bigint_free(final_result);
}

// Test arithmetic identities
TEST_F(BigIntIntegrationTest, ArithmeticIdentities) {
    // Test addition/subtraction identity with various numbers
    VerifyAddSubtractIdentity("123456", "789012");
    VerifyAddSubtractIdentity("-123456", "789012");
    VerifyAddSubtractIdentity("123456", "-789012");
    VerifyAddSubtractIdentity("-123456", "-789012");

    // Test multiplication/division identity with various numbers
    VerifyMultiplyDivideIdentity("123456", "789");
    VerifyMultiplyDivideIdentity("-123456", "789");
    VerifyMultiplyDivideIdentity("123456", "-789");
    VerifyMultiplyDivideIdentity("-123456", "-789");
}

// Test chained operations
TEST_F(BigIntIntegrationTest, ChainedOperations) {
    BigInt* num = bigint_create("1000");

    // Chain: 1000 + 500 - 200 * 2 / 4 = 1000 + 500 - 100 = 1400
    BigInt* temp1 = bigint_create("500");
    BigInt* step1 = bigint_add(num, temp1);

    BigInt* temp2 = bigint_create("200");
    BigInt* temp3 = bigint_create("2");
    BigInt* step2 = bigint_multiply(temp2, temp3);

    BigInt* temp4 = bigint_create("4");
    BigInt* step3 = bigint_divide(step2, temp4);

    BigInt* final_result = bigint_subtract(step1, step3);

    char* result_str = bigint_to_string(final_result);
    EXPECT_STREQ(result_str, "1400");

    free(result_str);
    bigint_free(num);
    bigint_free(temp1);
    bigint_free(temp2);
    bigint_free(temp3);
    bigint_free(temp4);
    bigint_free(step1);
    bigint_free(step2);
    bigint_free(step3);
    bigint_free(final_result);
}

// Test operations with very large numbers
TEST_F(BigIntIntegrationTest, LargeNumberOperations) {
    const char* large1 = "123456789012345678901234567890123456789";
    const char* large2 = "987654321098765432109876543210987654321";

    BigInt* a = bigint_create(const_cast<char*>(large1));
    BigInt* b = bigint_create(const_cast<char*>(large2));

    // Test that we can perform all operations with large numbers
    BigInt* sum = bigint_add(a, b);
    ASSERT_NE(sum, nullptr);

    BigInt* diff = bigint_subtract(b, a);
    ASSERT_NE(diff, nullptr);

    BigInt* product = bigint_multiply(a, b);
    ASSERT_NE(product, nullptr);

    // Verify the operations are consistent
    BigInt* verify_sum = bigint_add(a, diff);
    EXPECT_EQ(bigint_compare(b, verify_sum), 0);

    bigint_free(a);
    bigint_free(b);
    bigint_free(sum);
    bigint_free(diff);
    bigint_free(product);
    bigint_free(verify_sum);
}

// Test memory management in complex scenarios
TEST_F(BigIntIntegrationTest, MemoryManagementStressTest) {
    const int NUM_ITERATIONS = 100;

    for (int i = 0; i < NUM_ITERATIONS; i++) {
        BigInt* a = bigint_create("12345");
        BigInt* b = bigint_create("67890");

        BigInt* sum = bigint_add(a, b);
        BigInt* product = bigint_multiply(sum, a);
        BigInt* quotient = bigint_divide(product, b);

        // Verify we can still perform operations
        ASSERT_NE(sum, nullptr);
        ASSERT_NE(product, nullptr);
        ASSERT_NE(quotient, nullptr);

        bigint_free(a);
        bigint_free(b);
        bigint_free(sum);
        bigint_free(product);
        bigint_free(quotient);
    }
}

// Test string conversion round-trip integrity
TEST_F(BigIntIntegrationTest, StringConversionIntegrity) {
    std::vector<std::string> test_values = {
        "0",
        "1",
        "-1",
        "123456789",
        "-123456789",
        "999999999999999999999999999999",
        "-999999999999999999999999999999"
    };

    for (const auto& value : test_values) {
        BigInt* num = bigint_create(const_cast<char*>(value.c_str()));
        ASSERT_NE(num, nullptr);

        char* converted = bigint_to_string(num);
        ASSERT_NE(converted, nullptr);

        EXPECT_STREQ(converted, value.c_str());

        // Create another BigInt from the converted string
        BigInt* num2 = bigint_create(converted);
        ASSERT_NE(num2, nullptr);

        // They should be equal
        EXPECT_EQ(bigint_compare(num, num2), 0);

        free(converted);
        bigint_free(num);
        bigint_free(num2);
    }
}

// Test operations with zero
TEST_F(BigIntIntegrationTest, ZeroOperations) {
    BigInt* zero = bigint_create("0");
    BigInt* positive = bigint_create("12345");
    BigInt* negative = bigint_create("-12345");

    // Zero + anything = anything
    BigInt* sum1 = bigint_add(zero, positive);
    EXPECT_EQ(bigint_compare(sum1, positive), 0);

    BigInt* sum2 = bigint_add(zero, negative);
    EXPECT_EQ(bigint_compare(sum2, negative), 0);

    // Anything * 0 = 0
    BigInt* product1 = bigint_multiply(positive, zero);
    EXPECT_EQ(bigint_compare(product1, zero), 0);

    BigInt* product2 = bigint_multiply(negative, zero);
    EXPECT_EQ(bigint_compare(product2, zero), 0);

    // 0 / anything = 0 (for non-zero divisor)
    BigInt* quotient1 = bigint_divide(zero, positive);
    EXPECT_EQ(bigint_compare(quotient1, zero), 0);

    bigint_free(zero);
    bigint_free(positive);
    bigint_free(negative);
    bigint_free(sum1);
    bigint_free(sum2);
    bigint_free(product1);
    bigint_free(product2);
    bigint_free(quotient1);
}

// Test commutative and associative properties
TEST_F(BigIntIntegrationTest, MathematicalProperties) {
    BigInt* a = bigint_create("123");
    BigInt* b = bigint_create("456");
    BigInt* c = bigint_create("789");

    // Test commutative property: a + b = b + a
    BigInt* sum_ab = bigint_add(a, b);
    BigInt* sum_ba = bigint_add(b, a);
    EXPECT_EQ(bigint_compare(sum_ab, sum_ba), 0);

    // Test commutative property: a * b = b * a
    BigInt* product_ab = bigint_multiply(a, b);
    BigInt* product_ba = bigint_multiply(b, a);
    EXPECT_EQ(bigint_compare(product_ab, product_ba), 0);

    // Test associative property: (a + b) + c = a + (b + c)
    BigInt* sum_bc = bigint_add(b, c);
    BigInt* left_assoc = bigint_add(sum_ab, c);
    BigInt* right_assoc = bigint_add(a, sum_bc);
    EXPECT_EQ(bigint_compare(left_assoc, right_assoc), 0);

    bigint_free(a);
    bigint_free(b);
    bigint_free(c);
    bigint_free(sum_ab);
    bigint_free(sum_ba);
    bigint_free(product_ab);
    bigint_free(product_ba);
    bigint_free(sum_bc);
    bigint_free(left_assoc);
    bigint_free(right_assoc);
}

// Test error handling and edge cases
TEST_F(BigIntIntegrationTest, ErrorHandlingIntegration) {
    BigInt* valid = bigint_create("123");
    BigInt* zero = bigint_create("0");

    // Division by zero should be handled gracefully
    BigInt* div_by_zero = bigint_divide(valid, zero);
    EXPECT_EQ(div_by_zero, nullptr);

    BigInt* mod_by_zero = bigint_remainder(valid, zero);
    EXPECT_EQ(mod_by_zero, nullptr);

    // Operations with NULL should be handled gracefully
    BigInt* null_add = bigint_add(nullptr, valid);
    EXPECT_EQ(null_add, nullptr);

    BigInt* null_mult = bigint_multiply(valid, nullptr);
    EXPECT_EQ(null_mult, nullptr);

    bigint_free(valid);
    bigint_free(zero);
}
