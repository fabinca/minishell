/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 11:47:22 by hrothery          #+#    #+#             */
/*   Updated: 2022/05/04 09:55:28 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_pwd(void)
{
	char	pwd[100];

	if (!getcwd(pwd, 100))
	{
		perror("Unable to get current directory path");
		return (0);
	}
	printf("%s\n", pwd);
	return (0);
}

int	builtin_env(char **cmd, t_envvar *list)
{
	if (cmd[1])
	{
		printf("env: '%s': No such file or directory\n", cmd[1]);
		return (0);
	}
	while (list->next)
	{
		printf("%s=%s\n", list->name, list->content);
		list = list->next;
	}
	printf("%s=%s\n", list->name, list->content);
	return (0);
}

int	builtin_cd(char **cmd)
{
	if (!cmd[1])
	{
		chdir(getenv("HOME"));
		return (0);
	}
	if (cmd[2])
	{
		printf("bash: cd: too many arguments\n");
		return (0);
	}
	if (chdir(cmd[1]))
		printf("minishell: cd: %s: No such file or directory\n", cmd[1]);
	return (0);
}

static int	is_newline(char *s)
{
	int	i;

	if (s[0] != '-')
		return (0);
	i = 1;
	while (s[i] == 'n')
		i++;
	if (s[i] == '\0')
		return (1);
	return (0);
}

int	builtin_echo(char **cmd)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (cmd[i] == NULL)
	{
		printf("\n");
		return (0);
	}
	while (is_newline(cmd[i + j]))
	{
		j++;
		if (cmd[i + j] == NULL)
			return (0);
	}
	while (cmd[i + j] != NULL)
	{
		if (i != 1)
			printf(" ");
		printf("%s", cmd[i + j]);
		i++;
	}
	if (j == 0)
		printf("\n");
	return (0);
}
