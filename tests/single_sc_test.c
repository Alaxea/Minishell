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
	printf("\033[1;32mecho 1 > file1\033[0m\n");

    t_token *tokens = token_creator("echo 1 > file1");
	t_simple_cmd *sc = simple_cmd_creator(tokens);

	TEST_ASSERT_EQUAL_STRING("echo", sc->name);
	TEST_ASSERT_EQUAL_STRING("file1", sc->output_path);
	TEST_ASSERT_EQUAL(false, sc->heredoc);
	TEST_ASSERT_EQUAL_STRING(NULL, sc->input_path);
	TEST_ASSERT_EQUAL_STRING(NULL, sc->output_path_append);
	TEST_ASSERT_EQUAL_STRING("echo", sc->cmd[0]);
	TEST_ASSERT_EQUAL_STRING("1", sc->cmd[1]);
}

void test_function2(void) {
    printf("\033[0;32mTEST2\033[0m\n");
	printf("\033[1;32mcat file1.txt file2.txt\033[0m\n");

    t_token *tokens = token_creator("cat file1.txt file2.txt");
	t_simple_cmd *sc = simple_cmd_creator(tokens);
	TEST_ASSERT_EQUAL_STRING("cat", sc->name);
	TEST_ASSERT_EQUAL_STRING(NULL, sc->output_path);
	TEST_ASSERT_EQUAL(false, sc->heredoc);
	TEST_ASSERT_EQUAL_STRING(NULL, sc->input_path);
	TEST_ASSERT_EQUAL_STRING(NULL, sc->output_path_append);
	TEST_ASSERT_EQUAL_STRING("cat", sc->cmd[0]);
	TEST_ASSERT_EQUAL_STRING("file1.txt", sc->cmd[1]);
	TEST_ASSERT_EQUAL_STRING("file2.txt", sc->cmd[2]);
}

void test_function3(void) {
	printf("\033[0;32mTEST3\033[0m\n");
	printf("\033[1;32mwatch -n 5 'df -h | grep \"^/dev\"'\033[0m\n");

    t_token *tokens = token_creator("watch -n 5 'df -h | grep \"^/dev\"'");
	t_simple_cmd *sc = simple_cmd_creator(tokens);

	TEST_ASSERT_EQUAL_STRING("watch", sc->name);
	TEST_ASSERT_EQUAL_STRING(NULL, sc->output_path);
	TEST_ASSERT_EQUAL(false, sc->heredoc);
	TEST_ASSERT_EQUAL_STRING(NULL, sc->input_path);
	TEST_ASSERT_EQUAL_STRING(NULL, sc->output_path_append);
	TEST_ASSERT_EQUAL_STRING("watch", sc->cmd[0]);
	TEST_ASSERT_EQUAL_STRING("-n", sc->cmd[1]);
	TEST_ASSERT_EQUAL_STRING("5", sc->cmd[2]);
	TEST_ASSERT_EQUAL_STRING("'df -h | grep \"^/dev\"'", sc->cmd[3]);
	
}

void test_function4(void) {
    t_token *tokens = token_creator("< input.txt sort >> output.txt");
		printf("\033[1;32m< input.txt sort >> output.txt\033[0m\n");

	t_simple_cmd *sc = simple_cmd_creator(tokens);

	TEST_ASSERT_EQUAL_STRING("sort", sc->name);
	TEST_ASSERT_EQUAL_STRING(NULL, sc->output_path);
	TEST_ASSERT_EQUAL_STRING(false, sc->heredoc);
	TEST_ASSERT_EQUAL_STRING("input.txt", sc->input_path);
	TEST_ASSERT_EQUAL_STRING("output.txt", sc->output_path_append);
	TEST_ASSERT_EQUAL_STRING("sort", sc->cmd[0]);
	TEST_ASSERT_EQUAL_STRING(NULL, sc->cmd[1]);	
}

