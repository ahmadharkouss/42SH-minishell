#include "../headers/parse_pipeline.h"

int has_pipe(const char *str, size_t end)
{
    size_t i = 0;
    while (i < strlen(str) && i < (size_t)end)
    {
        if (str[i] == '|' || str[i] == '&')
        {
            return 1;
        }
        i++;
    }
    return 0;
}

void checkSubstring(struct Lexer *lexer, AstNode *node)
{
    // Check if "&&" is present in the string
    if (strstr(lexer->input, "&&") != NULL)
    {
        node->value = strdup("&&");
    }
    // Check if "||" is present in the string
    else if (strstr(lexer->input, "||") != NULL)
    {
        node->value = strdup("||");
    }
}

AstNode *parse_and_or(struct Lexer *lexer, int end, int begin_pos)
{
    init_lexer(lexer, begin_pos, 0);
    // Init the AST
    AstNode *andor = init_root(AST_AND_OR);
    // loop through commands seperated by |

    checkSubstring(lexer, andor);
    while (lexer->token->type != TOKEN_SEMI && lexer->token->type != TOKEN_EOF
           && lexer->pos < end)
    {
        while (lexer->token->type != TOKEN_AND_IF
               && lexer->token->type != TOKEN_OR_IF && lexer->pos < end)
        {
            lexer_next_token(lexer, end);
            free_token(lexer->token);
        }
        AstNode *child = parse_pipeline(lexer, lexer->pos, begin_pos);
        // grammar error
        if (child == NULL)
        {
            root_cleanup(andor);
            return NULL;
        }
        add_child(andor, child);
        begin_pos = lexer->pos;
        lexer_next_token(lexer, end);
        free_token(lexer->token);
    }
    // print_ast1(andor , 0);
    //  free_token(lexer->token);
    return andor;
}

AstNode *parse_pipeline(struct Lexer *lexer, int end, int begin_pos)
{
    // Init the lexer
    init_lexer(lexer, begin_pos, 0);
    // Init the AST
    AstNode *pipeline = init_root(AST_PIPELINE);
    // loop through commands seperated by |
    while (lexer->token->type != TOKEN_SEMI && lexer->token->type != TOKEN_EOF
           && lexer->pos < end && lexer->token->type != TOKEN_AND_IF
           && lexer->token->type != TOKEN_OR_IF)
    {
        while (lexer->token->type != TOKEN_PIPE && lexer->pos < end
               && lexer->token->type != TOKEN_AND_IF
               && lexer->token->type != TOKEN_OR_IF)
        {
            lexer_next_token(lexer, end);
            free_token(lexer->token);
        }
        AstNode *child = parse_simple_command(lexer, lexer->pos, begin_pos);
        // grammar error
        if (child == NULL)
        {
            root_cleanup(pipeline);
            return NULL;
        }
        add_child(pipeline, child);
        begin_pos = lexer->pos;
        lexer_next_token(lexer, end);
        free_token(lexer->token);
    }
    // free_token(lexer->token);
    return pipeline;
}
