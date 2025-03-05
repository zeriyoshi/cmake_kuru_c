#include "sandbox.h"

#include "unity.h"

static FILE *valid_fp = NULL, *invalid_fp = NULL;

void setUp(void) {
    valid_fp = fopen("/workspaces/cmake_kuru_c/assets/valid.jpg", "rb");
    invalid_fp = fopen("/workspaces/cmake_kuru_c/assets/invalid.jpg", "rb");
}

void tearDown(void) {
    if (valid_fp) {
        fclose(valid_fp);
    }

    if (invalid_fp) {
        fclose(invalid_fp);
    }
}

static inline FILE *get_valid_fp(void) {
    rewind(valid_fp);
    return valid_fp;
}

static inline FILE *get_invalid_fp(void) {
    rewind(invalid_fp);
    return invalid_fp;
}

void test_sandbox_test(void)
{
    TEST_ASSERT_TRUE(sandbox_test());
}

void test_sandbox_jpeg_size(void)
{
    TEST_ASSERT_EQUAL(200, sandbox_get_jpeg_width(get_valid_fp()));
    TEST_ASSERT_EQUAL(300, sandbox_get_jpeg_height(get_valid_fp()));
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_sandbox_test);
    RUN_TEST(test_sandbox_jpeg_size);

    return UNITY_END();
}
