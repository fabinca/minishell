/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 08:32:51 by hrothery          #+#    #+#             */
/*   Updated: 2022/05/12 09:42:13 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_alpha_numeric_underscore(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (!ft_isalpha(s[0]))
		return (0);
	while (s[i] && (s[i] == '_' || ft_isdigit(s[i]) || ft_isalpha(s[i])))
		i++;
	if (s[i] == '=')
		return (1);
	if (!s[i])
		return (2); //will only be added to the export list not the env list
	return (0);
}

static void	add_export_envvar(t_envvar *lst, char *s)
{
	t_envvar	*new;

	while (lst->next)
		lst = lst->next;
	new = malloc(sizeof(t_envvar));
	if (!new)
		return ;
	lst->next = new;
	new = init_export_var(new, s);
}

static void	add_envvar(t_envvar *lst, char *s)
{
	t_envvar	*new;
	t_envvar	*temp;

	while (lst->next && ft_strcmp(lst->next->name, "_"))
		lst = lst->next;
	temp = lst->next;
	new = malloc(sizeof(t_envvar));
	if (!new)
		return ;
	lst->next = new;
	new = init_var(new, s);
	new->next = temp;
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
			printf("minishell: export: '%s': not a valid identifier\n", cmd[i]);
		}
		else
		{
			if (is_alpha_numeric_underscore(cmd[i]) != 2 && !search_env_list(env_list, cmd[i]))
				add_envvar(env_list, cmd[i]);
			if (!search_exp_list(exp_list, cmd[i]))
				add_export_envvar(exp_list, cmd[i]);
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
		if (lst->content)
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
	if (lst->next->content)
		free(lst->next->content);
	if (lst->next->next)
		lst->next = lst->next->next;
	else
		lst->next = NULL;
}

int	builtin_unset(t_envvar *env_list, t_envvar *exp_list, char **cmd)
{
	int	i;
	t_envvar	*lst;
	t_envvar	*export;

	i = 1;
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
			i++;
			break ;
		}
		lst = env_list;
		export = exp_list;
		if (!ft_strcmp(lst->name, cmd[i]))
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
		if (!ft_strcmp(export->name, cmd[i]))
			del_var(export, 1);
		else
		{
			while (export->next)
			{
				if (ft_strcmp(export->next->name, cmd[i]) == 0)
				{
					del_var(export, 0);
					break ;
				}
				export = export->next;
			}
		}
		i++;
	}
	g_last_exit = 0;
	return (0);
}
