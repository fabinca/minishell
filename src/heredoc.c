/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 14:46:42 by hrothery          #+#    #+#             */
/*   Updated: 2022/05/13 15:39:39 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exe_heredoc(char *delimiter, t_envvar *env_list)
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
			str = quotes_and_envvars(str, ft_strlen(str) + 1, env_list);
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
