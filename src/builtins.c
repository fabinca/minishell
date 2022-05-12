/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 11:47:22 by hrothery          #+#    #+#             */
/*   Updated: 2022/05/12 14:38:57 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_pwd(int fd)
{
	char	pwd[100];

	if (!getcwd(pwd, 100))
	{
		perror("pwd");
		g_last_exit = 127;
		return (0);
	}
	ft_putstr_fd(pwd, fd);
	ft_putstr_fd("\n", fd);
	g_last_exit = 0;
	return (0);
}

int	builtin_env(char **cmd, int fd, t_envvar *list)
{
	if (cmd[1])
	{
		g_last_exit = 127;
		ft_putstr_fd("env: '", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putendl_fd("': No such file or directory", 2);
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
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		g_last_exit = 1;
		return (0);
	}
	if (chdir(cmd[1]))
	{
		ft_putstr_fd("minishell: cd: no such file or directory: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd("\n", 2);
		g_last_exit = 1;
	}
	else
		g_last_exit = 0;
	return (0);
}

int	builtin_exit(t_command *cmd_struct, t_envvar *env_lst, t_envvar *exp_list)
{
	char	**cmd;

	cmd = cmd_struct->cmd;
	if (!cmd[1])
	{
		ft_putstr_fd("exit\n", 1);
		g_last_exit = 0;
	}
	else
	{
		if (!ft_atoi_d_only(cmd[1]))
		{
			g_last_exit = 255;
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(cmd[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
		}
		else
		{
			ft_putstr_fd("exit\n", 1);
			g_last_exit = ft_atoi_d_only(cmd[1]);
		}
	}
	free_everything(env_lst, exp_list, cmd_struct);
	exit(g_last_exit);
	return (0);
}
