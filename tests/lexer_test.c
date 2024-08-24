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
void test_function2(void) {
    t_token *result = token_creator("echo 1 | wc -l");
TEST_ASSERT_EQUAL_STRING("echo 1", result->value);
TEST_ASSERT_EQUAL_STRING("|", result->next->value);
TEST_ASSERT_EQUAL_STRING("wc -l", result->next->next->value);
}

void test_function3(void) {
    t_token *result = token_creator("cat >> s");
TEST_ASSERT_EQUAL_STRING("cat", result->value);
TEST_ASSERT_EQUAL_STRING(">>", result->next->value);
TEST_ASSERT_EQUAL_STRING("s", result->next->next->value);
}

void test_function4(void) {
    t_token *result = token_creator("echo<<sort>grep");
TEST_ASSERT_EQUAL_STRING("echo", result->value);
TEST_ASSERT_EQUAL_STRING("<<", result->next->value);
TEST_ASSERT_EQUAL_STRING("sort", result->next->next->value);
TEST_ASSERT_EQUAL_STRING(">", result->next->next->next->value);
TEST_ASSERT_EQUAL_STRING("grep", result->next->next->next->next->value);
}

void test_function5(void) {
    t_token *result = token_creator("ls>cat>>test<s|<<eof cat -e |  sort -e");
TEST_ASSERT_EQUAL_STRING("ls", result->value);
TEST_ASSERT_EQUAL_STRING(">", result->next->value);
TEST_ASSERT_EQUAL_STRING("cat", result->next->next->value);
TEST_ASSERT_EQUAL_STRING(">>", result->next->next->next->value);
TEST_ASSERT_EQUAL_STRING("test", result->next->next->next->next->value);
TEST_ASSERT_EQUAL_STRING("<", result->next->next->next->next->next->value);
TEST_ASSERT_EQUAL_STRING("s", result->next->next->next->next->next->next->value);
TEST_ASSERT_EQUAL_STRING("|", result->next->next->next->next->next->next->next->value);
TEST_ASSERT_EQUAL_STRING("<<", result->next->next->next->next->next->next->next->next->value);
TEST_ASSERT_EQUAL_STRING("eof cat -e", result->next->next->next->next->next->next->next->next->next->value);
TEST_ASSERT_EQUAL_STRING("|", result->next->next->next->next->next->next->next->next->next->next->value);
TEST_ASSERT_EQUAL_STRING("sort -e", result->next->next->next->next->next->next->next->next->next->next->next->value);
}

void test_function6(void) {
    t_token *result = token_creator("cat >>|");
TEST_ASSERT_EQUAL_STRING("cat", result->value);
TEST_ASSERT_EQUAL_STRING(">>", result->next->value);
TEST_ASSERT_EQUAL_STRING("|", result->next->next->value);
}

void test_function7(void) {
    t_token *result = token_creator("<<heredoc eof | cat >>zosia");
TEST_ASSERT_EQUAL_STRING("<<", result->value);
TEST_ASSERT_EQUAL_STRING("heredoc eof", result->next->value);
TEST_ASSERT_EQUAL_STRING("|", result->next->next->value);
TEST_ASSERT_EQUAL_STRING("cat", result->next->next->next->value);
TEST_ASSERT_EQUAL_STRING(">>", result->next->next->next->next->value);
TEST_ASSERT_EQUAL_STRING("zosia", result->next->next->next->next->next->value);
}

void test_function8(void) {
    t_token *result = token_creator("cat |<<");
TEST_ASSERT_EQUAL_STRING("cat", result->value);
TEST_ASSERT_EQUAL_STRING("|", result->next->value);
TEST_ASSERT_EQUAL_STRING("<<", result->next->next->value);
}

void test_function9(void) {
    t_token *result = token_creator("grep '| << echo >' ");
TEST_ASSERT_EQUAL_STRING("grep '| << echo >'", result->value);
}

// not needed when using generate_test_runner.rb
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