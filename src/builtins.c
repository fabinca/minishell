/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 11:47:22 by hrothery          #+#    #+#             */
/*   Updated: 2022/03/25 12:07:37 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_pwd(void)
{
	char	pwd[100];

	printf("%s\n", getcwd(pwd, 100));
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

void	builtin_cd(char **cmd)
{
	if (!cmd[1])
		return ;
	if (cmd[2])
	{
		printf("bash: cd: too many arguments\n");
		return ;
	}
	if (chdir(cmd[1]))
		printf("minishell: cd: %s: No such file or directory\n", cmd[1]);
	return ;
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
		j++;
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
