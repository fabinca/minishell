/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:39:40 by cfabian           #+#    #+#             */
/*   Updated: 2022/03/18 16:53:27 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//t_command	**parser(char **tokens)
//{
//	t_command	**cmds_info;
//	// split by pipes; 
//	// if nothing before first pipe: / between two pipes: error
//	// if nothing behind last pipe: readline again like in bash or error ?
//	//if multiple contradicting redirections inside one part: use last one (?)
//	// tokens to cmd array and redirection struct (parser)

//	return (cmds_info);
//}

void	evaluate(char *line)
{
	t_list		*start;
	//t_command	**cmds_info;

	start = lexer(line);
	//cmds_info = parser(tokens);
	while (start->next)
	{
		start = start->next;
		printf("%s\n", (char *)start->content);
	}
	// checking for builtins
	// fork and execve
}

