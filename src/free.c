/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 11:45:03 by hrothery          #+#    #+#             */
/*   Updated: 2022/05/06 12:09:37 by cfabian          ###   ########.fr       */
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
		if (tokens->content != NULL)
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
	free_cmd(cmd);
	free_var_list(lst);
	rl_clear_history();
	exit(0);
	return (0);
}
