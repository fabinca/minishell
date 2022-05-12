# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/21 15:18:52 by cfabian           #+#    #+#              #
#    Updated: 2022/05/12 12:04:29 by hrothery         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		= 	minishell
SRC 		= 	src
SRCS 		= 	$(SRC)/builtins.c \
				$(SRC)/builtins2.c \
				$(SRC)/env_list.c \
				$(SRC)/exec_utils.c\
				$(SRC)/free.c \
				$(SRC)/heredoc.c \
				$(SRC)/lexer.c \
				$(SRC)/main.c \
				$(SRC)/parser.c \
				$(SRC)/piping.c \
				$(SRC)/quotes_and_envvars.c \
				$(SRC)/sort_envvars.c \
				$(SRC)/list_to_string.c \
				$(SRC)/gnl_delimit.c \
				$(SRC)/builtin_utils.c
												
OBJ			= 	obj
OBJS		= 	$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
CC			= 	gcc
RL_MAC		= 	-I $(HOME)/goinfre/.brew/opt/readline/include/ -L $(HOME)/goinfre/.brew/opt/readline/lib/
CFLAGS		=   -Wall -Werror -Wextra 
RM			= 	rm -f
LIB 		=	libft.a
INCLUDES	=	minishell.h libft.h

all: $(NAME)

fix:
	./fix.sh

$(OBJ)/%.o: $(SRC)/%.c $(OBJ)
	@$(CC) $(CFLAGS) -c $< -o $@ -g

$(OBJ)/%.o: $(SRC)/%.c $(OBJ)
	@$(CC) $(CFLAGS) -c $< -o $@ -g

$(OBJ):
	mkdir $(OBJ)

ifeq ($(shell uname), Linux)

$(NAME): $(LIB) $(OBJS)
	$(CC) $(OBJS) $(LIB) -g  -o $(NAME) -lreadline $(CFLAGS)

endif

ifeq ($(shell uname), Darwin)

$(NAME): $(LIB) $(OBJS)
	$(CC) $(OBJS) $(LIB) -g  -o $(NAME) -lreadline $(CFLAGS) $(RL_MAC)

endif

$(LIB):
	@make -C ./libft/
	mv ./libft/$(LIB) ./$(LIB)
	cp ./libft/libft.h ./libft.h

clean:
	$(RM) $(OBJ)/*
	$(RM) $(NAME)

fclean: clean
	$(RM) $(NAME) $(LIB)
	make -C libft fclean

re: fclean all

norm:
	@norminette $(SRC)/*.c $(INCLUDES)
	@make norm -C ./libft/

memcheck: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./minishell

	
.PHONY: all clean fclean re norm memcheck
