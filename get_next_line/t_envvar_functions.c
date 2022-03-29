/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_envvar_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 15:40:13 by hrothery          #+#    #+#             */
/*   Updated: 2022/03/29 17:57:47 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		s1++;
		s2++;
	}
	if (*s1 && !*s2)
		return (*(unsigned char *)s1);
	if (*s2 && !*s1)
		return (*(unsigned char *)s2 * -1);
	return (0);
}

typedef struct s_envvar
{
	char			*name;
	char			*content;
	struct s_envvar	*next;
}		t_envvar;

t_envvar	*add_envvar(t_envvar *lst)
{
	t_envvar	*new;

	new = malloc(sizeof(t_envvar));
	if (!new)
		return (0);
	if (lst)
		lst->next = new;
	return (new);
}

t_envvar	*init_var(t_envvar *var, char *envp)
{
	int	i;
	int	len;

	len = 0;
	while (envp[len] && envp[len] != '=')
		len++;
	i = len + 1;
	var->name = malloc(sizeof(char) * (len + 1));
	var->content = malloc(sizeof(char) * (ft_strlen(envp) - len));
	if (!var->name || !var->content)
		return (0);
	var->name[len] = '\0';
	while (len-- >= 0)
		var->name[len] = envp[len];
	len = 0;
	while (envp[i])
		var->content[len++] = envp[i++];
	var->content[len] = '\0';
	var->next = NULL;
	return (var);
}

t_envvar	*init_envp_list(char **envp)
{
	t_envvar	*start;
	t_envvar	*new;
	t_envvar	*var;
	int			i;

	i = 0;
	start = NULL;
	var = add_envvar(NULL);
	var = init_var(var, envp[i++]);
	start = var;
	while (envp[i])
	{
		new = add_envvar(var);
		new = init_var(new, envp[i++]);
		var = new;
	}
	return (start);
}

void	add_envar(t_envvar *lst, char *s) //use for export cmd
{
	t_envvar	*new;
	
	while (lst->next)
		lst = lst->next;
	new = add_envvar(lst);
	new = init_var(new, s);
}

void	del_first_var(t_envvar *lst)
{
	if (!lst)
		return ;
	free(lst->name);
	free(lst->content);
	if (lst->next)
		lst = lst->next;
	else
		lst->next = NULL;
}

void	del_next_var(t_envvar *lst)
{
	if (!lst->next)
		return ;
	free(lst->next->name);
	free(lst->next->content);
	if (lst->next->next)
		lst->next = lst->next->next;
	else
		lst->next = NULL;
}

void	unset(t_envvar *lst, char *s)
{
	if (ft_strcmp(lst->name,s) == 0)
	{
		del_first_var(lst);
		return ;
	}
	else
	{
		while (lst->next)
		{
			if (ft_strcmp(lst->next->name, s) == 0)
			{
				del_next_var(lst);
				return ;
			}
			lst = lst->next;
		}
		printf("variable %s not found", s);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_envvar	*list;
	
	if (argc != 1 || argv[1])
	{
		printf("wrong number of arguments\n");
		return (1);
	}
	list = init_envp_list(envp);
	add_envar(list, "you=win");
	unset(list, "you");
	unset(list, "HOSTTYPE");
	while (list->next)
	{
		printf("%s=%s\n", list->name, list->content);
		list = list->next;
	}
	printf("%s=%s\n", list->name, list->content);
	return (0);
}

