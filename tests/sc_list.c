#include "../unity/src/unity.h"
#include "../minishell.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}
void test_function1(void) {

t_token         *token = token_creator("| cat file2");
t_simple_cmd    *sc = parser(token);

}


int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_function1);
	// RUN_TEST(test_function2);
    // RUN_TEST(test_function3);
    // RUN_TEST(test_function4);
    // RUN_TEST(test_function5);
    // RUN_TEST(test_function6);
    // RUN_TEST(test_function7);
    // RUN_TEST(test_function8);
    // RUN_TEST(test_function9);

    return UNITY_END();
}