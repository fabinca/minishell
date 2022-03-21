/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 16:24:57 by hrothery          #+#    #+#             */
/*   Updated: 2022/03/21 13:49:16 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"

#define GRN  "\x1B[1;32m"
#define BLU  "\x1B[1;34m"
#define NRM  "\x1B[0m"

void	parse_builtin(char *line, char **envp, int	*exit_status);

void	display_prompt(void)
{
	char	*user;
	char	*dir;
	char	*pwd;
	char	*desktop;
	char	*line;

	user =  getenv("USER");
	desktop = getenv("NAME");
	pwd = getenv("PWD");
	dir = ft_strrchr(pwd, '/');
	printf("%s%s@%s:%s~%s$%s ", GRN, user, desktop, BLU, dir, NRM);
}


int	main(int argc, char **argv, char **envp)
{
	int	exit_status;
	char *line;

	exit_status = 0;
	while (exit_status == 0)
	{
		//display_prompt();
		line = readline("\033[1;36m\033[1mMinishell\033[0m$ ");
		parse_builtin(line, envp, &exit_status);
		add_history(line);
		free(line);
	}
	return (0);
}
