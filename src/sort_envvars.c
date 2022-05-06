/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_envvars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 10:24:37 by hrothery          #+#    #+#             */
/*   Updated: 2022/05/06 09:37:29 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_envvar	*add_var_to_list(t_envvar *lst, t_envvar *new)
{
	t_envvar	*temp;
	t_envvar	*start;

	if (ft_strcmp(new->name, lst->name) <= 0)
	{
		start = new;
		new->next = lst;
		return (start);
	}
	start = lst;
	while (lst->next)
	{
		if (ft_strcmp(new->name, lst->next->name) > 0)
			lst = lst->next;
		else
			break ;
	}
	if (lst->next)
	{
		temp = lst->next;
		lst->next = new;
		new->next = temp;
	}
	else
		lst->next = new;
	return (start);
}

t_envvar	*duplicate_variable(t_envvar *lst, t_envvar *new)
{
	int			i;

	i = 0;
	new->name = malloc(sizeof(char) * (ft_strlen(lst->name) + 1));
	while (lst->name[i])
	{
		new->name[i] = lst->name[i];
		i++;
	}
	new->name[i] = '\0';
	new->content = malloc(sizeof(char) * (ft_strlen(lst->content) + 1));
	i = 0;
	while (lst->content[i])
	{
		new->content[i] = lst->content[i];
		i++;
	}
	new->content[i] = '\0';
	new->next = NULL;
	return (new);
}

t_envvar	*duplicate_list(t_envvar *lst)
{
	t_envvar	*new_list;
	t_envvar	*new;

	new = new_var(NULL);
	if (lst)
	{
		new = duplicate_variable(lst, new);
		new_list = new;
	}
	while (lst->next)
	{
		lst = lst->next;
		new = new_var(NULL);
		new = duplicate_variable(lst, new);
		new_list = add_var_to_list(new_list, new);
	}
	return (new_list);
}

void	print_export_no_args(t_envvar *lst, int fd)
{
	t_envvar	*export_lst;
	t_envvar	*start_export_lst;

	export_lst = duplicate_list(lst);
	start_export_lst = export_lst;
	while (export_lst->next)
	{
		if (ft_strcmp(export_lst->name, "_"))
		{
			ft_putstr_fd("declare -x ", fd);
			ft_putstr_fd(export_lst->name, fd);
			ft_putstr_fd("=\"", fd);
			ft_putstr_fd(export_lst->content, fd);
			ft_putstr_fd("\"\n", fd);
		}
		export_lst = export_lst->next;
	}
	if (ft_strcmp(export_lst->name, "_"))
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(export_lst->name, fd);
		ft_putstr_fd("=\"", fd);
		ft_putstr_fd(export_lst->content, fd);
		ft_putstr_fd("\"\n", fd);
	}
	free_var_list(start_export_lst);
}
