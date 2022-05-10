/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 08:42:52 by cfabian           #+#    #+#             */
/*   Updated: 2022/05/10 22:58:24 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	parent_process(t_pipedata pdata) //, pid_t pid
{
	close(pdata.oldpipe[0]);
	close(pdata.oldpipe[1]);
	waitpid(pdata.pid, &g_last_exit, 0);
	dup2(pdata.newpipe[0], pdata.oldpipe[0]);
	close(pdata.newpipe[0]);
	dup2(pdata.newpipe[1], pdata.oldpipe[1]);
	close(pdata.newpipe[1]);
}

static void	child_process(t_pipedata pdata, char **envp, t_command *cmd_struct)
{
	char	*path;

	if (dup2(pdata.oldpipe[0], STDIN_FILENO) < 0)
		perror("dup2 replacing stdin");
	close(pdata.oldpipe[0]);
	if (cmd_struct->fd_in != 0)
	{
		dup2(cmd_struct->fd_in, STDIN_FILENO);
		close(cmd_struct->fd_in);
	}
	if (!cmd_struct->next || cmd_struct->fd_out != 1)
	{
		if (dup2(cmd_struct->fd_out, pdata.newpipe[1]) < 0)
			perror("dup2 printing to fd_out");
		close(cmd_struct->fd_out);
	}
	if (dup2(pdata.newpipe[1], STDOUT_FILENO) < 0)
		perror("dup2 replacing stdout");
	close(pdata.newpipe[1]);
	close(pdata.newpipe[0]);
	close(pdata.oldpipe[1]);
	if (is_builtin(cmd_struct->cmd))
		parse_builtin(cmd_struct, pdata.envlist);
	else
	{
		path = joined_path(pdata.paths, cmd_struct->cmd[0]);
		if (path)
			execve(path, cmd_struct->cmd, envp);
		else
		{
			//ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd_struct->cmd[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			//free_t_data(dt);
			exit(127); //Does not exit as 127! 
		}
	}
		//free_t_data(dt);
	exit(0);
}

int	pipex(t_pipedata pdata, char **envp, t_command *cmd_struct)
{
	if (!cmd_struct)
	{
		close(pdata.oldpipe[0]);
		close(pdata.oldpipe[1]);
		return (0);
	}
	if (pipe(pdata.newpipe) < 0)
		perror("pipe");
	pdata.pid = fork();
	if (pdata.pid < 0)
		perror("Fork");
	else if (pdata.pid == 0)
		child_process(pdata, envp, cmd_struct);
	else
	{
		parent_process(pdata); // pid
		pipex(pdata, envp, cmd_struct->next);
	}
	return (0);
}
