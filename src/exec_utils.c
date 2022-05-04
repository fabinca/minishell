/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 11:10:20 by hrothery          #+#    #+#             */
/*   Updated: 2022/05/04 15:10:11 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_my_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
		free(paths[i++]);
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
		joined_path = malloc((ft_strlen(my_paths[i]) + ft_strlen(token) + 1)
				* sizeof(char));
		if (!joined_path)
			return (0);
		joined_path = ft_strjoin(my_paths[i], token);
		if (access(joined_path, F_OK) == 0)
			return (joined_path);
		else
		{
			free (joined_path);
			i++;
		}
	}
	return (0);
}
