#include "../unity/src/unity.h"
#include "../minishell.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_function1(void) {
    t_token *result = token_creator("echo 1");
TEST_ASSERT_EQUAL_STRING("echo 1", result->value);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_function1);
    return UNITY_END();
}