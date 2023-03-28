#ifndef LEXER_UTILS_H
#define LEXER_UTILS_H

void lexer_skip_comment(struct Lexer *lexer);
int lexer_is_digit(char ch);
void lexer_number(struct Lexer *lexer);
int lexer_is_alpha(char ch);

#endif
