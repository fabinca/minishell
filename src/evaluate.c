/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:39:40 by cfabian           #+#    #+#             */
/*   Updated: 2022/03/16 18:03:26 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**lexer( char *line)
{
	char	**tokens;
	//replace environment variables and $?
	//Not interpret unclosed quotes or special characters which are not required by the
	//subject such as \ (backslash) or ; (semicolon). -> remove ?
	//Handle ’ (single quote) which should prevent the shell from interpreting the meta-
	//characters in the quoted sequence.
	//• Handle " (double quote) which should prevent the shell from interpreting the meta-
	//characters in the quoted sequence except for $ (dollar sign)
	return (tokens);
}

t_command	**parser(char **tokens)
{
	t_command	**cmds_info;
	// split by pipes; 
	// if nothing before first pipe: / between two pipes: error
	// if nothing behind last pipe: readline again like in bash or error ?
	//if multiple contradicting redirections inside one part: use last one (?)
	// tokens to cmd array and redirection struct (parser)

	return (cmds_info);
}

void	evaluate(char *line)
{
	char		**tokens;
	t_command	**cmds_info;

	tokens = lexer(line);
	cmds_info = parser(tokens);
	
	// checking for builtins
	// fork and execve
}

