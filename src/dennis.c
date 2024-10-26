#include <stdio.h>
#include <stdlib.h>
#include <l_lexer.h>

int main(int argc, char **argv)
{
	FILE *source = fopen(argv[1], "r");
	if (!source) {
		perror("Unable to open source code.\n");
		exit(EXIT_FAILURE);
	}

	token_t token;
	do {
		token = lexer_get_next_token(source);
		lexer_dbg_print_token(token);
	} while (token.type != TOKEN_EOF);

	fclose(source);
	return 0;
}