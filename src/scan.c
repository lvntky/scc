#include "../include/scan.h"
#include "../include/data.h"
#include <stdio.h>

void init_scanner() {
  Line = 0;
  Putback = '\n';
}

int character_position(char* string, int index) {
  char* position;
  position = strchr(string, index);
  return (position ? position - string : -1 );
}

int next_character() {
  int character;
  if (Putback) {
    character = Putback;
    Putback = 0;
    return character;
  }
  character = fgetc(Infile);
  if (EOF == character) {
    // Handle end of file
    // For example, you can return a special value or set a flag
  }
  if ('\n' == character) {
    Line++;
  }
  return character;
}

void put_back(int character) { Putback = character; }

int skip(void) {
  int character;
  character = next_character();
  while (' ' == character || '\t' == character || '\n' == character || '\r' == character || '\f' == character) {
    character = next_character();
  }
  return (character);
}

int scan_int(int character) {
  int k, val = 0;
  while ((k = character_position("0123456789", character)) >= 0) {
    val = val * 10 + k;
    character = next_character();
  }
  put_back(character);
  return val;
}

int scan(struct token *t) {
  int c;

  // Skip whitespace
  c = skip();

  // Determine the token based on
  // the input character
  switch (c) {
  case EOF:
    return (0);
  case '+':
    t->token = T_PLUS;
    break;
  case '-':
    t->token = T_MINUS;
    break;
  case '*':
    t->token = T_STAR;
    break;
  case '/':
    t->token = T_SLASH;
    break;
  default:

    // If it's a digit, scan the
    // literal integer value in
    if (isdigit(c)) {
      t->int_value = scan_int(c);
      t->token = T_INTLITERAL;
      break;
    }

    printf("\nUnrecognised character %c on line %d\n", c, Line);
    exit(1);
  }
  return 1;
}

void scan_debugger() {
  printf("====================================\n\tLexical Scan\n");
  char *tokstr[] = { "+", "-", "*", "/", "intlit" };
  token T;
  while (scan(&T)) {
    printf("\nTOKEN: %s", tokstr[T.token]);
    if(T.token == T_INTLITERAL) {
      printf("\t==>\t%d", T.int_value);
    }
  }
  printf("\n====================================");
}
