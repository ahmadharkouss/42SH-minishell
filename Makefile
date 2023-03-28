CC = gcc
CFLAGS =-Wall -Wextra -Werror -pedantic -std=c99 -Wvla

SRCDIR = src
HEADERDIR = $(SRCDIR)/headers
OBJDIR = obj
BINDIR = .

SRC = $(SRCDIR)/main.c $(SRCDIR)/parser/parser.c $(SRCDIR)/lexer/lexer.c \
      $(SRCDIR)/free_functions.c $(SRCDIR)/parser/parse_input.c \
      $(SRCDIR)/parser/print_ast.c $(SRCDIR)/utilities.c \
      $(SRCDIR)/parser/parse_pipeline.c $(SRCDIR)/parser/parse_command.c \
      $(SRCDIR)/parser/parse_shell_command.c $(SRCDIR)/execution/exec_cmd.c \
      $(SRCDIR)/execution/exec_main.c $(SRCDIR)/execution/exec_pipeline.c \
      $(SRCDIR)/execution/exec_shell_cmd.c $(SRCDIR)/execution/execute_utils.c \
      $(SRCDIR)/builtins/cd.c $(SRCDIR)/builtins/kill.c $(SRCDIR)/execution/exec_redir.c \
      $(SRCDIR)/parser/parse_redir.c $(SRCDIR)/builtins/dot.c \
      $(SRCDIR)/builtins/echo.c $(SRCDIR)/builtins/exit.c \
      $(SRCDIR)/builtins/true_false.c $(SRCDIR)/lexer/lexer_helper1.c \
      $(SRCDIR)/lexer/lexer_helper2.c $(SRCDIR)/lexer/lexer_utils.c
OBJ = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
DEP = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.d, $(SRC))

.PHONY: all clean

all: minishell

minishell: $(OBJ)
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(HEADERDIR) -c -o $@ $<

$(OBJDIR)/%.d: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(HEADERDIR) -MM -MT $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $<) -MF $@ $<

-include $(DEP)

clean:
	@rm -rf $(OBJDIR)
	@rm -f $(BINDIR)/minishell
