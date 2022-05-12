/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 08:32:51 by hrothery          #+#    #+#             */
/*   Updated: 2022/05/12 14:45:32 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_export_error(char *cmd)
{
	ft_putstr_fd("minishell: export: '", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}

static void	export_variable(char *cmd, t_envvar *env_list, t_envvar *exp_list)
{
	if (is_alpha_numeric_underscore(cmd) != 2 && \
	!search_env_list(env_list, cmd))
		add_envvar(env_list, cmd);
	if (!search_exp_list(exp_list, cmd))
		add_export_envvar(exp_list, cmd);
}

int	builtin_export(t_envvar *env_list, t_envvar *exp_list, char **cmd, int fd)
{
	int			i;

	i = 1;
	if (!cmd[i])
	{
		print_export_no_args(exp_list, fd);
		g_last_exit = 0;
		return (0);
	}
	while (cmd[i])
	{
		if (!is_alpha_numeric_underscore(cmd[i]))
		{
			g_last_exit = 1;
			print_export_error(cmd[i]);
		}
		else
		{
			export_variable(cmd[i], env_list, exp_list);
			g_last_exit = 0;
		}
		i++;
	}
	return (0);
}
