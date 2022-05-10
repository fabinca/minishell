/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 11:47:22 by hrothery          #+#    #+#             */
/*   Updated: 2022/05/10 14:20:24 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

char *ft_get_envvar(t_envvar *env_list, char *s)
{
	while (env_list)
	{
		if (!ft_strcmp(env_list->name, s))
			return (env_list->content);
		env_list = env_list->next;
	}
	return (0);
}

int	builtin_pwd(int fd)
{
	char	pwd[100];
	if (!getcwd(pwd, 100))
	{
		perror("Unable to get current directory path");
		g_last_exit = 127;
		return (0);
	}
	ft_putstr_fd(pwd, fd);
	ft_putstr_fd("\n", fd);
	//printf("%s\n", pwd);
	g_last_exit = 0;
	return (0);
}

int	builtin_env(char **cmd, int fd, t_envvar *list)
{
	if (cmd[1])
	{
		g_last_exit = 127;
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
	g_last_exit = 0;
	return (0);
}

int	builtin_cd(char **cmd, t_envvar *env_list)
{
	if (!cmd[1])
	{
		chdir(ft_get_envvar(env_list, "HOME"));
		g_last_exit = 0;
		return (0);
	}
	if (cmd[2])
	{
		ft_putstr_fd("minishell: cd: string not in pwd: ", 1);
		ft_putstr_fd(cmd[1], 1);
		ft_putstr_fd("\n", 2);
		g_last_exit = 1;
		return (0);
	}
	if (chdir(cmd[1]))
	{
		ft_putstr_fd("minishell: cd: no such file or directory: ", 1);
		ft_putstr_fd(cmd[1], 1);
		ft_putstr_fd("\n", 1);
		g_last_exit = 1;
	}
	else
		g_last_exit = 0;
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

int	builtin_echo(char **cmd, int fd_out)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	g_last_exit = 0;
	if (cmd[i] == NULL)
	{
		ft_putstr_fd("\n", fd_out);
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
			ft_putstr_fd(" ", fd_out);
		ft_putstr_fd(cmd[i + j], fd_out);
		i++;
	}
	if (j == 0)
		ft_putstr_fd("\n", fd_out);
	return (0);
}

//returns 1 if no builtin is found, 0 on success
int	parse_builtin(t_command *cmd_struct, t_envvar *env_list)
{
	char **cmd;
	int	fd_out;

	cmd = cmd_struct->cmd;
	if (cmd_struct->next)
		fd_out = 1;
	else
		fd_out = cmd_struct->fd_out;
	if (ft_strcmp(cmd[0], "echo") == 0)
		return (builtin_echo(cmd, fd_out));
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		return (builtin_pwd(fd_out));
	else if (ft_strcmp(cmd[0], "env") == 0)
		return (builtin_env(cmd, fd_out, env_list));
	else if (ft_strcmp(cmd[0], "exit") == 0)
		return (builtin_exit(cmd, env_list));
	else if (ft_strcmp(cmd[0], "cd") == 0)
		return (builtin_cd(cmd, env_list));
	else if (ft_strcmp(cmd[0], "unset") == 0)
		return (builtin_unset(env_list, cmd));
	else if (ft_strcmp(cmd[0], "export") == 0)
		return (builtin_export(env_list, cmd, fd_out));
	return (1);
}
