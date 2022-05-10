/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 11:45:03 by hrothery          #+#    #+#             */
/*   Updated: 2022/05/10 10:47:45 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_var_list(t_envvar *lst)
{
	t_envvar	*tmp;

	while (lst->next)
	{
		tmp = lst->next;
		free(lst->content);
		free(lst->name);
		free(lst);
		lst = tmp;
	}
	free(lst->content);
	free(lst->name);
	free(lst);
}

void	free_tokens(t_list *tokens)
{
	t_list	*tmp;

	if (!tokens)
		return ;
	while (tokens)
	{
		tmp = tokens->next;
		if (tokens->content)
			free(tokens->content);
		free(tokens);
		tokens = tmp;
	}
}

void	free_cmd_struct(t_command *cmd_struct)
{
	free(cmd_struct->cmd);
	free(cmd_struct);
	return ;
}

void	free_cmd(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		free(cmd[i++]);
	free (cmd);
}

int	builtin_exit(char **cmd, t_envvar *lst)
{
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
			ft_putstr_fd("minishell: exit: ", 1);
			ft_putstr_fd(cmd[1], 1);
			ft_putstr_fd(": numberic argument required\n", 1);
		}
		else
		{
			ft_putstr_fd("exit\n", 1);
			g_last_exit = ft_atoi_d_only(cmd[1]);
		}
	}
	free_cmd(cmd);
	free_var_list(lst);
	rl_clear_history();
	exit(g_last_exit);
	return (0);
}
