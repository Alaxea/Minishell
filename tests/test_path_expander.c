
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
    printf("\033[1;32m./minishell\033[0m\n");

    t_token *token = token_creator("./minishell");
	t_simple_cmd *sc = parser(token);
	expand(sc, environ);
	cmd_validation(sc, environ);
	TEST_ASSERT_EQUAL_STRING("/Users/eliza/Projects/common_core/Minishell/minishell", sc->name);
	TEST_ASSERT_EQUAL_STRING("minishell", sc->cmd[0]);
	TEST_ASSERT_EQUAL_STRING(NULL, sc->cmd[1]);
}

void test_function2(void) {

 printf("\033[0;32mTEST2\033[0m\n");
    printf("\033[1;32m/Users/eliza/Projects/common_core/Minishell/minishell\033[0m\n");

    t_token *token = token_creator("/Users/eliza/Projects/common_core/Minishell/minishell");
	t_simple_cmd *sc = parser(token);
	expand(sc, environ);
	cmd_validation(sc, environ);
	TEST_ASSERT_EQUAL_STRING("/Users/eliza/Projects/common_core/Minishell/minishell", sc->name);
	TEST_ASSERT_EQUAL_STRING("/Users/eliza/Projects/common_core/Minishell/minishell", sc->cmd[0]);
	TEST_ASSERT_EQUAL_STRING(NULL, sc->cmd[1]);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_function1);
    RUN_TEST(test_function2);
	
    return UNITY_END();
}