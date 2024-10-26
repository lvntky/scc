#ifndef __L_LEXER_H__
#define __L_LEXER_H__

#include <stdio.h>

#define MAX_TOKEN_LEN 256

typedef enum token_type {
	TOKEN_KEYWORD,
	TOKEN_IDENTIFIER,
	TOKEN_NUMBER,
	TOKEN_SYMBOL,
	TOKEN_UNKNOWN,
	TOKEN_EOF
} token_type;

typedef struct token {
	token_type type;
	char value[MAX_TOKEN_LEN];
} token_t;

token_t lexer_get_next_token(FILE *source);
int lexer_is_keyword(const char *str);
void lexer_dbg_print_token(token_t token);

#endif //__LEXER_H__