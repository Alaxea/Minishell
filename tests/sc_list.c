#include "../unity/src/unity.h"
#include "../minishell.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_function1(void) {
printf("\033[0;32mTEST1\033[0m\n");
printf("\033[1;32mcat file2\033[0m\n");
t_token         *token = token_creator("cat file2");
t_simple_cmd    *sc = parser(token);
TEST_ASSERT_EQUAL_STRING("cat", sc->name);
}

void test_function2(void) {
    printf("\033[0;32mTEST2\033[0m\n");

    printf("\033[1;32mls -la | grep \"test\" | sort\033[0m\n");

    t_token *tokens = token_creator("ls -la | grep \"test\" | sort");
	t_simple_cmd *sc = parser(tokens);
	TEST_ASSERT_EQUAL_STRING("ls", sc->name);
	TEST_ASSERT_EQUAL_STRING("grep", sc->next->name);
	TEST_ASSERT_EQUAL_STRING("sort", sc->next->next->name);    
}

void test_function3(void) {
    printf("\033[0;32mTEST3\033[0m\n");
    printf("\033[1;32mecho hello > output.txt\033[0m\n");

    t_token *tokens = token_creator("echo hello > output.txt");
    t_simple_cmd *sc = parser(tokens);

    TEST_ASSERT_EQUAL_STRING("echo", sc->name);
    TEST_ASSERT_EQUAL(NULL, sc->next);
}

void test_function4(void) {
    printf("\033[0;32mTEST4\033[0m\n");
    printf("\033[1;32mcat < input.txt | grep \"search\"\033[0m\n");

    t_token *tokens = token_creator("cat < input.txt | grep \"search\"");
    t_simple_cmd *sc = parser(tokens);

    TEST_ASSERT_EQUAL_STRING("cat", sc->name);
    TEST_ASSERT_EQUAL_STRING("grep", sc->next->name);
    TEST_ASSERT_EQUAL_STRING(NULL, sc->next->next);
}


void test_function5(void) {
    printf("\033[0;32mTEST5\033[0m\n");
    printf("\033[1;32mgcc -o program main.c utils.c\033[0m\n");

    t_token *tokens = token_creator("gcc -o program main.c utils.c");
    t_simple_cmd *sc = parser(tokens);

    TEST_ASSERT_EQUAL_STRING("gcc", sc->name);
    TEST_ASSERT_EQUAL(NULL, sc->next);
}

void test_function6(void) {
    printf("\033[0;32mTEST6\033[0m\n");
    printf("\033[1;32mps aux | grep \"nginx\" | awk '{print $2}'\033[0m\n");

    t_token *tokens = token_creator("ps aux | grep \"nginx\" | awk '{print $2}'");
    t_simple_cmd *sc = parser(tokens);

    TEST_ASSERT_EQUAL_STRING("ps", sc->name);
    TEST_ASSERT_EQUAL_STRING("grep", sc->next->name);
    TEST_ASSERT_EQUAL_STRING("awk", sc->next->next->name);
    TEST_ASSERT_EQUAL_STRING(NULL, sc->next->next->next);
}

void test_function7(void) {
    printf("\033[0;32mTEST7\033[0m\n");
    printf("\033[1;32mfind . -type f | < in grep \"main\"\033[0m\n");

    t_token *tokens = token_creator("find . -type f | < in grep \"main\"");
    t_simple_cmd *sc = parser(tokens);

    TEST_ASSERT_EQUAL_STRING("find", sc->name);
    TEST_ASSERT_EQUAL_STRING("grep", sc->next->name);
    TEST_ASSERT_EQUAL_STRING(NULL, sc->next->next);
}

void test_function8(void) {
    printf("\033[0;32mTEST8\033[0m\n");
    printf("\033[1;32mhead -n 10 /var/log/syslog | tail -n 5 | sort > out\033[0m\n");

    t_token *tokens = token_creator("head -n 10 /var/log/syslog | tail -n 5 | sort > out");
    t_simple_cmd *sc = parser(tokens);
    TEST_ASSERT_EQUAL_STRING("head", sc->name);
    TEST_ASSERT_EQUAL_STRING("tail", sc->next->name);
    TEST_ASSERT_EQUAL_STRING("sort", sc->next->next->name);
    TEST_ASSERT_EQUAL_STRING(NULL, sc->next->next->next);

}

void test_function9(void) {
    printf("\033[0;32mTEST9\033[0m\n");
    printf("\033[1;32mdmesg | grep \"error\" | less\033[0m\n");

    t_token *tokens = token_creator("dmesg | grep \"error\" | less");
    t_simple_cmd *sc = parser(tokens);

    TEST_ASSERT_EQUAL_STRING("dmesg", sc->name);
    TEST_ASSERT_EQUAL_STRING("grep", sc->next->name);
    TEST_ASSERT_EQUAL_STRING("less", sc->next->next->name);
    TEST_ASSERT_EQUAL_STRING(NULL, sc->next->next->next);
}

void test_function10(void) {
    printf("\033[0;32mTEST10\033[0m\n");
    printf("\033[1;32m<<eof >out echo \"Hello World\" | tr 'a-z' 'A-Z' | rev\033[0m\n");

    t_token *tokens = token_creator("<<eof >out echo \"Hello World\" | tr 'a-z' 'A-Z' | rev");
    t_simple_cmd *sc = parser(tokens);

    TEST_ASSERT_EQUAL_STRING("echo", sc->name);
    TEST_ASSERT_EQUAL_STRING("tr", sc->next->name);
    TEST_ASSERT_EQUAL_STRING("'a-z'", sc->next->cmd[1]);
    TEST_ASSERT_EQUAL_STRING("'A-Z'", sc->next->cmd[2]);
    TEST_ASSERT_EQUAL_STRING("rev", sc->next->next->name);
    TEST_ASSERT_EQUAL_STRING(NULL, sc->next->next->next);
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
    RUN_TEST(test_function10);

    return UNITY_END();
}