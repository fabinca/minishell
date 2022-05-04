# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/21 15:18:52 by cfabian           #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2022/05/04 06:38:53 by cfabian          ###   ########.fr        #
=======
#    Updated: 2022/05/02 08:01:27 by hrothery         ###   ########.fr        #
>>>>>>> main
#                                                                              #
# **************************************************************************** #

NAME		= 	minishell
SRC 		= 	src
SRCS 		= 	$(SRC)/parser.c \
				$(SRC)/lexer.c \
				$(SRC)/free.c \
				$(SRC)/quotes_and_envvars.c \
				$(SRC)/builtins.c \
<<<<<<< HEAD
				$(SRC)/file_descriptors.c \
				$(SRC)/main.c
=======
				$(SRC)/builtins2.c \
				$(SRC)/env_list.c \
				$(SRC)/heredoc.c \
				$(SRC)/sort_envvars.c \
				$(SRC)/parser.c \
				$(SRC)/quotes_and_envvars.c \
				$(SRC)/exec_utils.c \
>>>>>>> main
								
OBJ			= 	obj
OBJS		= 	$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
CC			= 	gcc
CFLAGS		= 	-Werror -Wall -Wextra
RM			= 	rm -f
LIB 		=	libft.a
INCLUDES	=	minishell.h libft.h

all: $(NAME)

$(OBJ)/%.o: $(SRC)/%.c $(OBJ)
	@$(CC) $(CFLAGS) -c $< -o $@ -g

$(OBJ):
	mkdir $(OBJ)

$(NAME): $(LIB) $(OBJS)
	@$(CC) -g -o $(NAME) $(OBJS) $(LIB) -lreadline

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
