#include "../unity/src/unity.h"
#include "../minishell.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_function1(void) {
t_token *token = token_creator("| cat file2");
t_simple_cmd *pars = parser(token);
t_simple_cmd *exec = executing(data);
TEST_ASSERT_EQUAL(0, validation(&token));
}



int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_function1);


    return UNITY_END();
}