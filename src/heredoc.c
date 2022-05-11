/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 14:46:42 by hrothery          #+#    #+#             */
/*   Updated: 2022/05/11 12:08:13 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exe_heredoc(char *delimiter)
{
	char	*str;
	int		fd;

	str = (char *)1;
	fd = open(".tmpheredoc", O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (fd < 0)
	{
		perror("open");
		return (-1);
	}
	while (str)
	{
		str = gnl_delimit(STDIN_FILENO, delimiter);
		if (str)
		{
			write(fd, str, ft_strlen(str));
			free(str);
		}
	}
	return (fd);
}

/*
int	main(void)
{
	double_delimiter("bla");
	return (0);
	close(fd);
}
*/
