/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:37:21 by cfabian           #+#    #+#             */
/*   Updated: 2022/04/07 12:38:31 by hrothery         ###   ########.fr       */
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
	char				**cmd;
	struct s_command	*next;
}	t_command;

typedef struct s_shell
{
	t_envvar	**vars;
}	t_shell;

t_list	*lexer(char *line);

//free.c
void	free_cmd(char **cmd);
void	builtin_exit(char **cmd, t_envvar *lst);
void	free_var_list(t_envvar *lst);

//builtins.c
void	builtin_echo(char **token);
void	builtin_env(char **cmd, t_envvar *list);
void	builtin_pwd(void);
void	builtin_cd(char **cmd);

//builtins2.c
void	builtin_unset(t_envvar *lst, char **cmd);
void	builtin_export(t_envvar *lst, char **cmd);

//env_list.c
t_envvar	*init_envp_list(char **envp);
t_envvar	*init_var(t_envvar *var, char *envp);
int			search_env_list(t_envvar *lst, char *cmd);
t_envvar	*new_var(t_envvar *lst);


//heredoc.c
void	exe_heredoc(char *delimiter);

//sort_envvars.c
void	print_export_no_args(t_envvar *lst);


#endif
