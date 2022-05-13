/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 11:45:03 by hrothery          #+#    #+#             */
/*   Updated: 2022/05/13 14:26:52 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_var_list(t_envvar *lst)
{
	t_envvar	*tmp;

	while (lst->next)
	{
		tmp = lst->next;
		if (lst->content)
			free(lst->content);
		free(lst->name);
		free(lst);
		lst = tmp;
	}
	if (lst->content)
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
		free(tokens);
		tokens = tmp;
	}
}

void	free_cmd_struct(t_command *cmd_struct)
{
	if (!cmd_struct)
		return ;
	if (cmd_struct->fd_in > 0)
		close(cmd_struct->fd_in);
	if (cmd_struct->fd_out > 1)
		close(cmd_struct->fd_out);
	ft_double_free(cmd_struct->cmd);
	//free(cmd_struct);
	return ;
}

void	free_complete_struct(t_command *cmd_struct)
{
	t_command	*temp;

	while (cmd_struct)
	{
		temp = cmd_struct;
		free_cmd_struct(cmd_struct);
		cmd_struct = temp->next;
	}
}

void	free_cmd(char **cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	while (cmd[i])
		free(cmd[i++]);
	free (cmd);
}

void	free_everything(t_envvar *env_list, t_envvar *exp_list, t_command *cmd_struct)
{
	free_complete_struct(cmd_struct);
	free_var_list(env_list);
	free_var_list(exp_list);
	rl_clear_history();
}

