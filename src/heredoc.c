/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 14:46:42 by hrothery          #+#    #+#             */
/*   Updated: 2022/05/11 13:19:57 by cfabian          ###   ########.fr       */
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
	close(fd);
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
