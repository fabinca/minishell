/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 14:46:42 by hrothery          #+#    #+#             */
/*   Updated: 2022/04/06 08:20:31 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exe_heredoc(char *delimiter)
{
	char	*str;
	int		fd;

	str = (char *)1;
	fd = open(".tmpheredoc", O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("open");
		return ;
	}
	while (str)
	{
		str = gnl_delimit(STDIN_FILENO, delimiter);
		if (str)
			write(fd, str, ft_strlen(str));
		free(str);
	}
	close(fd);
}
