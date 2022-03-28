/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_descriptors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:17:30 by hrothery          #+#    #+#             */
/*   Updated: 2022/03/28 13:17:17 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "../libft.h"
#define _GNU_SOURCE

void	double_delimiter(char *delimiter)
{
	char	*str;
	int		fd;

	str = (char *)1;
	fd = open("file path", O_CREAT | O_RDWR | O_APPEND, 0777);
	if (fd < 0)
	{
		perror("open\n");
		return ;
	}
	while (str)
	{
		str = gnl_delimit(STDIN_FILENO, delimiter);
		if (str)
			write(fd, str, ft_strlen(str)); //write into the temp file
		free(str);
	}
	
}

int	main(void)
{
	double_delimiter("Mädchen");
	return (0);
}