void test_function7(void) {
    printf("\033[0;32mTEST7\033[0m\n");
	printf("\033[1;32mcat file\033[0m\n");
    t_token *tokens = token_creator("cat file");
	t_simple_cmd *sc = simple_cmd_creator(tokens);
	TEST_ASSERT_EQUAL_STRING("cat", sc->name);
	TEST_ASSERT_EQUAL_STRING(NULL, sc->output_path);
	TEST_ASSERT_EQUAL(false, sc->heredoc);
	TEST_ASSERT_EQUAL_STRING(NULL, sc->input_path);
	TEST_ASSERT_EQUAL_STRING(NULL, sc->output_path_append);
	TEST_ASSERT_EQUAL_STRING("cat", sc->cmd[0]);
	TEST_ASSERT_EQUAL_STRING("file", sc->cmd[1]);
}
void test_function6(void) {
    printf("\033[0;32mTEST6\033[0m\n");
	printf("\033[1;32mecho \"super fajnie to wychodzi\" >> file\033[0m\n");

    t_token *tokens = token_creator("echo \"super fajnie to wychodzi\" >> file");
	t_simple_cmd *sc = simple_cmd_creator(tokens);
	TEST_ASSERT_EQUAL_STRING("echo", sc->name);
	TEST_ASSERT_EQUAL_STRING(NULL, sc->output_path);
	TEST_ASSERT_EQUAL(false, sc->heredoc);
	TEST_ASSERT_EQUAL_STRING(NULL, sc->input_path);
	TEST_ASSERT_EQUAL_STRING("file", sc->output_path_append);
	TEST_ASSERT_EQUAL_STRING("echo", sc->cmd[0]);
	TEST_ASSERT_EQUAL_STRING("\"super fajnie to wychodzi\"", sc->cmd[1]);
	TEST_ASSERT_EQUAL_STRING(NULL, sc->cmd[2]);
}
void test_function5(void) {
    printf("\033[0;32mTEST5\033[0m\n");
	printf("\033[1;32mls -a -l<file>file1\033[0m\n");

    t_token *tokens = token_creator("ls -a -l<file>file1");
	t_simple_cmd *sc = simple_cmd_creator(tokens);
	TEST_ASSERT_EQUAL_STRING("ls", sc->name);
	TEST_ASSERT_EQUAL_STRING("file1", sc->output_path);
	TEST_ASSERT_EQUAL(false, sc->heredoc);
	TEST_ASSERT_EQUAL_STRING("file", sc->input_path);
	TEST_ASSERT_EQUAL_STRING(NULL, sc->output_path_append);
	TEST_ASSERT_EQUAL_STRING("ls", sc->cmd[0]);
	TEST_ASSERT_EQUAL_STRING("-a", sc->cmd[1]);
	TEST_ASSERT_EQUAL_STRING("-l", sc->cmd[2]);
}


void test_function8(void) {
    printf("\033[0;32mTEST8\033[0m\n");

    printf("\033[1;32m<<x cat\033[0m\n");

    t_token *tokens = token_creator("<<x cat");
	t_simple_cmd *sc = simple_cmd_creator(tokens);
	TEST_ASSERT_EQUAL_STRING("cat", sc->name);

	TEST_ASSERT_EQUAL_STRING(NULL, sc->output_path);
	TEST_ASSERT_EQUAL(true, sc->heredoc);
	TEST_ASSERT_EQUAL_STRING(NULL, sc->input_path);
	TEST_ASSERT_EQUAL_STRING(NULL, sc->output_path_append);
	TEST_ASSERT_EQUAL_STRING("cat", sc->cmd[0]);
	TEST_ASSERT_EQUAL_STRING(NULL, sc->cmd[1]);
	TEST_ASSERT_EQUAL_STRING("x", sc->delimiter_heredoc);
}

