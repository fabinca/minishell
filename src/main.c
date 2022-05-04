/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 11:52:25 by hrothery          #+#    #+#             */
/*   Updated: 2022/05/04 08:58:54 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

void	parse_builtin(char *line, char **envp)
{
	char	**cmd;

	cmd = ft_split(line, ' ');
	if (ft_strcmp(cmd[0], "echo") == 0)
		builtin_echo(cmd);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		builtin_pwd();
	else if (ft_strcmp(cmd[0], "env") == 0)
		builtin_env(cmd, envp);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		builtin_exit(cmd);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		builtin_cd(cmd);
	else
		printf("%s: command not found\n", cmd[0]);
	free_cmd(cmd);
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

bool	redirect_and_piping(t_command *pipe_struct, t_pipedata p_data)
{
	if (!pipe_struct)
	{
		close(p_data.oldpipe[0]);
		close(p_data.oldpipe[1]);
		return (0);
	}
	if (pipe(p_data.newpipe) < 0)
		perror("pipe");
	if (p_data.ct == 0)
	{
		if (dup2(pipe_struct->fd_in, p_data.oldpipe[0]) < 0)
			perror("dup2 reading from fd_in");
		close(pipe_struct->fd_in);
	}
	if (!pipe_struct)
	{
		close(p_data.oldpipe[0]);
		close(p_data.oldpipe[1]);
		return (0);
	}
	if (pipe(p_data.newpipe) < 0)
		perror("pipe");
	return (1);
}

void	lex_parse_execute(char *line)
{
	t_list		*lexer_tokens;
	t_command	*pipe_struct;
	t_command	*buf;
	t_pipedata	p_data;

	p_data.ct = 0;
	lexer_tokens = lexer(line);
	pipe_struct = parser(lexer_tokens);
	//p_data.paths = 
	while (p_data.ct++ > -1)
	{
		if (!redirect_and_piping(pipe_struct, p_data))
			break ;
		//check for buildtins & exec them
		//normal commands
		pipe_struct = pipe_struct->next;
	}
	//free everything
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	g_last_exit = 0;
	if (argc != 1 || argv[1])
	{
		printf("Run program with ./minishell (no arguments\n");
		return (0);
	}
	add_history("");
	signal(SIGINT, sighandler); //ctrl c
	signal(SIGQUIT, SIG_IGN); // ctrl backslash
	//init envvars
	while (1)
	{
		display_prompt();
		line = readline("\033[1;36m\033[1mMinishell\033[0m$ ");
		if (!line)
			break ;
		add_history(line);
		lex_parse_execute(line);
		free(line);
	}
	//free memory
	printf("\n");
	return (0);
}
