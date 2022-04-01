/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 11:52:25 by hrothery          #+#    #+#             */
/*   Updated: 2022/04/01 15:04:54 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

void	parse_builtin(char *line, t_envvar *env_list)
{
	char	**cmd;

	cmd = ft_split(line, ' ');
	if (cmd[0] == NULL)
		return ;
	if (ft_strcmp(cmd[0], "echo") == 0)
		builtin_echo(cmd);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		builtin_pwd();
	else if (ft_strcmp(cmd[0], "env") == 0)
		builtin_env(cmd, env_list);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		builtin_exit(cmd);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		builtin_cd(cmd);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		builtin_unset(env_list, cmd);
	else if (ft_strcmp(cmd[0], "export") == 0)
		builtin_export(env_list, cmd);
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
	char 		*line;
	t_envvar	*env_list;

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
		parse_builtin(line, env_list);
		free(line);
	}
	//free memory
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
