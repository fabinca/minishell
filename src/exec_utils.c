/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 11:10:20 by hrothery          #+#    #+#             */
/*   Updated: 2022/05/12 11:35:03 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/* 
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
			ft_putstr_fd(cmd_struct->cmd[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			g_last_exit = 127;
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
} */

void	free_my_paths(char **paths)
{
	int	i;

	i = 0;
	if (!paths)
		return ;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

char	**find_paths(t_envvar *env_list)
{
	char	**my_paths;

	while (env_list)
	{
		if (!ft_strcmp(env_list->name, "PATH"))
		{
			my_paths = ft_split_slash(env_list->content, ':');
			return (my_paths);
		}
		env_list = env_list->next;
	}
	return (NULL);
}

char	*joined_path(char **my_paths, char *token)
{
	char	*joined_path;
	int		i;

	i = 0;
	while (my_paths[i])
	{
		//joined_path = (char *)ft_calloc((ft_strlen(my_paths[i]) + ft_strlen(token) + 1), sizeof(char));
		//if (!joined_path)
		//	return (0);
		joined_path = ft_strjoin(my_paths[i], token);
		if (!joined_path)
			return (0);
		if (access(joined_path, X_OK) == 0)
			return (joined_path);
		else
		{
			free (joined_path);
			i++;
		}
	}
	return (0);
}