void test_function9(void) {
    printf("\033[0;32mTEST9\033[0m\n");
    t_token *tokens = token_creator("<input.txt sort>>output.txt");
		printf("\033[1;32m<input.txt sort>>output.txt\033[0m\n");

	t_simple_cmd *sc = simple_cmd_creator(tokens);

	TEST_ASSERT_EQUAL_STRING("sort", sc->name);
	TEST_ASSERT_EQUAL_STRING(NULL, sc->output_path);
	TEST_ASSERT_EQUAL_STRING(false, sc->heredoc);
	TEST_ASSERT_EQUAL_STRING("input.txt", sc->input_path);
	TEST_ASSERT_EQUAL_STRING("output.txt", sc->output_path_append);
	TEST_ASSERT_EQUAL_STRING("sort", sc->cmd[0]);
	TEST_ASSERT_EQUAL_STRING(NULL, sc->cmd[1]);	
}


void test_function10(void) {
    printf("\033[0;32mTEST10\033[0m\n");

    printf("\033[1;32m<< x cat >o\033[0m\n");

    t_token *tokens = token_creator("<< x cat >o");
	t_simple_cmd *sc = simple_cmd_creator(tokens);

	TEST_ASSERT_EQUAL_STRING("cat", sc->name);
	TEST_ASSERT_EQUAL_STRING("o", sc->output_path);
	TEST_ASSERT_EQUAL(true, sc->heredoc);
	TEST_ASSERT_EQUAL_STRING(NULL, sc->input_path);
	TEST_ASSERT_EQUAL_STRING(NULL, sc->output_path_append);
	TEST_ASSERT_EQUAL_STRING("cat", sc->cmd[0]);
	TEST_ASSERT_EQUAL_STRING(NULL, sc->cmd[1]);
	TEST_ASSERT_EQUAL_STRING("x", sc->delimiter_heredoc);
}



void test_function11(void) {
    printf("\033[0;32mTEST11\033[0m\n");

    printf("\033[1;32mecho hello > file.txt\033[0m\n");

    t_token *tokens = token_creator("echo hello > file.txt");
	t_simple_cmd *sc = simple_cmd_creator(tokens);
	TEST_ASSERT_EQUAL_STRING("echo", sc->name);

	TEST_ASSERT_EQUAL_STRING("file.txt", sc->output_path);
	TEST_ASSERT_EQUAL(false, sc->heredoc);
	TEST_ASSERT_EQUAL_STRING(NULL, sc->input_path);
	TEST_ASSERT_EQUAL_STRING(NULL, sc->output_path_append);
	TEST_ASSERT_EQUAL_STRING("echo", sc->cmd[0]);
	TEST_ASSERT_EQUAL_STRING("hello", sc->cmd[1]);
	TEST_ASSERT_EQUAL_STRING(NULL, sc->cmd[2]);
	TEST_ASSERT_EQUAL_STRING(NULL, sc->delimiter_heredoc);
}

void test_function12(void) {
    printf("\033[0;32mTEST12\033[0m\n");

    printf("\033[1;32mcat < input.txt\033[0m\n");

    t_token *tokens = token_creator("cat < input.txt");
	t_simple_cmd *sc = simple_cmd_creator(tokens);
	TEST_ASSERT_EQUAL_STRING("cat", sc->name);

	TEST_ASSERT_EQUAL_STRING(NULL, sc->output_path);
	TEST_ASSERT_EQUAL(false, sc->heredoc);
	TEST_ASSERT_EQUAL_STRING("input.txt", sc->input_path);
	TEST_ASSERT_EQUAL_STRING(NULL, sc->output_path_append);
	TEST_ASSERT_EQUAL_STRING("cat", sc->cmd[0]);
	TEST_ASSERT_EQUAL_STRING(NULL, sc->cmd[1]);
	TEST_ASSERT_EQUAL_STRING(NULL, sc->delimiter_heredoc);
}

