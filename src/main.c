/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 11:52:25 by hrothery          #+#    #+#             */
/*   Updated: 2022/03/28 13:35:27 by cfabian          ###   ########.fr       */
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
	while (1)
	{
		display_prompt();
		line = readline("\033[1;36m\033[1mMinishell\033[0m$ ");
		if (!line)
			break ;
		add_history(line);
		if (line[0])
			parse_builtin(line, envp);
		free(line);
	}
	//free memory
	printf("\n");
	return (0);
}
