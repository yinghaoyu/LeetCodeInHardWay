#include <stdio.h>
#include <stdlib.h>

static int main_ret = 0;
static int test_count = 0;
static int test_pass = 0;

#define EXPECT_EQ_BASE(equality, expect, actual, format)                                                    \
  do                                                                                                        \
  {                                                                                                         \
    test_count++;                                                                                           \
    if (equality)                                                                                           \
      test_pass++;                                                                                          \
                                                                                                            \
    else                                                                                                    \
    {                                                                                                       \
      fprintf(stderr, "%s:%d expect: " format " actual: " format "\n", __FILE__, __LINE__, expect, actual); \
      main_ret = 1;                                                                                         \
    }                                                                                                       \
  } while (0)

#define EXPECT_EQ_INT(expect, actual) EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%d")

#define EXPECT_EQ_DOUBLE(expect, actual) EXPECT_EQ_BASE((expect) - (actual) < 1e-5, expect, actual, "%.17g")

#define EXPECT_TRUE(actual) EXPECT_EQ_BASE((actual) != 0, "true", "false", "%s")

#define EXPECT_FALSE(actual) EXPECT_EQ_BASE((actual) == 0, "false", "true", "%s")

#define EXPECT_SUMMARY printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
