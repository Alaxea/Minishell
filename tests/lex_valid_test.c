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
TEST_ASSERT_EQUAL(0, validation(&token));
}

void test_function2(void) {
t_token *token = token_creator("ls | grep 'zosia >>' >");
TEST_ASSERT_EQUAL(0, validation(&token));
}

void test_function3(void) {
t_token *token = token_creator("uniq | sort");
TEST_ASSERT_EQUAL(1, validation(&token));
}

void test_function4(void) {
t_token *token = token_creator("cat file | sort | | uniq");
TEST_ASSERT_EQUAL(0, validation(&token));
}

void test_function5(void) {
t_token *token = token_creator(" < < file2 cat");
TEST_ASSERT_EQUAL(0, validation(&token));
}

void test_function6(void) {
t_token *token = token_creator("echo zosia > > file");
TEST_ASSERT_EQUAL(0, validation(&token));
}

void test_function7(void) {
t_token *token = token_creator("echo zosia >> file |");
TEST_ASSERT_EQUAL(0, validation(&token));
}

void test_function8(void) {
t_token *token = token_creator("ls>cat>>test<s | <<eof cat -e |  sort -e");
TEST_ASSERT_EQUAL(1, validation(&token));
}

void test_function9(void) {
t_token *token = token_creator("cat > | sort");
TEST_ASSERT_EQUAL(0, validation(&token));
}


int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_function1);
	RUN_TEST(test_function2);
    RUN_TEST(test_function3);
    RUN_TEST(test_function4);
    RUN_TEST(test_function5);
    RUN_TEST(test_function6);
    RUN_TEST(test_function7);
    RUN_TEST(test_function8);
    RUN_TEST(test_function9);

    return UNITY_END();
}