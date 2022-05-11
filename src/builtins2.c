/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 08:32:51 by hrothery          #+#    #+#             */
/*   Updated: 2022/05/11 13:45:20 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_alpha_numeric_underscore(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (!ft_isalpha(s[0]))
		return (0);
	while (s[i] && (s[i] == '_' || ft_isdigit(s[i]) || ft_isalpha(s[i])))
		i++;
	if (s[i] == '=' || !s[i])
		return (1);
	return (0);
}

bool	has_equal_sign(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

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

int	builtin_export(t_envvar *lst, char **cmd, int fd)
{
	int			i;

	i = 1;
	if (!cmd[i])
	{
		print_export_no_args(lst, fd);
		g_last_exit = 0;
		return (0);
	}
	while (cmd[i])
	{
		if (!is_alpha_numeric_underscore(cmd[i]))
		{
			g_last_exit = 1;
			printf("minishell: export: '%s': not a valid identifier\n", cmd[i]);
		}
		else
		{
			if (!search_env_list(lst, cmd[i]))
				add_envvar(lst, cmd[i]);
			g_last_exit = 0;
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
	{
		g_last_exit = 0;
		return (0);
	}
	while (cmd[i])
	{
		if (!is_alpha_numeric_underscore(cmd[i]) || has_equal_sign(cmd[i]))
			printf("minishell: export: '%s': not a valid identifier\n", cmd[i]);
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
	g_last_exit = 0;
	return (0);
}
