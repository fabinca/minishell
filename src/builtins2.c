/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 08:32:51 by hrothery          #+#    #+#             */
/*   Updated: 2022/05/12 12:59:30 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			ft_putstr_fd("minishell: export: '", 2);
			ft_putstr_fd(cmd[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
		}
		else
		{
			if (is_alpha_numeric_underscore(cmd[i]) != 2 && \
			!search_env_list(env_list, cmd[i]))
				add_envvar(env_list, cmd[i]);
			if (!search_exp_list(exp_list, cmd[i]))
				add_export_envvar(exp_list, cmd[i]);
			g_last_exit = 0;
		}
		i++;
	}
	return (0);
}

void	search_variable_to_delete(t_envvar *lst, char c, char *s)
{
	if (c == 'v')
	{
		if (!ft_strcmp(lst->name, s))
			del_var(lst, 1);
		else
		{
			while (lst->next)
			{
				if (ft_strcmp(lst->next->name, s) == 0)
				{
					del_var(lst, 0);
					break ;
				}
				lst = lst->next;
			}
		}
	}
	if (c == 'x')
	{
		if (!ft_strcmp(lst->name, s))
			del_var(lst, 1);
		else
		{
			while (lst->next)
			{
				if (!ft_strcmp(lst->next->name, s))
				{
					del_var(lst, 0);
					break ;
				}
				lst = lst->next;
			}
		}
	}
}

int	builtin_unset(t_envvar *env_list, t_envvar *exp_list, char **cmd)
{
	int			i;
	bool		exit_value;

	i = 1;
	exit_value = 0;
	if (!cmd[i])
	{
		g_last_exit = 0;
		return (0);
	}
	while (cmd[i])
	{
		if (!is_alpha_numeric_underscore(cmd[i]) || ft_strchr(cmd[i], '='))
		{
			printf("minishell: export: '%s': not a valid identifier\n", cmd[i]);
			exit_value = 1;
		}
		else
		{
			search_variable_to_delete(env_list, 'v', cmd[i]);
			search_variable_to_delete(exp_list, 'x', cmd[i]);
		}
		i++;
	}
	g_last_exit = exit_value;
	return (0);
}
