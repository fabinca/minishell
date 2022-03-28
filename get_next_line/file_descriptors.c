/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_descriptors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:17:30 by hrothery          #+#    #+#             */
/*   Updated: 2022/03/28 14:41:10 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "gnl_delimit.h"
#include <sys/stat.h>
#include <sys/types.h>
//#include "../libft/libft.h"
#define _GNU_SOURCE

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*s1 != *s2)
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		if (*s1 == 0)
			return (0);
		i++;
		s1++;
		s2++;
	}
	return (0);
}


void	builtin_gnl_without_delimiter(char *delimiter)
{
	char	*str;
	int		fd;

	str = (char *)1;
	fd = open("/home/hrothery/Minishell/my_work_for_minishell/get_next_line/gnltemp", O_CREAT | O_RDWR | O_APPEND, 0777);
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
	builtin_gnl_without_delimiter("Mädchen");
	return (0);
}
