# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/21 15:18:52 by cfabian           #+#    #+#              #
#    Updated: 2022/05/04 12:25:34 by hrothery         ###   ########.fr        #
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
				$(SRC)/quotes_and_envvars.c \
				$(SRC)/sort_envvars.c
								
OBJ			= 	obj
OBJS		= 	$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
CC			= 	gcc
CFLAGS		= 	-I $(HOME)/goinfre/.brew/opt/readline/include/ #-Wall -Werror -Wextra 
RM			= 	rm -f
LIB 		=	libft.a
INCLUDES	=	minishell.h libft.h

all: $(NAME)

$(OBJ)/%.o: $(SRC)/%.c $(OBJ)
	@$(CC) $(CFLAGS) -c $< -o $@ -g

$(OBJ):
	mkdir $(OBJ)

$(NAME): $(LIB) $(OBJS)
	$(CC) -lreadline -L $(HOME)/goinfre/.brew/opt/readline/lib/ $(CFLAGS) $(SRCS) $(LIB) -g  -o $(NAME)

$(LIB):
	@make -C ./libft/
	mv ./libft/$(LIB) ./$(LIB)
	cp ./libft/libft.h ./libft.h

clean:
	$(RM) $(OBJ)/*

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
