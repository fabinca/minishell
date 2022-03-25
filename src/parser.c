/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:56:46 by cfabian           #+#    #+#             */
/*   Updated: 2022/03/25 20:33:43 by cfabian          ###   ########.fr       */
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

static int	redirection(t_command *cmd, t_list *token)
{
	if (ft_strcmp(token->content, ">") == 0)
	{
		token = token->next;
		cmd->fd_out = open(token->content, O_CREAT | O_TRUNC | O_RDWR, 0666);
	}
	if (ft_strcmp(token->content, ">>") == 0)
	{
		token = token->next;
		cmd->fd_out = open(token->content, O_CREAT | O_APPEND | O_RDWR, 0666);
	}
	if (ft_strcmp(token->content, "<") == 0)
	{
		token = token->next;
		cmd->fd_in = open(token->content, O_RDONLY);
	}
	if (ft_strcmp(token->content, "<<") == 0)
	{
		token = token->next;
		// but how to implement this ? 
		//<< should be given a delimiter, then read the input until a line containing the
		//delimiter is seen. However, it doesn’t have to update the history!
	}
	if (cmd->fd_in == -1 || cmd->fd_out == -1)
	{
		perror(token->content);
		return (0);
	}
	return (1);
}

t_command	*parser(t_list *token)
{
	t_command	*commands;
	t_command	*commands_first;

	commands_first = create_cmd_struct();
	commands = commands_first;
	while (token)
	{
		if (ft_strcmp(token->content, "|") == 0)
		{
			commands->next = create_cmd_struct();
			commands = commands->next;
		}
		else if (is_redirection_symbol(token->content))
		{
			redirection(commands, token);
			token = token->next;
		}
			
		else
		{
			if (commands->ct >= 10)
				commands->cmd = ft_realloc(commands->cmd, (commands->ct + 2) * sizeof(char *));
			commands->cmd[++commands->ct] = quotes_and_envvars(token->content, ft_strlen(token->content) + 1);
		}
		token = token->next;
	}
	return(commands_first);
}
