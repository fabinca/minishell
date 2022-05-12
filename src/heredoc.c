/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 14:46:42 by hrothery          #+#    #+#             */
/*   Updated: 2022/05/12 12:53:47 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exe_heredoc(char *delimiter)
{
	char	*str;
	int		fd;
	pid_t	pid;

	str = (char *)1;
	pid = fork();
	if (pid == -1)
		perror("fork");
	if (pid == 0)
	{
		signal(SIGINT, sighandler_child);
		fd = open(".tmpheredoc", O_CREAT | O_RDWR | O_TRUNC, 0666);
		if (fd < 0)
		{
			perror("open");
			return ;
		}
		while (str)
		{
			str = gnl_delimit(STDIN_FILENO, delimiter);
			if (!str)
				break ;
			write(fd, str, ft_strlen(str));
			free(str);
		}
		close(fd);
		exit(0);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &g_last_exit, 0);
		g_last_exit = g_last_exit / 255;
		signal(SIGINT, sighandler);
	}
}

/*
int	main(void)
{
	double_delimiter("bla");
	return (0);
	close(fd);
}
*/
