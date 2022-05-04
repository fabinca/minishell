/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 08:32:51 by hrothery          #+#    #+#             */
/*   Updated: 2022/05/04 09:56:22 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	add_envvar(t_envvar *lst, char *s)
{
	t_envvar	*new;

	while (lst->next)
		lst = lst->next;
	new = malloc(sizeof(t_envvar));
	if (!new)
		return ;
	lst->next = new;
	new = init_var(new, s);
}

int	builtin_export(t_envvar *lst, char **cmd)
{
	int			i;

	i = 1;
	if (!cmd[i])
	{
		print_export_no_args(lst);
		return (0);
	}
	while (cmd[i])
	{
		if (cmd[i][0] == '=')
			printf("minishell: export: '%s': not a valid identifier\n", cmd[i]);
		else
		{
			if (ft_strchr(cmd[i], '='))
			{
				if (!search_env_list(lst, cmd[i]))
					add_envvar(lst, cmd[i]);
			}
		}
		i++;
	}
	return (0);
}

static void	del_var(t_envvar *lst, int first)
{
	if (first == 1)
	{
		if (!lst)
			return ;
		free(lst->name);
		free(lst->content);
		if (lst->next)
			lst = lst->next;
		else
			lst->next = NULL;
		return ;
	}
	if (!lst->next)
		return ;
	free(lst->next->name);
	free(lst->next->content);
	if (lst->next->next)
		lst->next = lst->next->next;
	else
		lst->next = NULL;
}

int	builtin_unset(t_envvar *start, char **cmd)
{
	int	i;
	t_envvar	*lst;

	i = 1;
	if (!cmd[i])
		return (0);
	while (cmd[i])
	{
		lst = start;
		if (ft_strcmp(lst->name, cmd[i]) == 0)
			del_var(lst, 1);
		else
		{
			while (lst->next)
			{
				if (ft_strcmp(lst->next->name, cmd[i]) == 0)
				{
					del_var(lst, 0);
					break ;
				}
				lst = lst->next;
			}
		}
		i++;
	}
	return (0);
}