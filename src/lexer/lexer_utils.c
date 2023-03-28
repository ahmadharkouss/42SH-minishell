#include "../headers/lexer_all.h"

void lexer_skip_comment(struct Lexer *lexer)
{
    while (lexer->ch != '\n' && lexer->ch != 0)
    {
        lexer_next_char(lexer);
    }
}

int lexer_is_digit(char ch)
{
    return ch >= '0' && ch <= '9';
}

void lexer_number(struct Lexer *lexer)
{
    char buffer[13000];
    int i = 0;
    while (lexer_is_digit(lexer->ch))
    {
        buffer[i++] = lexer->ch;
        lexer_next_char(lexer);
    }
    buffer[i] = 0;
    lexer->token->value = strdup(buffer);
}

int lexer_is_alpha(char ch)
{
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_';
}
