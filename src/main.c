/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:10:11 by cfabian           #+#    #+#             */
/*   Updated: 2022/03/18 16:52:39 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
// Display a prompt when waiting for a new command.
// Have a working history.
int	main(void)
{
	char	*prompt;
	char	cwd[100];
	char	*line;

	prompt = "\033[0;32mminishell:\033[0m$ ";
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd error");
		return (0);
	}	
	while (1)
	{
		line = readline(prompt);
		add_history(line);
		evaluate(line);
		free(line);
	}
	return (0);
}
