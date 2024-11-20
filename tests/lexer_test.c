#include "../unity/src/unity.h"
#include "../minishell.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_function1(void) {
    t_token *result = token_creator("echo 1", 0, 0);
TEST_ASSERT_EQUAL_STRING("echo 1", result->value);
}
void test_function2(void) {
    t_token *result = token_creator("echo 1 | wc -l", 0, 0);
TEST_ASSERT_EQUAL_STRING("echo 1", result->value);
TEST_ASSERT_EQUAL_STRING("|", result->next->value);
TEST_ASSERT_EQUAL_STRING("wc -l", result->next->next->value);
}

void test_function3(void) {
    t_token *result = token_creator("cat >> s", 0, 0);
TEST_ASSERT_EQUAL_STRING("cat", result->value);
TEST_ASSERT_EQUAL_STRING(">>", result->next->value);
TEST_ASSERT_EQUAL_STRING("s", result->next->next->value);
}

void test_function4(void) {
    t_token *result = token_creator("echo<<sort>grep", 0, 0);
TEST_ASSERT_EQUAL_STRING("echo", result->value);
TEST_ASSERT_EQUAL_STRING("<<", result->next->value);
TEST_ASSERT_EQUAL_STRING("sort", result->next->next->value);
TEST_ASSERT_EQUAL_STRING(">", result->next->next->next->value);
TEST_ASSERT_EQUAL_STRING("grep", result->next->next->next->next->value);
}

void test_function5(void) {
    t_token *result = token_creator("ls>cat>>test<s | <<eof cat -e |  sort -e", 0, 0);
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
    t_token *result = token_creator("cat >>|", 0, 0);
TEST_ASSERT_EQUAL_STRING("cat", result->value);
TEST_ASSERT_EQUAL_STRING(">>", result->next->value);
TEST_ASSERT_EQUAL_STRING("|", result->next->next->value);
}

void test_function7(void) {
    t_token *result = token_creator("<<heredoc eof | cat >>zosia", 0, 0);
TEST_ASSERT_EQUAL_STRING("<<", result->value);
TEST_ASSERT_EQUAL_STRING("heredoc eof", result->next->value);
TEST_ASSERT_EQUAL_STRING("|", result->next->next->value);
TEST_ASSERT_EQUAL_STRING("cat", result->next->next->next->value);
TEST_ASSERT_EQUAL_STRING(">>", result->next->next->next->next->value);
TEST_ASSERT_EQUAL_STRING("zosia", result->next->next->next->next->next->value);
}

void test_function8(void) {
    t_token *result = token_creator("cat |<<", 0, 0);
TEST_ASSERT_EQUAL_STRING("cat", result->value);
TEST_ASSERT_EQUAL_STRING("|", result->next->value);
TEST_ASSERT_EQUAL_STRING("<<", result->next->next->value);
}

void test_function9(void) {
    t_token *result = token_creator("grep '| << echo >' ", 0, 0);
TEST_ASSERT_EQUAL_STRING("grep '| << echo >'", result->value);
}

void test_function10(void) {
    t_token *result = token_creator("ls | < test grep so_long > file2", 0, 0);
TEST_ASSERT_EQUAL_STRING("ls", result->value);
TEST_ASSERT_EQUAL_STRING("|", result->next->value);
TEST_ASSERT_EQUAL_STRING("<", result->next->next->value);
TEST_ASSERT_EQUAL_STRING("test grep so_long", result->next->next->next->value);
TEST_ASSERT_EQUAL_STRING(">", result->next->next->next->next->value);
TEST_ASSERT_EQUAL_STRING("file2", result->next->next->next->next->next->value);
}

void test_function11(void) {
    t_token *result = token_creator("< file1 cat | sort | uniq >output", 0, 0);
TEST_ASSERT_EQUAL_STRING("<", result->value);
TEST_ASSERT_EQUAL_STRING("file1 cat", result->next->value);
TEST_ASSERT_EQUAL_STRING("|", result->next->next->value);
TEST_ASSERT_EQUAL_STRING("sort", result->next->next->next->value);
TEST_ASSERT_EQUAL_STRING("|", result->next->next->next->next->value);
TEST_ASSERT_EQUAL_STRING("uniq", result->next->next->next->next->next->value);
TEST_ASSERT_EQUAL_STRING(">", result->next->next->next->next->next->next->value);
TEST_ASSERT_EQUAL_STRING("output", result->next->next->next->next->next->next->next->value);
}

void test_function12(void) {
    t_token *result = token_creator("watch -n 5 'df -h | grep \"^/dev\"'", 0, 0);
TEST_ASSERT_EQUAL_STRING("watch -n 5 'df -h | grep \"^/dev\"'", result->value);
}

void test_function13(void) {
    t_token *result = token_creator("ls -la | grep \"test\" | sort", 0, 0);
TEST_ASSERT_EQUAL_STRING("ls -la", result->value);
TEST_ASSERT_EQUAL_STRING("|", result->next->value);
TEST_ASSERT_EQUAL_STRING("grep \"test\"", result->next->next->value);
TEST_ASSERT_EQUAL_STRING("|", result->next->next->next->value);
TEST_ASSERT_EQUAL_STRING("sort", result->next->next->next->next->value);
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
    RUN_TEST(test_function10);
    RUN_TEST(test_function11);
    RUN_TEST(test_function12);
    RUN_TEST(test_function13);


    return UNITY_END();
}