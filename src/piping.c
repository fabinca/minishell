/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 08:42:52 by cfabian           #+#    #+#             */
/*   Updated: 2022/05/12 19:12:39 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	dup2_and_close(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
		perror("What the hell");
	close(oldfd);
}

static void	parent_process(t_pdata pdata, t_command *cmd_s)
{
	signal(SIGINT, SIG_IGN);
	close(pdata.oldpipe[0]);
	close(pdata.oldpipe[1]);
	if (cmd_s->next && cmd_s->cmd && ft_strcmp(cmd_s->cmd[0], "cat"))
		waitpid(pdata.pid, &g_last_exit, WNOHANG);
	else
		waitpid(pdata.pid, &g_last_exit, 0);
	signal(SIGINT, sighandler);
	g_last_exit = g_last_exit / 255;
	dup2_and_close(pdata.newpipe[0], pdata.oldpipe[0]);
	dup2_and_close(pdata.newpipe[1], pdata.oldpipe[1]);
}

void	child_p(t_pdata pd, t_envvar *env_l, t_envvar *exp_l, t_command *cmd_s)
{
	char	*path;
	char	**own_env;

	path = NULL;
	signal(SIGINT, sighandler_child);
	if (!pd.first_cmd)
		dup2_and_close(pd.oldpipe[0], STDIN_FILENO);
	if (cmd_s->fd_in != 0)
		dup2_and_close(cmd_s->fd_in, STDIN_FILENO);
	if (!cmd_s->next || cmd_s->fd_out != 1)
		dup2_and_close(cmd_s->fd_out, pd.newpipe[1]);
	dup2_and_close(pd.newpipe[1], STDOUT_FILENO);
	close(pd.newpipe[0]);
	close(pd.oldpipe[1]);
	if (is_builtin(cmd_s->cmd))
		parse_builtin(cmd_s, env_l, exp_l);
	else
	{
		if (pd.paths)
			path = joined_path(pd.paths, cmd_s->cmd[0]);
		own_env = ft_listtostr(env_l);
		if (path)
			execve(path, cmd_s->cmd, own_env);
		free(path);
		execve(cmd_s->cmd[0], cmd_s->cmd, own_env);
		ft_double_free(own_env);
		print_error("minishell: ", cmd_s->cmd[0], ": command not found\n", NULL);
		exit(127);
	}
		//free_t_data(dt);
	exit(0);
}

int	pipex(t_pdata pdata, t_envvar *env_list, t_envvar *exp_list, t_command *cmd_struct)
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
		child_p(pdata, env_list, exp_list, cmd_struct);
	else
	{
		parent_process(pdata, cmd_struct); // pid
		pdata.first_cmd = 0;
		pipex(pdata, env_list, exp_list, cmd_struct->next);
	}
	return (0);
}
