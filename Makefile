# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/21 15:18:52 by cfabian           #+#    #+#              #
#    Updated: 2022/03/25 12:00:20 by hrothery         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= 	minishell
SRC 		= 	src
SRCS 		= 	$(SRC)/main.c \
				$(SRC)/lexer.c \
				$(SRC)/free.c \
				$(SRC)/builtins.c \
								
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
