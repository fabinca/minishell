/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:37:21 by cfabian           #+#    #+#             */
/*   Updated: 2022/05/13 16:08:44 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define MAX_ENVVAR_LEN 128
# define MAX_TOKEN_LEN 1256 //I increased this because my path doesn't fit in the parser
# define GRN  "\x1B[1;32m"
# define BLU  "\x1B[1;34m"
# define NRM  "\x1B[0m"
# define BUFFER_SIZE 40
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
# include <sys/types.h>
# include <sys/wait.h>

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
	int			newpipe[2];
	int			oldpipe[2];
	char		**paths;
	char		*c_p;
	bool		first_cmd;
	pid_t		pid;
	t_envvar	*envlist;
}	t_pipedata;

//builtin_utils.c
char		*ft_get_envvar(t_envvar *env_list, char *s);
int			is_alpha_numeric_underscore(char *s);
void		del_var(t_envvar *lst, int first);
void		add_export_envvar(t_envvar *lst, char *s);
void		add_envvar(t_envvar *lst, char *s);

//builtins.c
int			builtin_echo(char **cmd, int fd);
int			builtin_env(char **cmd_struct, int fd, t_envvar *list);
int			builtin_pwd(int fd);
int			builtin_cd(char **cmd, t_envvar *env_list);
char		*ft_get_envvar(t_envvar *env_list, char *s);

//builtins2.c
int			builtin_unset(t_envvar *lst, t_envvar *exp_list, char **cmd);
int			builtin_export(t_envvar *lst, t_envvar *export_list, char **cmd, int fd);
int			parse_builtin(t_command *cmd_struct, t_envvar *env_list, t_envvar *export_list);
bool		is_builtin(char **cmd);

//env_list.c
t_envvar	*init_envp_list(char **envp);
t_envvar	*init_var(t_envvar *var, char *envp);
t_envvar	*init_export_var(t_envvar *var, char *envp);
int			search_env_list(t_envvar *lst, char *cmd);
int			search_exp_list(t_envvar *lst, char *cmd);
t_envvar	*new_var(t_envvar *lst);

//error_msg.c
void	print_error(char *str1, char *str2, char *str3, char *str4);

//execute.c
int			exec_cmd(t_command *cmd_struct, t_envvar *env_list, char **envp);

//exec_utils
int			exec_cmd(t_command *cmd_struct, t_envvar *env_list, char **envp);
void		free_my_paths(char **paths);
char		**find_paths(t_envvar *env_list);
char		*joined_path(char **my_paths, char *token);

//export_list.c


//free.c
void		free_cmd(char **cmd);
void		free_complete_struct(t_command *cmd_struct);
void		free_tokens(t_list *tokens);
void		free_cmd_struct(t_command *temp);
int			builtin_exit(t_command *cmd_struct, t_envvar *env_lst, t_envvar *exp_lst);
void		free_var_list(t_envvar *lst);
void		free_everything(t_envvar *env_list, t_envvar *exp_list, t_command *cmd_struct);


//get_next_line_delimit
char		*gnl_delimit(int fd, char *delimiter);
char		*ft_strjoin_gnl(char *s1, char*s2);

//heredoc.c
void		exe_heredoc(char *delimiter, t_envvar *env_list);

//lexer.c
t_list		*lexer(char *line);
int			is_redirection_symbol(char *token_string);

//list_to_string.c
char		**ft_listtostr(t_envvar *env_list);
void		ft_double_free(char **s);

//main.c
//int			parse_builtin(t_command *cmd_struct, t_envvar *env_list);
//parser.c
t_command	*parser(t_list *token, t_envvar *env_list);
bool		is_builtin(char **cmd);

//piping.c
int			pipex(t_pipedata pdata, t_envvar *env_list, \
t_envvar	*exp_list, t_command *cmd_struct);

//quotes and envars
char		*quotes_and_envvars(char *string, size_t len, t_envvar *env_list);

//signals.c
void		sighandler(int num);
void		sighandler_child(int num);
void		display_prompt(void);

//sort_envvars.c
void		print_export_no_args(t_envvar *lst, int fd);
t_envvar	*duplicate_list(t_envvar *lst);
t_envvar	*add_var_to_list(t_envvar *lst, t_envvar *new);

#endif
