/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:54:42 by hrothery          #+#    #+#             */
/*   Updated: 2022/03/21 13:56:14 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//strcmp is not in the libft


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"


char	**ft_split(char const *s, char c);


int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		s1++;
		s2++;
	}
	if (*s1 && !*s2)
		return (*(unsigned char *)s1);
	if (*s2 && !*s1)
		return (*(unsigned char *)s2 * -1);
	return (0);
}

void	builtin_env(char **cmd, char **envp)
{
	int	i;

	if (cmd[1])
	{
		printf("env: '%s': No such file or directory\n", cmd[1]);
		return ;
	}
	i = 0;
	while (envp[i])
		printf("%s\n", envp[i++]);
}

void	builtin_pwd(void)
{
	printf("%s\n", getenv("PWD"));
}

void	builtin_echo(char **token)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (token[i] == NULL)
	{
		printf("\n");
		return ;
	}
	if (ft_strcmp(token[i], "-n") == 0)
	{
		j++; //start the echo at the token after "-n"
		if (token[i + 1] == NULL)
			return ;
	}
	while (token[i + j] != NULL)
	{
		if (i != 1)
			printf(" ");
		printf("%s", token[i + j]);
		i++;
	}
	if (j == 0)
		printf("\n");
}

void	builtin_exit(char **cmd, int *exit_status)
{
	if (cmd[1])
		printf("exit: '%s': No such file or directory\n", cmd[1]); //!!!couldn't read so fast to get the actual error msg!!!
	//how can I clear the screen or close the terminal screen?
	(*exit_status)++;
}

void	parse_builtin(char *line, char **envp, int *exit_status)
{
	char **cmd;

	cmd = ft_split(line, ' ');
	if (ft_strcmp(cmd[0], "echo") == 0)
		builtin_echo(cmd);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		builtin_pwd();
	else if (ft_strcmp(cmd[0], "env") == 0)
		builtin_env(cmd, envp);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		builtin_exit(cmd, exit_status);
	else
		printf("%s: command not found\n", cmd[0]);
}

/* int	main(int argc, char **argv)
{
	if (argc < 2)
		return (0);
	parse_builtin(line);
	return (0);
} */