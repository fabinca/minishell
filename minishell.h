/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:37:21 by cfabian           #+#    #+#             */
/*   Updated: 2022/03/28 13:35:06 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define MAX_ENVVAR_LEN 128
# define MAX_TOKEN_LEN 256
# define GRN  "\x1B[1;32m"
# define BLU  "\x1B[1;34m"
# define NRM  "\x1B[0m"
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "./libft.h"
# include <stdbool.h>
# include <signal.h>
# include <fcntl.h>

extern int g_last_exit;
typedef struct s_envvar
{
	char			*name;
	char			*content;
	struct s_envvar	*next;
}	t_envvar;

typedef struct s_tok
{
	size_t	start;
	size_t	len;
	char	*string;
}	t_tok;

typedef struct s_command
{
	int					fd_in;
	int					fd_out;
	int					ct;
	char				**cmd;
	struct s_command	*next;
}	t_command;

typedef struct s_shell
{
	t_envvar	**vars;
}	t_shell;


//lexer.c
t_list		*lexer(char *line);
int			is_redirection_symbol(char *token_string);

//parser.c
t_command	*parser(t_list *token);

//quotes and envars
char		*quotes_and_envvars(char *string, size_t len);

//free.c
void		free_cmd(char **cmd);
void		builtin_exit(char **cmd);

//builtins.c
void		builtin_echo(char **token);
void		builtin_env(char **cmd, char **envp);
void		builtin_pwd(void);
void		builtin_cd(char **cmd);

#endif
