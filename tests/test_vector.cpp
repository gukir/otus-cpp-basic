#include <gtest/gtest.h>

// Простейший тест, который всегда проходит успешно
TEST(HelloTest, BasicAssertions) {
  EXPECT_STRNE("hello", "world");
  EXPECT_EQ(7 * 6, 42);
}
