/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 11:47:22 by hrothery          #+#    #+#             */
/*   Updated: 2022/05/10 10:14:16 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_pwd(int fd)
{
	char	pwd[100];
	if (!getcwd(pwd, 100))
	{
		perror("Unable to get current directory path");
		return (0);
	}
	ft_putstr_fd(pwd, fd);
	ft_putstr_fd("\n", fd);
	return (0);
}

int	builtin_env(t_command *cmd_struct, t_envvar *list)
{
	char	**cmd;
	int		fd;

	cmd = cmd_struct->cmd;
	fd = cmd_struct->fd_out;
	if (cmd[1])
	{
		printf("env: '%s': No such file or directory\n", cmd[1]);
		return (0);
	}
	while (list->next)
	{
		ft_putstr_fd(list->name, fd);
		ft_putstr_fd("=", fd);
		ft_putstr_fd(list->content, fd);
		ft_putstr_fd("\n", fd);
		list = list->next;
	}
	ft_putstr_fd(list->name, fd);
	ft_putstr_fd("=", fd);
	ft_putstr_fd(list->content, fd);
	ft_putstr_fd("\n", fd);
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

int	builtin_echo(t_command *cmd_struct)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (cmd_struct->cmd[i] == NULL)
	{
		ft_putstr_fd("\n", cmd_struct->fd_out);
		return (0);
	}
	while (is_newline(cmd_struct->cmd[i + j]))
	{
		j++;
		if (cmd_struct->cmd[i + j] == NULL)
			return (0);
	}
	while (cmd_struct->cmd[i + j] != NULL)
	{
		if (i != 1)
			ft_putstr_fd(" ", cmd_struct->fd_out);
		ft_putstr_fd(cmd_struct->cmd[i + j], cmd_struct->fd_out);
		i++;
	}
	if (j == 0)
		ft_putstr_fd("\n", cmd_struct->fd_out);
	return (0);
}

//returns 1 if no builtin is found, 0 on success
int	parse_builtin(t_command *cmd_struct, t_envvar *env_list)
{
	char **cmd;

	cmd = cmd_struct->cmd;
	if (ft_strcmp(cmd[0], "echo") == 0)
		return (builtin_echo(cmd_struct));
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		return (builtin_pwd(cmd_struct->fd_out));
	else if (ft_strcmp(cmd[0], "env") == 0)
		return (builtin_env(cmd_struct, env_list));
	else if (ft_strcmp(cmd[0], "exit") == 0)
		return (builtin_exit(cmd, env_list));
	else if (ft_strcmp(cmd[0], "cd") == 0)
		return (builtin_cd(cmd));
	else if (ft_strcmp(cmd[0], "unset") == 0)
		return (builtin_unset(env_list, cmd));
	else if (ft_strcmp(cmd[0], "export") == 0)
		return (builtin_export(env_list, cmd, cmd_struct->fd_out));
	return (1);
}
