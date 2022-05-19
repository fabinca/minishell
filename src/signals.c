/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 12:52:31 by cfabian           #+#    #+#             */
/*   Updated: 2022/05/18 14:56:51 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//void	display_prompt(void)
//{
//	char	*user;
//	char	*dir;
//	char	pwd[MAX_PATH];

//	user = getenv("USER");
//	dir = ft_strrchr(getcwd(pwd, MAX_PATH), '/');
//	printf("%s%s:%s~%s$%s  ", GRN, user, BLU, dir, NRM);
//}

void	sighandler_child(int num)
{
	if (num == SIGINT)
	{
		rl_replace_line("", 0);
		printf("\n");
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
		//display_prompt();
		//printf("\033[1;36m\033[1mMinishell\033[0m$ ");
		rl_on_new_line();
		rl_redisplay();
	}
}
