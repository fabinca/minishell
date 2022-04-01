/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 14:46:42 by hrothery          #+#    #+#             */
/*   Updated: 2022/04/01 14:47:43 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//This function opens a temp file in the same directory and copies all lines into the file 
//until a line matches the delimiter.
//The file needs to be closed again because most Linux systems do not support O_TEMP
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
			write(fd, str, ft_strlen(str)); //write into the temp file
		free(str);
	}
	close(fd);
}