void test_function13(void) {
    printf("\033[0;32mTEST13\033[0m\n");

    printf("\033[1;32mgcc -o program file.c\033[0m\n");

    t_token *tokens = token_creator("gcc -o program file.c");
	t_simple_cmd *sc = simple_cmd_creator(tokens);
	TEST_ASSERT_EQUAL_STRING("gcc", sc->name);

	TEST_ASSERT_EQUAL_STRING(NULL, sc->output_path);
	TEST_ASSERT_EQUAL(false, sc->heredoc);
	TEST_ASSERT_EQUAL_STRING(NULL, sc->input_path);
	TEST_ASSERT_EQUAL_STRING(NULL, sc->output_path_append);
	TEST_ASSERT_EQUAL_STRING("gcc", sc->cmd[0]);
	TEST_ASSERT_EQUAL_STRING("-o", sc->cmd[1]);
	TEST_ASSERT_EQUAL_STRING("program", sc->cmd[2]);
	TEST_ASSERT_EQUAL_STRING("file.c", sc->cmd[3]);
	TEST_ASSERT_EQUAL_STRING(NULL, sc->cmd[4]);
	TEST_ASSERT_EQUAL_STRING(NULL, sc->delimiter_heredoc);
}

void test_function14(void) {
    printf("\033[0;32mTEST14\033[0m\n");

    printf("\033[1;32mrm -rf /home/user/*\033[0m\n");

    t_token *tokens = token_creator("rm -rf /home/user/*");
	t_simple_cmd *sc = simple_cmd_creator(tokens);
	TEST_ASSERT_EQUAL_STRING("rm", sc->name);

	TEST_ASSERT_EQUAL_STRING(NULL, sc->output_path);
	TEST_ASSERT_EQUAL(false, sc->heredoc);
	TEST_ASSERT_EQUAL_STRING(NULL, sc->input_path);
	TEST_ASSERT_EQUAL_STRING(NULL, sc->output_path_append);
	TEST_ASSERT_EQUAL_STRING("rm", sc->cmd[0]);
	TEST_ASSERT_EQUAL_STRING("-rf", sc->cmd[1]);
	TEST_ASSERT_EQUAL_STRING("/home/user/*", sc->cmd[2]);
	TEST_ASSERT_EQUAL_STRING(NULL, sc->cmd[3]);
	TEST_ASSERT_EQUAL_STRING(NULL, sc->delimiter_heredoc);
}

void test_function15(void) {
    printf("\033[0;32mTEST15\033[0m\n");

    printf("\033[1;32mmkdir -p /new/dir && cd /new/dir\033[0m\n");

    t_token *tokens = token_creator("mkdir -p /new/dir && cd /new/dir");
	t_simple_cmd *sc = simple_cmd_creator(tokens);
	TEST_ASSERT_EQUAL_STRING("mkdir", sc->name);

	TEST_ASSERT_EQUAL_STRING(NULL, sc->output_path);
	TEST_ASSERT_EQUAL(false, sc->heredoc);
	TEST_ASSERT_EQUAL_STRING(NULL, sc->input_path);
	TEST_ASSERT_EQUAL_STRING(NULL, sc->output_path_append);
	TEST_ASSERT_EQUAL_STRING("mkdir", sc->cmd[0]);
	TEST_ASSERT_EQUAL_STRING("-p", sc->cmd[1]);
	TEST_ASSERT_EQUAL_STRING("/new/dir", sc->cmd[2]);
	TEST_ASSERT_EQUAL_STRING(NULL, sc->cmd[3]);
	TEST_ASSERT_EQUAL_STRING(NULL, sc->delimiter_heredoc);
}

	// sc->cmd **char
	// sc->heredoc bool
	// sc->input_path *char
	// sc->name *char
	// sc->output_path *char
	// sc->output_path_append *char
	// sc->parser_done bool
	// sc->path *char

// ls>cat>>test<s 
// <<eof cat -e 

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
    RUN_TEST(test_function14);

    return UNITY_END();
}