/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 08:42:52 by cfabian           #+#    #+#             */
/*   Updated: 2022/05/10 09:56:05 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	parent_process(t_pipedata pdata) //, pid_t pid
{
	close(pdata.oldpipe[0]);
	close(pdata.oldpipe[1]);
	waitpid(pdata.pid, NULL, 0);
	dup2(pdata.newpipe[0], pdata.oldpipe[0]);
	close(pdata.oldpipe[1]);
	close(pdata.newpipe[1]);
}

static void	child_process(t_pipedata pdata, char **envp, t_command *cmd_struct)
{
	char	*path;

	if (cmd_struct->fd_in != 0)
	{
		if (dup2(cmd_struct->fd_in, pdata.oldpipe[0]) < 0)
			perror("dup2 reading from fd_in");
		close(cmd_struct->fd_in);
	}
	if (dup2(pdata.oldpipe[0], STDIN_FILENO) < 0)
		perror("dup2 replacing stdin");
	close(pdata.oldpipe[0]);
	if (cmd_struct->fd_out != 1)
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
	path = joined_path(pdata.paths, cmd_struct->cmd[0]);
	if (path)
		execve(path, cmd_struct->cmd, envp);
	//free_t_data(dt);
	exit(EXIT_FAILURE);
}

int	pipex(t_pipedata pdata, char **envp, t_command *cmd_struct)
{
	pid_t	pid;

	//if (!cmd_struct->next)
	//{
	//	close(pdata.oldpipe[0]);
	//	close(pdata.oldpipe[1]);
	//	return (0);
	//}
	if (pipe(pdata.newpipe) < 0)
		perror("pipe");
	pid = fork();
	if (pid < 0)
		perror("Fork");
	else if (pid == 0)
		child_process(pdata, envp, cmd_struct);
	else
	{
		parent_process(pdata); // pid
		if (cmd_struct->next)
			pipex(pdata, envp, cmd_struct->next);
	}
	return (0);
}
