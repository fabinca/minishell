/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:56:46 by cfabian           #+#    #+#             */
/*   Updated: 2022/05/11 15:13:13 by hrothery         ###   ########.fr       */
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
		if (cmd->fd_out > 1)
			close(cmd->fd_out);
		token = token->next;
		cmd->fd_out = open(token->content, O_CREAT | O_TRUNC | O_RDWR, 0666);
	}
	else if (ft_strcmp(token->content, ">>") == 0)
	{
		token = token->next;
		if (cmd->fd_out > 1)
			close(cmd->fd_out);
		cmd->fd_out = open(token->content, O_CREAT | O_APPEND | O_RDWR, 0666);
	}
	if (cmd->fd_out == -1)
	{
		perror(token->content);
		return (0);
	}
	if (ft_strcmp(token->content, "<") == 0)
	{
		if (cmd->fd_in > 0)
			close(cmd->fd_in);
		token = token->next;
		cmd->fd_in = open(token->content, O_RDONLY);
	}
	else if (ft_strcmp(token->content, "<<") == 0)
	{
		token = token->next;
		exe_heredoc(token->content);
		if (cmd->fd_in > 0)
			close(cmd->fd_in);
		cmd->fd_in = open(".tmpheredoc", O_RDONLY);
		unlink(".tmpheredoc");
		if (g_last_exit == 1)
			return (0);
	}
	if (cmd->fd_in == -1)
	{
		perror(token->content);
		return (0);
	}
	printf("fdin: %d  fdout: %d \n", cmd->fd_in, cmd->fd_out);
	return (1);
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

t_command	*parser(t_list *token, t_envvar *env_list)
{
	t_command	*commands;
	t_command	*commands_first;

	if (!token)
		return (NULL);
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
			if (!redirection(commands, token))
			{
				//free_data
				return (NULL);
			}
			token = token->next;
		}
		else
		{
			if (commands->ct >= 10)
				commands->cmd = ft_realloc(commands->cmd, (commands->ct + 2) * sizeof(char *));
			commands->cmd[++commands->ct] = quotes_and_envvars(token->content, ft_strlen(token->content) + 1, env_list);
			if (commands->ct == 1)
				commands_first = look_for_builtin(commands_first, commands);
		}
		token = token->next; //is it ok? 
	}
	//printf("%s\n", commands_first->cmd[0]);
	return(commands_first);
}
