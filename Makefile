# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/25 17:14:37 by sakllam           #+#    #+#              #
#    Updated: 2022/04/26 05:14:09 by sakllam          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= ./minishell
SRCS= 	execution/exec_tree.c        parsing/abstract_tree___.c   parsing/lexer__.c            parsing/syntax_analyser.c \
		execution/exec_tree_.c       parsing/abstract_tree____.c  parsing/lexer___.c           parsing/syntax_analyser_.c \
		execution/exec_tree__.c      parsing/abstract_tree_____.c parsing/lst_functions.c      parsing/syntax_analyser__.c \
		execution/exec_tree___.c     parsing/her_doc_start.c      parsing/parsing.c            parsing/syntax_analyser___.c \
		execution/exec_tree____.c    parsing/herdocstpone.c       parsing/redesin.c            parsing/trim.c \
		parsing/abstract_tree.c      parsing/lexer.c              parsing/redesin_.c  execution/envmanup/clone_env.c\
		parsing/abstract_tree_.c     parsing/lexer_.c             parsing/redesin__.c \
		execution/builtin/cd.c       execution/envmanup/clone_env_.c          execution/execution_utils/exec_utils_.c \
		execution/builtin/echo.c     execution/envmanup/clone_env__.c         execution/execution_utils/herdoc_work.c \
		execution/builtin/env.c      execution/execution_utils/before_exec.c   execution/execution_utils/ismatch.c \
		execution/builtin/exit.c     execution/execution_utils/before_exec_.c  execution/execution_utils/ismatch_.c \
		execution/builtin/export.c   execution/execution_utils/before_exec__.c execution/execution_utils/split_join.c execution/builtin/pwd.c\
  		execution/execution_utils/before_func.c   execution/execution_utils/variablesexp.c \
		execution/builtin/unset.c    execution/execution_utils/doubleexp.c     execution/execution_utils/variablesexp_.c \
		execution/builtin/wild.c      execution/execution_utils/doubleexp_.c execution/builtin/display_export.c\
		execution/execution_utils/exec_utils.c \
		main.c    parsing/nomore.c  execution/builtin/extra_norm.c      main_utils.c trush.c\

CFLAGS := -g -Wall -Wextra -Werror
LFLAGS := -L/goinfre/sakllam/.brew/opt/readline/lib
IFLAGS := -I/goinfre/sakllam/.brew/opt/readline/include

OBJS :=$(SRCS:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	gcc $(CFLAGS) $^ -o $@ $(FLAGS) -lreadline -lncurses $(LFLAGS)

%.o: %.c mini_shell.h 
	gcc $(CFLAGS) $(IFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
