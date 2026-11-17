#include <gtest/gtest.h>

// First test: it only checks that the test setup itself works.
// Real tests for each feature come later.
TEST(SanityTest, TestFrameworkWorks) {
    EXPECT_EQ(1 + 1, 2);
}
