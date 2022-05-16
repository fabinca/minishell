/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 12:52:31 by cfabian           #+#    #+#             */
/*   Updated: 2022/05/16 08:43:09 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	display_prompt(void)
{
	char	*user;
	char	*dir;
	char	pwd[100];

	user = getenv("USER");
	dir = ft_strrchr(getcwd(pwd, 100), '/');
	printf("%s%s:%s~%s$%s  ", GRN, user, BLU, dir, NRM);
}

void	sighandler_child(int num)
{
	if (num == SIGINT)
	{
		exit(1);
	}
}

void	sighandler(int num)
{
	if (num == SIGINT)
	{
		g_last_exit = 130;
		rl_replace_line("", 0);
		printf("\n");
		display_prompt();
		printf("\033[1;36m\033[1mMinishell\033[0m$ ");
		rl_redisplay();
	}
}
