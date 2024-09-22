
#include "../unity/src/unity.h"
#include "../minishell.h"

extern char **environ;

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_function1(void) {

 printf("\033[0;32mTEST1\033[0m\n");
    printf("\033[1;32mecho 1\033[0m\n");

    t_token *token = token_creator("echo 1");
	t_simple_cmd *sc = parser(token);
	expand(sc, environ);
	TEST_ASSERT_EQUAL_STRING("echo", sc->name);
	TEST_ASSERT_EQUAL_STRING("echo", sc->cmd[0]);
	TEST_ASSERT_EQUAL_STRING("1", sc->cmd[1]);
}

void test_function2(void) {
 printf("\033[0;32mTEST2\033[0m\n");
    printf("\033[1;32mecho '1'\033[0m\n");
	char *input = "echo '1'";
    t_token *token = token_creator(input);
	t_simple_cmd *sc = parser(token);
	expand(sc, environ);
	TEST_ASSERT_EQUAL_STRING("echo", sc->name);
	TEST_ASSERT_EQUAL_STRING("echo", sc->cmd[0]);
	TEST_ASSERT_EQUAL_STRING("1", sc->cmd[1]);
}

void test_function3(void) {
 printf("\033[0;32mTEST3\033[0m\n");
    printf("\033[1;32mecho \"1\"\033[0m\n");
	char *input = "echo \"1\"";
    t_token *token = token_creator(input);
	t_simple_cmd *sc = parser(token);
	expand(sc, environ);
	TEST_ASSERT_EQUAL_STRING("echo", sc->name);
	TEST_ASSERT_EQUAL_STRING("echo", sc->cmd[0]);
	TEST_ASSERT_EQUAL_STRING("1", sc->cmd[1]);
}


int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_function1);
    RUN_TEST(test_function2);
    RUN_TEST(test_function3);

    return UNITY_END();
}