/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 09:25:26 by hrothery          #+#    #+#             */
/*   Updated: 2022/05/06 09:25:54 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_cmd(t_command *cmd_struct, t_envvar *env_list, char **envp)
{
	char	**paths;
	char	*exec_path;
	pid_t	pid;

	if (is_builtin(cmd_struct->cmd))
		parse_builtin(cmd_struct, env_list);
	else
	{
		paths = find_paths(env_list);
		exec_path = joined_path(paths, cmd_struct->cmd[0]);
		if (!exec_path)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd_struct->cmd[0], 2);
			ft_putstr_fd(": no such file or directory\n", 2);
			return (1);
		}
		if ((pid = fork()) < 0)
		{
			ft_putstr_fd("error: fork\n", 2);
			return (1);
		}
		if (pid == 0)
		{
			if (execve(exec_path, cmd_struct->cmd, envp) < 0)
			{
				ft_putstr_fd("error:  cannot execute ", 2);
				ft_putstr_fd(cmd_struct->cmd[0], 2);
				ft_putstr_fd("\n", 2);
				free(exec_path);
				free_my_paths(paths);
				//exit(EXIT_FAILURE);
				return (1);
			}
		}
		waitpid(0, NULL, 0);
	}
	return (0);
	//exit(EXIT_SUCCESS);
}
