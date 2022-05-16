/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_delimit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:47:33 by hrothery          #+#    #+#             */
/*   Updated: 2022/05/16 11:14:39 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*increase_buffer(int fd, char *buf)
{
	char	*more_buf;
	int		return_value;

	return_value = 1;
	more_buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!more_buf)
		return (NULL);
	while (!ft_strchr(buf, '\n') && return_value)
	{
		return_value = read(fd, more_buf, BUFFER_SIZE);
		if (return_value < 0)
		{
			free(more_buf);
			return (NULL);
		}
		more_buf[return_value] = '\0';
		buf = ft_strjoin_gnl(buf, more_buf);
	}
	free (more_buf);
	return (buf);
}

static char	*get_line(char *buf)
{
	int		i;
	char	*out_line;

	i = 0;
	if (!buf[i])
		return (0);
	while (buf[i] != '\n' && buf[i])
		i++;
	out_line = malloc(sizeof(char) * (i + 2));
	if (!out_line)
		return (0);
	i = 0;
	while (buf[i] != '\n' && buf[i])
	{
		out_line[i] = buf[i];
		i++;
	}
	if (buf[i] == '\n')
		out_line[i++] = '\n';
	out_line[i] = '\0';
	free(buf);
	return (out_line);
}

char	*gnl_delimit(int fd, char *delimiter)
{
	char		*line;
	char		*buf;

	buf = NULL;
	if (fd < 0)
		return (0);
	write(1, ">", 1);
	buf = increase_buffer(fd, buf);
	if (!buf)
		return (0);
	line = get_line(buf);
	if (!ft_strcmp(line, "\n"))
		return (line);
	if (!ft_strncmp(line, delimiter, ft_strlen(delimiter)) \
	&& ft_strlen(line) - 1 == ft_strlen(delimiter))
	{
		free(line);
		return (NULL);
	}
	return (line);
}
