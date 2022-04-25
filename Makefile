# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/25 17:14:37 by sakllam           #+#    #+#              #
#    Updated: 2022/04/25 17:14:40 by sakllam          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= ./minishell
SRCS= execution/exec_tree.c   parsing/abstarct_tree.c   parsing/parsing.c  parsing/t_list.c \
      parsing/ft_her_doc.c  parsing/redirections.c parsing/trim.c \
	  execution/free.c parsing/lexer.c parsing/syntax_analyser.c  main.c \
	  execution/builtin/exit.c  execution/execution_utils/before_exec.c \
	  execution/builtin/ft_cd.c execution/execution_utils/doubleexp.cexecution/built in/ft_echo.c \
	  execution/execution_utils/exec_utils.c \
	  execution/builtin/ft_env.c execution/execution_utils/expending.c \
	  execution/builtin/ft_export.c  execution/execution_utils/get_path_utils.c \
	  execution/builtin/ft_pwd.c execution/execution_utils/ismatch.c \
	  execution/builtin/ft_unset.c execution/execution_utils/pipe.c \
	  execution/builtin/wild.c  execution/execution_utils/praparing_execution.c \
	  execution/env mnpl/clone_env.c  execution/execution_utils/redir.c \
	  execution/execution_utils/befoc_fun.c  execution/execution_utils/strjoin_split.c \
	  execution/execution_utils/before_exec copy.c execution/execution_utils/varexp.c \

CFLAGS := -Wall -Wextra -Werror
FLAGS := -lreadline -L `brew --prefix readline`/lib -I `brew --prefix readline`/include -lncurses

OBJS :=$(SRCS:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	gcc $(CFLAGS) $^ -o $@ $(FLAGS)

%.o: %.c mini_shell.h 
	gcc $(CFLAGS) -c $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all