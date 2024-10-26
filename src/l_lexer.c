#include <l_lexer.h>
#include <ctype.h>
#include <string.h>

const char *keywords[] = { "int",    "return", "if",	   "else",   "for",
			   "while",  "void",   "char",	   "float",  "double",
			   "struct", "break",  "continue", "sizeof", "typedef" };

token_t lexer_get_next_token(FILE *source)
{
	token_t token;
	int ch;

	do {
		ch = fgetc(source);
	} while (isspace(ch));

	if (ch == EOF) {
		token.type = TOKEN_EOF;
		strncpy(token.value, "EOF", strlen("EOF") + 1);
		return token;
	}

	if (isalpha(ch) || ch == '_') {
		int i = 0;
		token.value[i++] = ch;

		while (isalnum((ch = fgetc(source))) || ch == '_') {
			if (i < MAX_TOKEN_LEN - 1) {
				token.value[i++] = ch;
			}
		}
		token.value[i] = '\0';
		ungetc(ch, source);

		if (lexer_is_keyword(token.value)) {
			token.type = TOKEN_KEYWORD;
		} else {
			token.type = TOKEN_IDENTIFIER;
		}
		return token;
	}

	// Handle numbers
	if (isdigit(ch)) {
		int i = 0;
		token.value[i++] = ch;

		while (isdigit((ch = fgetc(source)))) {
			if (i < MAX_TOKEN_LEN - 1) {
				token.value[i++] = ch;
			}
		}
		token.value[i] = '\0';
		ungetc(ch, source);

		token.type = TOKEN_NUMBER;
		return token;
	}

	// Handle symbols (operators, punctuation, etc.)
	token.value[0] = ch;
	token.value[1] = '\0';

	token.type = TOKEN_SYMBOL;
	return token;
}
int lexer_is_keyword(const char *str)
{
	for (size_t i = 0; i < sizeof(keywords) / sizeof(char *); i++) {
		if (strcmp(str, keywords[i]) == 0) {
			return 1;
		}
	}
	return 0;
}
void lexer_dbg_print_token(token_t token)
{
	const char *token_type_str;

	switch (token.type) {
	case TOKEN_KEYWORD:
		token_type_str = "Keyword";
		break;
	case TOKEN_IDENTIFIER:
		token_type_str = "Identifier";
		break;
	case TOKEN_NUMBER:
		token_type_str = "Number";
		break;
	case TOKEN_SYMBOL:
		token_type_str = "Symbol";
		break;
	case TOKEN_UNKNOWN:
		token_type_str = "Unknown";
		break;
	case TOKEN_EOF:
		token_type_str = "EOF";
		break;
	default:
		token_type_str = "Unknown";
	}

	printf("Token: %-12s | Type: %s\n", token.value, token_type_str);
}
