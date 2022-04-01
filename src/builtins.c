/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 11:47:22 by hrothery          #+#    #+#             */
/*   Updated: 2022/04/01 10:50:54 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_pwd(void)
{
	char	pwd[100];

	printf("%s\n", getcwd(pwd, 100));
}

void	builtin_env(char **cmd, t_envvar *list)
{

	if (cmd[1])
	{
		printf("env: '%s': No such file or directory\n", cmd[1]);
		return ;
	}
	while (list->next)
	{
		printf("%s=%s\n", list->name, list->content);
		list = list->next;
	}
	printf("%s=%s\n", list->name, list->content);
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

void	builtin_echo(char **cmd)
{
	int	i;
	int	j;
	char	*envvar;

	i = 1;
	j = 0;
	if (cmd[i] == NULL)
	{
		printf("\n");
		return ;
	}
	if (ft_strcmp(cmd[i], "-n") == 0)
	{
		j++;
		if (cmd[i + 1] == NULL)
			return ;
	}
	while (cmd[i + j] != NULL)
	{
		if (i != 1)
			printf(" ");
		if (cmd[i + j][0] == '$')
		{
			envvar = getenv(&cmd[i + j][1]);
			if (envvar)
				printf("%s", envvar);
		}
		else
			printf("%s", cmd[i + j]);
		i++;
	}
	if (j == 0)
		printf("\n");
}
