/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:56:46 by cfabian           #+#    #+#             */
/*   Updated: 2022/05/17 17:30:17 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_command	*create_cmd_struct( void )
{
	t_command	*new;

	new = (t_command *)ft_calloc(1, sizeof(t_command));
	if (!new)
		return (NULL);
	new->fd_in = STDIN_FILENO;
	new->fd_out = STDOUT_FILENO;
	new->next = NULL;
	new->ct = -1;
	new->cmd = (char **)ft_calloc(10, sizeof(char *));
	return (new);
}

bool	is_builtin(char **cmd)
{
	if (!cmd || !cmd[0])
		return (0);
	if (ft_strcmp(cmd[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "env") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "export") == 0)
		return (1);
	return (0);
}

t_command	*look_for_builtin(t_command *cmd_first, t_command *cmd)
{
	t_command	*temp;

	if (!is_builtin(cmd->cmd))
		return (cmd_first);
	while (cmd_first != cmd)
	{
		temp = cmd_first;
		cmd_first = cmd_first->next;
		free_cmd_struct(temp);
		if (!cmd_first->next)
			break ;
	}
	return (cmd_first);
}

t_command	*hnd_cmd_s(t_command *c_s, char *s, t_command *first, t_envvar *env)
{
	if (c_s->ct >= 10)
		c_s->cmd = ft_realloc(c_s->cmd, (c_s->ct + 2) * sizeof(char *));
	c_s->cmd[++c_s->ct] = quotes_and_envvars(s, ft_strlen(s) + 1, env);
	//if (c_s->ct == 1)
	//	return (look_for_builtin(first, c_s));
	return (first);
}

t_command	*parser(t_list *t, t_envvar *e_lst)
{
	t_command	*c_s;
	t_command	*cmds_first;

	cmds_first = create_cmd_struct();
	c_s = cmds_first;
	while (t)
	{
		if (is_rdr(t->content) && rdr(c_s, t->next, is_rdr(t->content), e_lst))
		{
			free(t->content);
			t = t->next;
		}
			
		//else if (is_rdr(t->content))
		//{
		//	free_complete_struct(cmds_first);
		//	return (NULL);
		//}
		else if (ft_strcmp(t->content, "|") == 0)
		{
			c_s->next = create_cmd_struct();
			c_s = c_s->next;
		}
		else
			cmds_first = hnd_cmd_s(c_s, t->content, cmds_first, e_lst);
		t = t->next;
	}
	return (cmds_first);
}
