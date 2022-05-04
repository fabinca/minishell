/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:37:21 by cfabian           #+#    #+#             */
/*   Updated: 2022/05/04 11:46:55 by hrothery         ###   ########.fr       */
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

typedef struct s_pipedata
{
	int		newpipe[2];
	int		oldpipe[2];
	char	**paths;
	char	*c_p;
	int		error;
	pid_t	pid;
	int		ct;
}	t_pipedata;

typedef struct s_shell
{
	t_envvar	**vars;
}	t_shell;


//builtins.c
int			builtin_echo(char **token);
int			builtin_env(char **cmd, t_envvar *list);
int			builtin_pwd(void);
int			builtin_cd(char **cmd);

//builtins2.c
int			builtin_unset(t_envvar *lst, char **cmd);
int			builtin_export(t_envvar *lst, char **cmd);

//env_list.c
t_envvar	*init_envp_list(char **envp);
t_envvar	*init_var(t_envvar *var, char *envp);
int			search_env_list(t_envvar *lst, char *cmd);
t_envvar	*new_var(t_envvar *lst);

//exec_utils
void		free_my_paths(char **paths);
char		**find_paths(t_envvar *env_list);
char		*joined_path(char **my_paths, char *token);

//free.c
void		free_cmd(char **cmd);
void		free_cmd_struct(t_command *temp);
int			builtin_exit(char **cmd, t_envvar *lst);
void		free_var_list(t_envvar *lst);

//heredoc.c
void		exe_heredoc(char *delimiter);

//lexer.c
t_list		*lexer(char *line);
int			is_redirection_symbol(char *token_string);

//parser.c
t_command	*parser(t_list *token);

//quotes and envars
char		*quotes_and_envvars(char *string, size_t len);

//sort_envvars.c
void		print_export_no_args(t_envvar *lst);

#endif
