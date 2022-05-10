/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 11:52:25 by hrothery          #+#    #+#             */
/*   Updated: 2022/05/10 09:54:42 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

//returns 1 if no builtin is found, 0 on success
int	parse_builtin(char **cmd, t_envvar *env_list)
{
	if (ft_strcmp(cmd[0], "echo") == 0)
		return (builtin_echo(cmd));
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		return (builtin_pwd());
	else if (ft_strcmp(cmd[0], "env") == 0)
		return (builtin_env(cmd, env_list));
	else if (ft_strcmp(cmd[0], "exit") == 0)
		return (builtin_exit(cmd, env_list));
	else if (ft_strcmp(cmd[0], "cd") == 0)
		return (builtin_cd(cmd));
	else if (ft_strcmp(cmd[0], "unset") == 0)
		return (builtin_unset(env_list, cmd));
	else if (ft_strcmp(cmd[0], "export") == 0)
		return (builtin_export(env_list, cmd));
	return (1);
}

void	display_prompt(void)
{
	char	*user;
	char	*dir;
	char	pwd[100];

	user = getenv("USER");
	dir = ft_strrchr(getcwd(pwd, 100), '/');
	printf("%s%s:%s~%s$%s ", GRN, user, BLU, dir, NRM);
}

void	sighandler(int num)
{
	if (num == SIGINT)
	{
		rl_replace_line("", 0);
		printf("\n");
		display_prompt();
		printf("\033[1;36m\033[1mMinishell\033[0m$ ");
		rl_redisplay();
	}
}

bool	redirect_and_piping(t_command *cmd_struct, t_pipedata p_data)
{
	if (!cmd_struct)
	{
		close(p_data.oldpipe[0]);
		close(p_data.oldpipe[1]);
		return (0);
	}
	if (pipe(p_data.newpipe) < 0)
		perror("pipe");
	if (p_data.ct == 0 && cmd_struct->next)
	{
		if (dup2(cmd_struct->fd_in, p_data.oldpipe[0]) < 0)
			perror("dup2 reading from fd_in");
		close(cmd_struct->fd_in);
	}
	return (1);
}

void	lex_parse_execute(char *line, t_envvar *env_list, char **envp)
{
	t_list		*lexer_tokens;
	t_command	*cmd_struct;
	t_command	*cmd_start;
	t_pipedata	p_data;

	if (is_only_whitespaces(line))
		return ;
	p_data.ct = 0;
	lexer_tokens = lexer(line);
	cmd_struct = parser(lexer_tokens);
	if (!cmd_struct) //do we need this? 
		return ;
	p_data.paths = find_paths(env_list);
	cmd_start = cmd_struct;
	pipe (p_data.oldpipe);
	pipex(p_data, envp, cmd_struct);
	unlink(".tmpheredoc");
	//while (cmd_start)
	//{
	//	cmd_struct = cmd_start->next;
	//	free_cmd_struct(cmd_start);
	//	cmd_start = cmd_struct;
	//}
	//free_tokens(lexer_tokens);
	//free_my_paths(p_data.paths);
}

int	main(int argc, char **argv, char **envp)
{
	char 		*line;
	t_envvar	*env_list;

	g_last_exit = 0;
	if (argc != 1 || argv[1])
	{
		printf("Run program with ./minishell (no arguments\n");
		return (0);
	}
	add_history("");
	signal(SIGINT, sighandler); //ctrl c
	signal(SIGQUIT, SIG_IGN); // ctrl backslash
	//signal(EOF, sighandler);
	env_list = init_envp_list(envp);
	while (1)
	{
		display_prompt();
		line = readline("\033[1;36m\033[1mMinishell\033[0m$ ");
		if (!line)
			break ;
		add_history(line);
		lex_parse_execute(line, env_list, envp);
		free(line);
	}
	free_var_list(env_list);
	printf("\n");
	return (0);
}

//test for heredoc
/* int	main(void)
{
	exe_heredoc("three");
	unlink(".tmpheredoc");
	return (0);
} */
