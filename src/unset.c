/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:45:38 by hrothery          #+#    #+#             */
/*   Updated: 2022/05/12 14:51:34 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	search_variable_to_delete(t_envvar *lst, char *s)
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

static int	check_valid_cmd(char *cmd, t_envvar *env_list, t_envvar *exp_list)
{
	int	exit_value;

	exit_value = 0;
	if (!is_alpha_numeric_underscore(cmd) || ft_strchr(cmd, '='))
	{
		printf("minishell: export: '%s': not a valid identifier\n", cmd);
		exit_value = 1;
	}
	else
	{
		search_variable_to_delete(env_list, cmd);
		search_variable_to_delete(exp_list, cmd);
	}
	return (exit_value);
}

int	builtin_unset(t_envvar *env_list, t_envvar *exp_list, char **cmd)
{
	int			i;

	i = 1;
	if (!cmd[i])
	{
		g_last_exit = 0;
		return (0);
	}
	while (cmd[i])
	{
		g_last_exit = check_valid_cmd(cmd[i], env_list, exp_list);
		i++;
	}
	return (0);
}
